#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#define IS(n, str) (strcmp((n)->name, (str)) == 0)
#define MAX_LOOP_DEPTH 32
static int break_stack[MAX_LOOP_DEPTH], break_sp = 0;
static int cont_stack[MAX_LOOP_DEPTH], cont_sp = 0;

//1.全局状态
static FILE *ir;          
static int reg_cnt = 1;   //寄存器计数
static int label_cnt = 0; //标签计数，控制流跳转
static int has_ret = 0;   //当前函数是否包含返回语句
static int bb_closed = 0; //当前基本块是否已经结束

//2.记录每个寄存器的类型，false 表示整型，true 表示浮点型
static bool reg_is_float[10000] = {0};
static int new_reg(void) // 默认 int
{
    int r = reg_cnt++;
    reg_is_float[r] = false;
    return r;
}
static int new_label(void) { return label_cnt++; }

//3.符号表
typedef struct Var
{
    char *name; //变量名
    char *ty;   //IR 类型字符串
    int ptr;    //alloca 返回的指针寄存器，变量在内存中的位置
    int dims[8];
    int dim_cnt;  //数组维度信息 ，整数为0
    int is_float; //基础元素类型：0‑int 1‑float
    struct Var *next;
} Var;

//4.作用域
typedef struct Scope
{
    Var *vars;
    struct Scope *prev;
} Scope;
static Scope *cur = NULL;

//创建一个新的作用域
static void push_scope(void)
{
    Scope *s = calloc(1, sizeof(Scope));
    s->prev = cur;
    cur = s;
}
//弹出当前作用域
static void pop_scope(void)
{
    Var *v = cur->vars;
    while (v)
    {
        Var *n = v->next;
        free(v->name);
        free(v->ty);
        free(v);
        v = n;
    }
    Scope *p = cur->prev;
    free(cur);
    cur = p;
}

//在当前作用域中查找变量
static Var *lookup(const char *name)
{
    for (Scope *s = cur; s; s = s->prev)
        for (Var *v = s->vars; v; v = v->next)
            if (strcmp(v->name, name) == 0)
                return v;
    return NULL;
}

//add_var：添加变量到当前作用域。
static Var *add_var(const char *name, const char *ty, int ptr, int *dims, int dc, int is_float)
{
    Var *v = calloc(1, sizeof(Var));
    v->name = strdup(name);
    v->ty = strdup(ty);
    v->ptr = ptr;
    v->dim_cnt = dc;
    v->is_float = is_float;
    for (int i = 0; i < dc; ++i)
        v->dims[i] = dims[i];
    v->next = cur->vars;
    cur->vars = v;
    return v;
}

//is_float_token：检查字符串 lex 是否为浮点数。
//fmt_float：将浮点数 d 格式化为科学计数法字符串。
//eval_const：递归求值常量表达式。
static bool is_float_token(const char *lex) { return strchr(lex, '.') != NULL; }
static void fmt_float(double d, char *buf) { sprintf(buf, "%.6e", d); }
static int eval_const(Node *n);

//flatten_initval：扁平收集 InitVal 里的所有 Exp 常量到 vals[]，返回数量
static int flatten_initval(Node *iv, int vals[])
{
    int cnt = 0;
    void dfs(Node *p)
    {
        if (IS(p, "Exp")) {                 //常量表达式
            vals[cnt++] = eval_const(p);
            return;
        }
        for (int i = 0; i < p->kid_cnt; ++i)
            dfs(p->kids[i]);
    }
    dfs(iv);
    return cnt;
}

//float_literal_bitcast：将浮点字面量转换为 IR 中的 bitcast 指令。
static char *float_literal_bitcast(const char *lex)
{
    union
    {
        float f;
        uint32_t u;
    } bits;
    bits.f = strtof(lex, NULL); //str 3.14 - float 3.14
    char buf[64];
    /* 2) 生成 “bitcast (i32 <bits> to float)” */
    snprintf(buf, sizeof(buf),
            "bitcast i32 %u to float", bits.u);
    return strdup(buf); /* 调用者负责释放           */
}

