/* sysy.y */

%error-verbose
%debug

%left PLUS MINUS
%left MUL DIV MOD
%left LOR
%left LAND
%left EQ NE
%left LT LE GT GE
%right UMINUS

%code requires {
#include "ast.h"
}

%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *);

Node *ast_root;
Node* new_node(const char *s){
    Node *n = malloc(sizeof(Node));
    n->name    = strdup(s);
    n->kids    = NULL;
    n->kid_cnt = 0;
    return n;
}
void add_child(Node *p, Node *c){
    p->kids = realloc(p->kids,
                     sizeof(Node*) * (p->kid_cnt + 1));
    p->kids[p->kid_cnt++] = c;
}
void print_tree(Node *n,int d){
    for(int i=0;i<d;i++) printf("   ");
    if(d>0) printf("|-- ");
    if(n->kid_cnt==0) printf("%s\n",n->name);
    else{
        printf("<%s>\n",n->name);
        for(int i=0;i<n->kid_cnt;i++)
            print_tree(n->kids[i],d+1);
    }
}
void free_tree(Node *n){
    for(int i=0;i<n->kid_cnt;i++) free_tree(n->kids[i]);
    free(n->kids);
    free(n->name);
    free(n);
}
extern int yylex(void);
void yyerror(const char *s){
    fprintf(stderr,"Parse error: %s\n",s);
    exit(1);
}
%}

%token <node> ID NUMBER CHAR_CONST STRING
%token VOID INT FLOAT CONST IF ELSE WHILE RETURN BREAK CONTINUE PRINT
%token <node> PLUS   "+"
%token <node> MINUS  "-"
%token <node> MUL    "*"
%token <node> DIV    "/"
%token <node> MOD    "%"
%token <node> EQ     "=="
%token <node> NE     "!="
%token <node> LT     "<"
%token <node> GT     ">"
%token <node> LE     "<="
%token <node> GE     ">="
%token <node> ASSIGN "="
%token <node> NOT    "!"
%token <node> LAND   "&&"
%token <node> LOR    "||"
%token LP RP LBRACE RBRACE LBRACK RBRACK SEMI COMMA
%token <node> OPERATOR

%type <node>
  CompUnit CompUnitItem
  Decl ConstDecl ConstDefList ConstDef ConstInitVal ConstInitValList
  VarDecl VarDefList VarDef InitVal InitValList
  FuncDef FuncFParams FuncFParam FuncRParams
  BType Block BlockItem Item
  ConstSubscriptList SubscriptList LVal NonEmptyConstSubscriptList
  Stmt Exp LOrExp LAndExp EqExp RelExp AddExp MulExp UnaryExp PrimaryExp Cond

%%

CompUnit
  : CompUnitItem
      { ast_root=new_node("CompUnit"); add_child(ast_root,$1); }
  | CompUnit CompUnitItem
      { add_child(ast_root,$2); }
  ;

CompUnitItem
  : FuncDef   { $$=$1; }   
  | Decl      { $$=$1; }
  ;

FuncDef
  : BType ID LP RP Block
      {
        $$ = new_node("FuncDef");
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, new_node("("));
        add_child($$, new_node(")"));
        add_child($$, $5);
      }
  | BType ID LP FuncFParams RP Block
      {
        $$ = new_node("FuncDef");
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, new_node("("));
        add_child($$, $4);
        add_child($$, new_node(")"));
        add_child($$, $6);
      }
;


FuncFParam
  : BType ID
      {
        $$ = new_node("FuncFParam");
        add_child($$, $1);
        add_child($$, $2);
      }
  | BType ID LBRACK RBRACK
      {
        $$ = new_node("FuncFParam");
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, new_node("[]"));
      }
  | BType ID LBRACK RBRACK NonEmptyConstSubscriptList
      {
        $$ = new_node("FuncFParam");
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, new_node("[]"));
        add_child($$, $5);
      }
  ;

Decl
  : ConstDecl { $$=$1; }
  | VarDecl   { $$=$1; }
  ;

ConstDecl
  : CONST BType ConstDefList SEMI
      {
        $$=new_node("ConstDecl");
        add_child($$,new_node("const"));
        add_child($$,$2);
        add_child($$,$3);
        add_child($$,new_node(";"));
      }
  ;

ConstDefList
  : ConstDef                     { $$=new_node("ConstDefList"); add_child($$,$1); }
  | ConstDefList COMMA ConstDef  { $$=$1; add_child($$,$3); }
  ;

