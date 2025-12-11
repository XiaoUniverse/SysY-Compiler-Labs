#ifndef AST_H
#define AST_H

#include <stdio.h>

typedef struct Node {
    char* name;
    int kid_cnt;
    struct Node** kids;
} Node;

Node* new_node(const char* name);
Node* create_node(const char* name, int child_count, ...);
void add_child(Node* parent, Node* child);
void print_ast(Node* root, int indent);
void free_tree(Node* root);
void print_ast_to_file(Node* node, int depth, FILE* fp);


#endif