//get_num：将数字字面量转换为整数。
//eval_const：递归求值常量表达式。
static int get_num(Node *num) { return atoi(num->kids[0]->name); }
static int eval_const(Node *n)
{
    if (IS(n, "ConstExp"))
        return eval_const(n->kids[0]);
    if (IS(n, "Exp"))
        return eval_const(n->kids[0]);
    if (IS(n, "NUMBER"))
        return get_num(n);
    if (IS(n, "PrimaryExp"))
        return eval_const(n->kids[0]);
    if (IS(n, "UnaryExp"))
    {
        if (n->kid_cnt == 2 && IS(n->kids[0], "-"))
            return -eval_const(n->kids[1]);
        return eval_const(n->kids[0]);
    }
    if (IS(n, "AddExp") || IS(n, "MulExp"))
    {
        int val = eval_const(n->kids[0]);
        for (int i = 1; i < n->kid_cnt; i += 2)
        {
            char *op = n->kids[i]->name;
            int rhs = eval_const(n->kids[i + 1]);
            if (*op == '+')
                val += rhs;
            else if (*op == '-')
                val -= rhs;
            else if (*op == '*')
                val *= rhs;
            else
                val /= rhs;
        }
        return val;
    }
    return 0;
}

//build_array_ty：生成数组类型字符串，[d[0] x d[1] x ... x d[dc-1]]
static void build_array_ty(char *buf, int *d, int dc, int is_float)
{
    if (dc == 0)
    {
        strcat(buf, is_float ? "float" : "i32");
        return;
    }
    char t[64];
    sprintf(t, "[%d x ", d[0]);
    strcat(buf, t);
    build_array_ty(buf + strlen(buf), d + 1, dc - 1, is_float);
    strcat(buf, "]");
}

//ensure_float：确保寄存器 reg 的类型为浮点型。
//ensure_int：确保寄存器 reg 的类型为整型。
static int ensure_float(int reg)
{
    if (reg_is_float[reg])
        return reg;
    int r = new_reg();
    fprintf(ir, "  %%%d = sitofp i32 %%%d to float\n", r, reg);
    reg_is_float[r] = true;
    return r;
}
static int ensure_int(int reg)
{
    if (!reg_is_float[reg])
        return reg;
    int r = new_reg();
    fprintf(ir, "  %%%d = fptosi float %%%d to i32\n", r, reg);
    reg_is_float[r] = false;
    return r;
}

//gen_exp：生成表达式。
//gen_rel：生成关系表达式。
static int gen_exp(Node *);
static int gen_rel(Node *);

//gen_primary：生成基本表达式。
static int gen_primary(Node *n)
{
    if (IS(n->kids[0], "("))//括号表达式
        return gen_exp(n->kids[1]);

    Node *x = n->kids[0];
    //数值常量
    if (IS(x, "NUMBER"))
    {
        const char *lex = x->kids[0]->name;
        int r = new_reg();

        if (is_float_token(lex))          //浮点字面量
        {
            char *fc = float_literal_bitcast(lex);
            //装进寄存器，保持 SSA 形式
            fprintf(ir, "  %%%d = %s\n", r, fc);
            reg_is_float[r] = true;
            free(fc);
        }
        else                              //整数字面量
        {
            fprintf(ir, "  %%%d = add i32 0, %s\n", r, lex);
            reg_is_float[r] = false;
        }
        return r;
    }

    //变量访问
    if (IS(x, "LVal"))
    {
        Var *v = lookup(x->kids[0]->name);
        if (!v)
        {
            fprintf(stderr, "未声明变量 %s\n", x->kids[0]->name);
            exit(1);
        }
        int addr;
        if (v->dim_cnt == 0)
        {
            addr = v->ptr;
        }
        else
        {
            int idx[8], ic = 0;
            void collect_idx(Node * p)
            {
                if (!p)
                    return;
                for (int i = 0; i < p->kid_cnt; ++i)
                {
                    if (IS(p->kids[i], "(") && i + 1 < p->kid_cnt)
                        idx[ic++] = gen_exp(p->kids[i + 1]);
                    collect_idx(p->kids[i]);
                }
            }
            collect_idx(x);
            int g = new_reg();
            fprintf(ir, "  %%%d = getelementptr %s, %s* %%%d, i32 0", g, v->ty, v->ty, v->ptr);
            for (int k = 0; k < ic; ++k)
                fprintf(ir, ", i32 %%%d", idx[k]);
            fprintf(ir, "\n");
            addr = g;
        }
        int r = new_reg();
        fprintf(ir, "  %%%d = load %s, %s* %%%d\n", r, v->is_float ? "float" : "i32", v->is_float ? "float" : "i32", addr);
        reg_is_float[r] = v->is_float;
        return r;
    }
    //报错
    fprintf(stderr, "Unhandled PrimaryExp type: %s\n", x->name);
    exit(1);
}