ConstDef
  : ID ConstSubscriptList ASSIGN ConstInitVal
      {
        $$=new_node("ConstDef");
        add_child($$, $1);
        add_child($$,$2);
        add_child($$,new_node("="));
        add_child($$,$4);
      }
  ;

ConstInitVal
  : Exp
      { $$=new_node("ConstInitVal"); add_child($$, $1); }
  | LBRACE ConstInitValList RBRACE
      {
        $$=new_node("ConstInitVal");
        add_child($$,new_node("{"));
        add_child($$,$2);
        add_child($$,new_node("}"));
      }
  ;

ConstInitValList
  : ConstInitVal                          { $$=new_node("ConstInitValList"); add_child($$,$1); }
  | ConstInitValList COMMA ConstInitVal   { $$=$1; add_child($$,$3); }
  ;

VarDecl
  : BType VarDefList SEMI
      {
        $$=new_node("VarDecl");
        add_child($$,$1);
        add_child($$,$2);
        add_child($$,new_node(";"));
      }
  ;

VarDefList
  : VarDef
      {
        $$ = new_node("VarDefList");
        add_child($$, $1);
      }
  | VarDefList COMMA VarDef
      {
        $$ = $1;
        add_child($$, new_node(","));  // 显式加上逗号节点
        add_child($$, $3);
      }
;

VarDef
  : ID ConstSubscriptList
      {
        $$ = new_node("VarDef");
        add_child($$, $1);  // 添加变量名
        if ($2 == NULL) {  // 如果 ConstSubscriptList 是空的，加入 epsilon
          Node *epsilon = new_node("epsilon");
          add_child($$, epsilon);
        } else {
          add_child($$, $2);  // 否则，添加 ConstSubscriptList
        }
      }
  | ID ConstSubscriptList ASSIGN InitVal
      {
        $$ = new_node("VarDef");
        add_child($$, $1);
        if ($2 == NULL) {  // 处理空的 ConstSubscriptList
          Node *epsilon = new_node("epsilon");
          add_child($$, epsilon);
        } else {
          add_child($$, $2);
        }
        add_child($$, new_node("="));
        add_child($$, $4);
      }
;

InitVal
  : Exp                               { $$ = new_node("InitVal"); add_child($$, $1); }
  | LBRACE RBRACE                     { $$ = new_node("InitVal"); add_child($$, new_node("{")); add_child($$, new_node("}")); }
  | LBRACE InitValList RBRACE         { $$ = new_node("InitVal"); add_child($$, new_node("{")); add_child($$, $2); add_child($$, new_node("}")); }
;

InitValList
  : InitVal                           { $$ = new_node("InitValList"); add_child($$, $1); }
  | InitValList COMMA InitVal         { $$ = $1; add_child($$, new_node(",")); add_child($$, $3); }
;



FuncFParams
  : FuncFParam
      {
        $$ = new_node("FuncFParams");
        add_child($$, $1);
      }
  | FuncFParams COMMA FuncFParam
      {
        $$ = $1;
        add_child($$, new_node(","));
        add_child($$, $3);
      }
  ;



FuncRParams
  : Exp                          { $$=new_node("FuncRParams"); add_child($$, $1); }
  | FuncRParams COMMA Exp        { $$=$1; add_child($$,new_node(",")); add_child($$,$3); }
  ;

BType
  : VOID   { $$=new_node("BType"); add_child($$,new_node("void")); }
  | INT    { $$=new_node("BType"); add_child($$,new_node("int")); }
  | FLOAT  { $$=new_node("BType"); add_child($$,new_node("float")); }
  ;

Block
  : LBRACE BlockItem RBRACE
      {
        $$=new_node("Block");
        add_child($$,new_node("{"));
        add_child($$,$2);
        add_child($$,new_node("}"));
      }
  ;

BlockItem
  : /* empty */                { $$=new_node("BlockItem"); add_child($$,new_node("epsilon")); }
  | BlockItem Item             { $$=new_node("BlockItem"); add_child($$, $1); add_child($$, $2); }
  ;

Item
  : VarDecl
      {
        Node *d=new_node("Decl");
        add_child(d,$1);
        $$=d;
      }
  | Stmt { $$=$1; }
  ;

ConstSubscriptList
  : /* empty */ {
      $$ = new_node("ConstSubscriptList");
      add_child($$, new_node("epsilon"));  // 确保空的列表添加 epsilon
  }
