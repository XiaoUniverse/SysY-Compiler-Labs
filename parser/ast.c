#include "ast.h"
#include <stdio.h>

#include "ast.h"
#include <stdio.h>
#include <string.h>

void print_ast_to_file(Node* node, int depth, FILE* fp) {
    static int last[100] = {0}; // 标记每一层是不是最后一个节点

    for (int i = 0; i < depth - 1; ++i) {
        if (last[i])
            fprintf(fp, "    ");
        else
            fprintf(fp, "│   ");
    }

    if (depth > 0) {
        if (last[depth - 1])
            fprintf(fp, "└── ");
        else
            fprintf(fp, "├── ");
    }

    if (node->kid_cnt > 0)
        fprintf(fp, "<%s>\n", node->name);
    else
        fprintf(fp, "%s\n", node->name);

    for (int i = 0; i < node->kid_cnt; ++i) {
        last[depth] = (i == node->kid_cnt - 1); // 当前节点是否是最后一个孩子
        print_ast_to_file(node->kids[i], depth + 1, fp);
    }
}


