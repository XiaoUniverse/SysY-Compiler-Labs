#include <stdio.h>
#include "ast.h"

extern FILE* yyin;
extern Node* ast_root;
int yyparse();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("用法：%s <源文件>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("无法打开文件");
        return 1;
    }

    if (yyparse() == 0) {
        printf("语法分析成功，语法树如下：\n\n");

        // ? 输出到终端
        print_ast_to_file(ast_root, 0, stdout);

        // ? 同时输出到文件
        FILE* out = fopen("ast_output.txt", "w");
        if (!out) {
            perror("无法写入语法树文件");
            return 1;
        }
        print_ast_to_file(ast_root, 0, out);
        fclose(out);

        printf("\n语法树也已写入 ast_output.txt\n");
    } else {
        printf("语法分析失败。\n");
    }

    fclose(yyin);
    return 0;
}