| LBRACK AddExp RBRACK {
    $$ = new_node("ConstSubscriptList");
    add_child($$, new_node("["));
    
    Node *constexp_node = new_node("ConstExp");
    add_child(constexp_node, $2);  // $2 是 AddExp
    add_child($$, constexp_node);  // 添加整个 ConstExp 节点

    add_child($$, new_node("]"));
}
| ConstSubscriptList LBRACK AddExp RBRACK {
    $$ = $1;
    add_child($$, new_node("["));
    
    Node *constexp_node = new_node("ConstExp");
    add_child(constexp_node, $3);  // $3 是 AddExp
    add_child($$, constexp_node);

    add_child($$, new_node("]"));
}
;

NonEmptyConstSubscriptList
  : LBRACK NUMBER RBRACK
      {
        $$ = new_node("ConstSubscriptList");
        add_child($$, new_node("["));
        add_child($$, new_node("constexp"));  // 打印 constexp
        add_child($$, $2);
        add_child($$, new_node("]"));
      }
  | NonEmptyConstSubscriptList LBRACK NUMBER RBRACK
      {
        add_child($$, new_node("["));
        add_child($$, new_node("constexp"));  // 打印 constexp
        add_child($$, $3);
        add_child($$, new_node("]"));
      }
  ;



SubscriptList
  : /* empty */                         { $$=new_node("SubscriptList"); add_child($$,new_node("epsilon")); }
  | SubscriptList LBRACK Exp RBRACK
      {
        $$=new_node("SubscriptList");
        add_child($$, $1);
        add_child($$, new_node("["));
        add_child($$, $3);
        add_child($$, new_node("]"));
      }
  ;

LVal
  : ID SubscriptList
      {
        $$=new_node("LVal");
        add_child($$, $1);
        add_child($$,$2);
      }
  ;

Stmt
  : ID LP RP SEMI
      {
        $$=new_node("Stmt");
        add_child($$, $1);
        add_child($$, new_node("("));
        add_child($$, new_node(")"));
        add_child($$, new_node(";"));
      }
  | ID LP FuncRParams RP SEMI
      {
        $$=new_node("Stmt");
        add_child($$, $1);
        add_child($$, new_node("("));
        add_child($$,$3);
        add_child($$, new_node(")"));
        add_child($$, new_node(";"));
      }
  | LVal ASSIGN Exp SEMI
      {
        $$=new_node("Stmt");
        add_child($$, $1);
        add_child($$, new_node("="));
        add_child($$, $3);
        add_child($$, new_node(";"));
      }
  | RETURN Exp SEMI
      {
        $$=new_node("Stmt");
        add_child($$, new_node("return"));
        add_child($$,$2);
        add_child($$, new_node(";"));
      }
  | IF LP Cond RP Stmt %prec LOWER_THAN_ELSE
      {
        $$=new_node("Stmt");
        add_child($$, new_node("if"));
        add_child($$, new_node("("));
        add_child($$,$3);
        add_child($$, new_node(")"));
        add_child($$,$5);
      }
  | IF LP Cond RP Stmt ELSE Stmt
      {
        $$=new_node("Stmt");
        add_child($$, new_node("if"));
        add_child($$, new_node("("));
        add_child($$,$3);
        add_child($$, new_node(")"));
        add_child($$,$5);
        add_child($$, new_node("else"));
        add_child($$,$7);
      }
  | WHILE LP Cond RP Stmt
      {
        $$=new_node("Stmt");
        add_child($$, new_node("while"));
        add_child($$, new_node("("));
        add_child($$,$3);
        add_child($$, new_node(")"));
        add_child($$,$5);
      }
  | Block { $$=$1; }
  | BREAK SEMI                       { $$ = new_node("Stmt"); add_child($$, new_node("break")); }
  | CONTINUE SEMI                  { $$ = new_node("Stmt"); add_child($$, new_node("continue")); }
  | SEMI
      {
        $$ = new_node("Stmt");
        add_child($$, new_node(";")); // 表示空语句
      }
  ;

Exp
  : LOrExp                { $$=new_node("Exp"); add_child($$, $1); }
  ;

LOrExp
  : LAndExp               { $$=$1; }
  | LOrExp LOR LAndExp    {
        $$=new_node("LOrExp");
        add_child($$, $1);
        add_child($$, new_node("||"));
        add_child($$, $3);
    }
  ;