//gen_unary：生成一元表达式。
static int gen_unary(Node *n)
{
    //函数调用
    if (IS(n, "UnaryExp") && n->kid_cnt >= 3 && IS(n->kids[1], "("))
    {
        int args[16], ac = 0;
        if (n->kid_cnt == 4)
        {
            void gather(Node * p)
            {
                if (IS(p, "Exp"))
                {
                    args[ac++] = gen_exp(p);
                    return;
                }
                for (int i = 0; i < p->kid_cnt; ++i)
                    gather(p->kids[i]);
            }
            gather(n->kids[2]);
        }
        int r = new_reg();
        fprintf(ir, "  %%%d = call i32 @%s(", r, n->kids[0]->name);
        for (int i = 0; i < ac; ++i)
        {
            if (i)
                fputs(", ", ir);
            fprintf(ir, "i32 %%%d", ensure_int(args[i]));
        }
        fputs(")\n", ir);
        return r;
    }
    if (n->kid_cnt == 1)
        return gen_primary(n->kids[0]); //普通一元表达式

    //单目负号
    int v = gen_unary(n->kids[1]);
    if (reg_is_float[v])
    {
        int r = new_reg();
        fprintf(ir, "  %%%d = fsub float 0.000000e+00, %%%d\n", r, v);
        reg_is_float[r] = true;
        return r;
    }
    else
    {
        int r = new_reg();
        fprintf(ir, "  %%%d = sub i32 0, %%%d\n", r, v);
        return r;
    }
}

//gen_mul：生成乘法表达式。
static int gen_mul(Node *n)
{
    int left = gen_exp(n->kids[0]);
    for (int i = 1; i < n->kid_cnt; i += 2)
    {
        char *op = n->kids[i]->name;
        int right = gen_unary(n->kids[i + 1]);
        if (reg_is_float[left] || reg_is_float[right])
        {
            left = ensure_float(left);
            right = ensure_float(right);
            int r = new_reg();
            if (*op == '*')
                fprintf(ir, "  %%%d = fmul float %%%d, %%%d\n", r, left, right);
            else
                fprintf(ir, "  %%%d = fdiv float %%%d, %%%d\n", r, left, right);
            reg_is_float[r] = true;
            left = r;
        }
        else
        {
            int r = new_reg();
            if (*op == '*')
                fprintf(ir, "  %%%d = mul i32 %%%d, %%%d\n", r, left, right);
            else
                fprintf(ir, "  %%%d = sdiv i32 %%%d, %%%d\n", r, left, right);
            left = r;
        }
    }
    return left;
}

