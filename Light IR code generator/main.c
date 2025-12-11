#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"  // 包含由 Bison 生成的头文件

extern Node *ast_root;  // 外部声明 AST 树的根节点
extern void gen_ir(Node *root, const char *file); // 中间代码生成器函数
extern FILE *yyin;
// 打印树的函数 (已定义在 parser.y 文件中)
void print_tree(Node *n, int d);

int main(int argc, char *argv[]) {
    // 检查命令行参数
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source.c>\n", argv[0]);
        return 1;
    }

    // 打开输入文件
    FILE *input_file = fopen(argv[1], "r");  // 使用传入的文件路径
    if (input_file == NULL) {
        perror("Unable to open input file");
        return 1;  // 文件打开失败，退出程序
    }

    // 设置 yyin 为文件
    yyin = input_file;

    // 语法分析，调用 Bison 生成的解析函数
    int parse_result = yyparse();  // 执行语法分析，生成 AST
    if (parse_result != 0) {
        printf("Syntax analysis failed, error code: %d\n", parse_result);
        fclose(input_file);
        return 1;
    }
    printf("Syntax analysis successful, generating intermediate code...\n");

    // 检查 AST 是否生成成功
    if (ast_root == NULL) {
        fprintf(stderr, "AST root is NULL, syntax analysis failed to generate AST.\n");
        fclose(input_file);
        return 1;
    }

    // 生成中间代码并输出到文件
    const char *ir_filename = "output.ll";  // 可以根据需要修改文件名或路径
    gen_ir(ast_root, ir_filename);

    // 打印 output.ll 文件的内容
    printf("\nGenerated Intermediate Code (IR):\n");

    // 打开 output.ll 文件并打印其内容
    FILE *ir_file = fopen(ir_filename, "r");
    if (ir_file == NULL) {
        perror("Unable to open output.ll file");
        fclose(input_file);
        return 1;
    }

    // 逐行读取并打印文件内容
    char line[1024];
    while (fgets(line, sizeof(line), ir_file) != NULL) {
        printf("%s", line);
    }

    // 文件关闭
    fclose(ir_file);
    fclose(input_file);
    free_tree(ast_root);  // 确保释放 AST 树的内存

    return 0;
}



//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//extern int yylineno;
//extern int yylex();
//extern char* yytext;
//extern FILE *yyin;
//
//// 根据 token 数字值返回 token 名称
//const char* get_token_name(int token) {
//    switch (token) {
//        case 258: return "LOWER_THAN_ELSE";
//        case 259: return "ELSE";
//        case 260: return "ID";
//        case 261: return "STRING";
//        case 262: return "INT_CONST";
//        case 263: return "FLOAT_CONST";
//        case 264: return "VOID";
//        case 265: return "INT";
//        case 266: return "FLOAT";
//        case 267: return "CONST";
//        case 268: return "IF";
//        case 269: return "WHILE";
//        case 270: return "RETURN";
//        case 271: return "BREAK";
//        case 272: return "CONTINUE";
//        case 273: return "EQ";
//        case 274: return "NE";
//        case 275: return "LT";
//        case 276: return "GT";
//        case 277: return "LE";
//        case 278: return "GE";
//        case 279: return "ASSIGN";
//        case 280: return "PLUS";
//        case 281: return "MINUS";
//        case 282: return "MUL";
//        case 283: return "DIV";
//        case 284: return "MOD";
//        case 285: return "NOT";
//        case 286: return "LAND";
//        case 287: return "LOR";
//        case 288: return "LP";
//        case 289: return "RP";
//        case 290: return "LBRACE";
//        case 291: return "RBRACE";
//        case 292: return "LBRACK";
//        case 293: return "RBRACK";
//        case 294: return "SEMI";
//        case 295: return "COMMA";
//        default: return "UNKNOWN";
//    }
//}
//
//int main() {
//    int token;
//
//    // 打开输入文件
//    FILE *input_file = fopen("array.c", "r");  // 替换为您的文件路径
//    if (input_file == NULL) {
//        perror("Unable to open file");
//        return 1;  // 文件打开失败，退出程序
//    }
//
//    // 设置 yyin 为文件
//    yyin = input_file;
//
//    // 逐个读取 token 并输出
//    while ((token = yylex()) != 0) {
//        printf("Token: %s\n", get_token_name(token));  // 输出 token 名称
//    }
//
//    // 文件关闭
//    fclose(input_file);
//
//    return 0;
//}