LAndExp
  : EqExp                 { $$=$1; }
  | LAndExp LAND EqExp    {
        $$=new_node("LAndExp");
        add_child($$, $1);
        add_child($$, new_node("&&"));
        add_child($$, $3);
    }
  ;

EqExp
  : RelExp                { $$=$1; }
  | EqExp EQ RelExp       {
        $$=new_node("EqExp");
        add_child($$, $1);
        add_child($$, new_node("=="));
        add_child($$, $3);
    }
  | EqExp NE RelExp       {
        $$=new_node("EqExp");
        add_child($$, $1);
        add_child($$, new_node("!="));
        add_child($$, $3);
    }
  ;

RelExp
  : AddExp                { $$=$1; }
  | RelExp LT AddExp      {
        $$=new_node("RelExp");
        add_child($$, $1);
        add_child($$, new_node("<"));
        add_child($$, $3);
    }
  | RelExp LE AddExp      {
        $$=new_node("RelExp");
        add_child($$, $1);
        add_child($$, new_node("<="));
        add_child($$, $3);
    }
  | RelExp GT AddExp      {
        $$=new_node("RelExp");
        add_child($$, $1);
        add_child($$, new_node(">"));
        add_child($$, $3);
    }
  | RelExp GE AddExp      {
        $$=new_node("RelExp");
        add_child($$, $1);
        add_child($$, new_node(">="));
        add_child($$, $3);
    }
  ;

AddExp
  : MulExp                { $$=new_node("AddExp"); add_child($$, $1); }
  | AddExp PLUS MulExp    {
        $$=new_node("AddExp");
        add_child($$, $1);
        add_child($$, new_node("+"));
        add_child($$, $3);
    }
  | AddExp MINUS MulExp   {
        $$=new_node("AddExp");
        add_child($$, $1);
        add_child($$, new_node("-"));
        add_child($$, $3);
    }
  ;

MulExp
  : UnaryExp              { $$=new_node("MulExp"); add_child($$, $1); }
  | MulExp MUL UnaryExp   {
        $$=new_node("MulExp");
        add_child($$, $1);
        add_child($$, new_node("*"));
        add_child($$, $3);
    }
  | MulExp DIV UnaryExp   {
        $$=new_node("MulExp");
        add_child($$, $1);
        add_child($$, new_node("/"));
        add_child($$, $3);
    }
  | MulExp MOD UnaryExp   {
        $$=new_node("MulExp");
        add_child($$, $1);
        add_child($$, new_node("%"));
        add_child($$, $3);
    }
  ;

UnaryExp
  : PrimaryExp
      {
        $$ = new_node("UnaryExp");
        add_child($$, $1);
      }
  | PLUS UnaryExp
      {
        $$ = new_node("UnaryExp");
        add_child($$, new_node("+"));
        add_child($$, $2);
      }
  | MINUS UnaryExp %prec UMINUS
      {
        $$ = new_node("UnaryExp");
        add_child($$, new_node("-"));
        add_child($$, $2);
      }
  | NOT UnaryExp
    {
        $$ = new_node("UnaryExp");
        add_child($$, new_node("!"));
        add_child($$, $2);
    }

;

Cond
  : LOrExp { $$ = new_node("Cond"); add_child($$, $1); }
  ;



PrimaryExp
  : LP Exp RP            {
        $$=new_node("PrimaryExp");
        add_child($$, new_node("("));
        add_child($$, $2);
        add_child($$, new_node(")"));
    }
  | ID LP RP             {
        $$=new_node("PrimaryExp");
        add_child($$, $1);
        add_child($$, new_node("("));
        add_child($$, new_node(")"));
    }
  | ID LP FuncRParams RP {
        $$=new_node("PrimaryExp");
        add_child($$, $1);
        add_child($$, new_node("("));
        add_child($$, $3);
        add_child($$, new_node(")"));
    }
  | LVal                  { $$=new_node("PrimaryExp"); add_child($$, $1); }
| NUMBER {
    $$ = new_node("PrimaryExp");
    Node *n = new_node("Number");
    add_child(n, $1);       // $1 是 "3"
    add_child($$, n);       // 把 Number 加入 PrimaryExp
}
  | STRING    { $$=new_node("PrimaryExp"); add_child($$, $1); }
  | CHAR_CONST { $$=new_node("PrimaryExp"); add_child($$, $1); }
  ;

%%
int yydebug = 1; // 启用 Bison 的调试模式熟悉这个代码 