//gen_add：生成加法表达式。
static int gen_add(Node *n)
{
    int left = gen_exp(n->kids[0]);
    for (int i = 1; i < n->kid_cnt; i += 2)
    {
        char *op = n->kids[i]->name;
        int right = gen_mul(n->kids[i + 1]);
        if (reg_is_float[left] || reg_is_float[right])
        {
            left = ensure_float(left);
            right = ensure_float(right);
            int r = new_reg();
            if (*op == '+')
                fprintf(ir, "  %%%d = fadd float %%%d, %%%d\n", r, left, right);
            else
                fprintf(ir, "  %%%d = fsub float %%%d, %%%d\n", r, left, right);
            reg_is_float[r] = true;
            left = r;
        }
        else
        {
            int r = new_reg();
            if (*op == '+')
                fprintf(ir, "  %%%d = add i32 %%%d, %%%d\n", r, left, right);
            else
                fprintf(ir, "  %%%d = sub i32 %%%d, %%%d\n", r, left, right);
            left = r;
        }
    }
    return left;
}

//gen_rel：生成关系表达式。
static int gen_rel(Node *n)
{
    //bool
    if (n->kid_cnt == 1)
    {
        int v = gen_exp(n->kids[0]);
        int r = new_reg();
        if (reg_is_float[v])
        {
            fprintf(ir, "  %%%d = fcmp one float %%%d, 0.000000e+00\n", r, v);
        }
        else
        {
            fprintf(ir, "  %%%d = icmp ne i32 %%%d, 0\n", r, v);
        }
        return r;
    }

    const char *op = n->kids[1]->name;

    //逻辑与 / 或
    if (strcmp(op, "&&") == 0 || strcmp(op, "||") == 0)
    {
        int left = gen_rel(n->kids[0]);
        int right = gen_rel(n->kids[2]);
        int r = new_reg();
        if (strcmp(op, "&&") == 0)
            fprintf(ir, "  %%%d = and i1 %%%d, %%%d\n", r, left, right);
        else
            fprintf(ir, "  %%%d = or  i1 %%%d, %%%d\n", r, left, right);
        return r;
    }

    //比较运算
    int l = gen_exp(n->kids[0]);
    int rgt = gen_exp(n->kids[2]);
    const bool use_float = reg_is_float[l] || reg_is_float[rgt];
    if (use_float)
    {
        l = ensure_float(l);
        rgt = ensure_float(rgt);
    }
    const char *cc;
    if (use_float)
    {
        cc = (*op == '<') ? "olt" : (*op == '>')        ? "ogt"
                                : strcmp(op, "<=") == 0 ? "ole"
                                : strcmp(op, ">=") == 0 ? "oge"
                                : strcmp(op, "==") == 0 ? "oeq"
                                                        : "one";
    }
    else
    {
        cc = (*op == '<') ? "slt" : (*op == '>')        ? "sgt"
                                : strcmp(op, "<=") == 0 ? "sle"
                                : strcmp(op, ">=") == 0 ? "sge"
                                : strcmp(op, "==") == 0 ? "eq"
                                                        : "ne";
    }
    int r = new_reg();
    fprintf(ir, "  %%%d = %scmp %s %s %%%d, %%%d\n", r, use_float ? "f" : "i", cc, use_float ? "float" : "i32", l, rgt);
    return r;
}

//gen_exp：生成表达式。
static int gen_exp(Node *n)
{
    if (IS(n, "RelExp"))
        return gen_rel(n);
    if (IS(n, "Exp") || IS(n, "AddExp"))
        return gen_add(n);
    if (IS(n, "MulExp"))
        return gen_mul(n);
    if (IS(n, "UnaryExp"))
        return gen_unary(n);
    if (IS(n, "PrimaryExp"))
        return gen_primary(n);
    if (IS(n, "NUMBER"))
    {
        Node wrap;
        wrap.kids = malloc(sizeof(Node *));
        wrap.kids[0] = n;
        wrap.kid_cnt = 1;
        wrap.name = "PrimaryExp";
        int r = gen_primary(&wrap);
        free(wrap.kids);
        return r;
    }
    if (IS(n, "LVal"))
    {
        Node wrap;
        wrap.kids = malloc(sizeof(Node *));
        wrap.kids[0] = n;
        wrap.kid_cnt = 1;
        wrap.name = "PrimaryExp";
        int r = gen_primary(&wrap);
        free(wrap.kids);
        return r;
    }
    fprintf(stderr, "未处理的表达式节点: %s\n", n->name);
    exit(1);
}

//gen_lval_addr：获取 LVal 地址。
static int gen_lval_addr(Node *lval)
{
    Var *v = lookup(lval->kids[0]->name);
    if (!v)
    {
        fprintf(stderr, "未声明变量 %s\n", lval->kids[0]->name);
        exit(1);
    }
    if (v->dim_cnt == 0)
        return v->ptr;

    int idx_reg[8], ic = 0;
    void collect_idx(Node * p)
    {
        if (!p)
            return;
        for (int i = 0; i < p->kid_cnt; ++i)
        {
            if (IS(p->kids[i], "(") && i + 1 < p->kid_cnt)
                idx_reg[ic++] = gen_exp(p->kids[i + 1]);
            collect_idx(p->kids[i]);
        }
    }
    collect_idx(lval);
    int g = new_reg();
    fprintf(ir, "  %%%d = getelementptr %s, %s* %%%d, i32 0", g, v->ty, v->ty, v->ptr);
    for (int k = 0; k < ic; ++k)
        fprintf(ir, ", i32 %%%d", idx_reg[k]);
    fprintf(ir, "\n");
    return g;
}

//gen_stmt：生成语句。
static void gen_stmt(Node *); /* forward */

//gen_assign：生成赋值语句。
static void gen_assign(Node *s)
{
    int addr = gen_lval_addr(s->kids[0]);
    Var *v = lookup(s->kids[0]->kids[0]->name);
    int val = gen_exp(s->kids[2]);
    if (v->is_float)
        val = ensure_float(val);
    else
        val = ensure_int(val);
    fprintf(ir, "  store %s %%%d, %s* %%%d\n", v->is_float ? "float" : "i32", val, v->is_float ? "float" : "i32", addr);
}

//gen_ret：生成返回语句。
static void gen_ret(Node *s)
{
    int v = gen_exp(s->kids[1]);
    v = ensure_int(v); //函数返回值仍固定 i32
    fprintf(ir, "  ret i32 %%%d\n", v);
    has_ret = 1;
    bb_closed = 1;
}

//gen_while：生成 while 循环。
static void gen_while(Node *s)
{
    int Lcond = new_label(), Lbody = new_label(), Lend = new_label();
    break_stack[break_sp++] = Lend;
    cont_stack[cont_sp++] = Lcond;

    fprintf(ir, "  br label %%L%d\n", Lcond);
    fprintf(ir, "L%d:\n", Lcond);
    bb_closed = 0;
    int c = gen_rel(s->kids[2]);
    fprintf(ir, "  br i1 %%%d, label %%L%d, label %%L%d\n", c, Lbody, Lend);
    fprintf(ir, "L%d:\n", Lbody);
    bb_closed = 0;
    gen_stmt(s->kids[4]);
    fprintf(ir, "  br label %%L%d\n", Lcond);
    bb_closed = 1;
    fprintf(ir, "L%d:\n", Lend);
    bb_closed = 0;
    --break_sp;
    --cont_sp;
}

//gen_if：生成 if 语句。
static void gen_block(Node *);
static void gen_if(Node *s)
{
    int Lthen = new_label();
    int Lend = new_label();
    int Lelse = (s->kid_cnt > 5 ? new_label() : Lend);
    int cond = gen_rel(s->kids[2]);
    fprintf(ir, "  br i1 %%%d, label %%L%d, label %%L%d\n", cond, Lthen, Lelse);
    bb_closed = 1;
    fprintf(ir, "L%d:\n", Lthen);
    bb_closed = 0;
    gen_stmt(s->kids[4]);
    if (!bb_closed)
    {
        fprintf(ir, "  br label %%L%d\n", Lend);
        bb_closed = 1;
    }
    if (Lelse != Lend)
    {
        fprintf(ir, "L%d:\n", Lelse);
        bb_closed = 0;
        gen_stmt(s->kids[6]);
        if (!bb_closed)
        {
            fprintf(ir, "  br label %%L%d\n", Lend);
            bb_closed = 1;
        }
    }
    fprintf(ir, "L%d:\n", Lend);
    bb_closed = 0;
}

//gen_stmt：生成语句。
static void gen_stmt(Node *n)
{
    if (!IS(n, "Stmt"))
    {
        gen_block(n);
        return;
    }
    if (n->kid_cnt >= 3 && IS(n->kids[1], "="))
        gen_assign(n);
    else if (IS(n->kids[0], "return"))
        gen_ret(n);
    else if (IS(n->kids[0], "while"))
        gen_while(n);
    else if (IS(n->kids[0], "{"))
        gen_block(n->kids[1]);
    else if (IS(n->kids[0], "Block"))
        gen_block(n->kids[0]);
    else if (IS(n->kids[0], "break"))
    {
        if (break_sp == 0)
        {
            fprintf(stderr, "break 不在循环内\n");
            exit(1);
        }
        fprintf(ir, "  br label %%L%d\n", break_stack[break_sp - 1]);
        bb_closed = 1;
    }
    else if (IS(n->kids[0], "if"))
        gen_if(n);
    else if (IS(n->kids[0], "continue"))
    {
        if (cont_sp == 0)
        {
            fprintf(stderr, "continue 不在循环内\n");
            exit(1);
        }
        fprintf(ir, "  br label %%L%d\n", cont_stack[cont_sp - 1]);
        bb_closed = 1;
    }
}

//scan_vardef：扫描变量声明。
//scan_vardef_list：扫描变量声明列表。
static void scan_vardef(Node *vd, int base_is_float);
static void scan_vardef_list(Node *n, int base_is_float)
{
    if (IS(n, "VarDef"))
    {
        scan_vardef(n, base_is_float);
        return;
    }
    for (int i = 0; i < n->kid_cnt; ++i)
        scan_vardef_list(n->kids[i], base_is_float);
}

//collect_dims：收集维度信息。
static void collect_dims(Node *sub, int *dims, int *dc)
{
    if (!sub || IS(sub, "epsilon"))
        return;
    for (int i = 0; i < sub->kid_cnt; ++i)
        collect_dims(sub->kids[i], dims, dc);
    if (IS(sub, "ConstExp"))
        dims[(*dc)++] = eval_const(sub);
}

// 收集变量名、类型、数组维度。
// 分配空间（alloca），加入符号表。
// 处理初始化（标量或数组），生成 store 指令。
static void scan_vardef(Node *vd, int base_is_float)
{
    char *id = vd->kids[0]->name;
    int dims[8], dc = 0;
    collect_dims(vd->kids[1], dims, &dc);//收集维度
    char ty[128] = {0};
    build_array_ty(ty, dims, dc, base_is_float);//构建数组类型
    int ptr = new_reg();
    fprintf(ir, "  %%%d = alloca %s\n", ptr, ty);
    Var *v = add_var(id, ty, ptr, dims, dc, base_is_float);

    bool has_init = false; //常量初始化
    for (int i = 0; i < vd->kid_cnt; ++i)
        if (IS(vd->kids[i], "InitVal"))
        {
            has_init = true;
            Node *iv = vd->kids[i]->kids[0];
            if (IS(iv, "Exp"))
            {
                int val = gen_exp(iv);
                if (v->is_float)
                    val = ensure_float(val);
                else
                    val = ensure_int(val);
                fprintf(ir, "  store %s %%%d, %s* %%%d\n", v->is_float ? "float" : "i32", val, v->is_float ? "float" : "i32", ptr);
            }
        }
    if (has_init && dc > 0) //有初始化and是数组
{
    int vals[1024];               
    int vc = flatten_initval(vd, vals);

    //按行主序写回数组元素
    int total = 1;
    for (int k = 0; k < dc; ++k) total *= dims[k];

    for (int idx = 0; idx < total; ++idx)
    {
        int g = new_reg();                     //GEP 寄存器

        //计算多维下标：row-major
        int rem = idx, sub[8];
        for (int k = dc - 1; k >= 0; --k) {
            sub[k] = rem % dims[k];
            rem   /= dims[k];
        }

        fprintf(ir, "  %%%d = getelementptr %s, %s* %%%d, i32 0",
                g, v->ty, v->ty, ptr);
        for (int k = 0; k < dc; ++k)
            fprintf(ir, ", i32 %d", sub[k]);
        fprintf(ir, "\n");

        int val = (idx < vc) ? vals[idx] : 0;  //多余为0
        fprintf(ir,
            "  store i32 %d, i32* %%%d\n", val, g);
    }
}
}

//walk_blockitem：递归遍历 BlockItem 链，保证顺序
static void walk_blockitem(Node *node, int block_btype)
{
    if (!node || IS(node, "epsilon"))
        return;

    if (IS(node, "VarDecl"))
    {
        //VarDecl → BType VarDefList ;
        int is_float = IS(node->kids[0]->kids[0], "float");
        scan_vardef_list(node->kids[1], is_float);
        return;
    }
    if (IS(node, "Stmt") || IS(node, "Block"))
    {
        gen_stmt(node);
        return;
    }

    for (int i = 0; i < node->kid_cnt; ++i)
        walk_blockitem(node->kids[i], block_btype);
}

//gen_block：生成基本块。
static void gen_block(Node *blk)                
{
    push_scope();
    for (int i = 0; i < blk->kid_cnt; ++i)
    {
        Node *child = blk->kids[i];
        if (!child || IS(child, "{") || IS(child, "}") || IS(child, "epsilon"))
            continue;
        walk_blockitem(child, 0);
    }
    pop_scope();
}

//collect_params：收集函数参数。
static void collect_params(Node *p, char *name[], int *cnt)
{
    if (!p || IS(p, "epsilon"))
        return;
    if (IS(p, "FuncFParam"))
    {
        if (p->kid_cnt >= 2)
            name[(*cnt)++] = p->kids[1]->name;
        return;
    }
    for (int i = 0; i < p->kid_cnt; ++i)
        collect_params(p->kids[i], name, cnt);
}

//gen_func：生成函数。
static void gen_func(Node *func)
{
    char *fname = func->kids[1]->name;
    char *param_name[16];
    int pc = 0;
    collect_params(func->kids[3], param_name, &pc);
    fprintf(ir, "define dso_local i32 @%s(", fname);
    for (int i = 0; i < pc; ++i)
    {
        if (i)
            fputs(", ", ir);
        fprintf(ir, "i32 %%%d", i);
    }
    fputs(") #0 {\n", ir);
    reg_cnt = pc + 1;
    push_scope();
    for (int i = 0; i < pc; ++i)
    {
        int ptr = new_reg();
        fprintf(ir, "  %%%d = alloca i32\n", ptr);
        fprintf(ir, "  store i32 %%%d, i32* %%%d\n", i, ptr);
        add_var(param_name[i], "i32", ptr, NULL, 0, 0);
    }
    has_ret = 0;
    gen_block(func->kids[5]);
    if (!has_ret)
        fputs("  ret i32 0\n", ir);
    pop_scope();
    fputs("}\n", ir);
}

//gen_ir：生成 IR 代码。
void gen_ir(Node *root, const char *file)
{
    ir = fopen(file, "w");
    if (!ir)
    {
        perror("open ir");
        exit(1);
    }
    for (int i = 0; i < root->kid_cnt; ++i)
        if (IS(root->kids[i], "FuncDef"))
            gen_func(root->kids[i]);
    fclose(ir);
}
