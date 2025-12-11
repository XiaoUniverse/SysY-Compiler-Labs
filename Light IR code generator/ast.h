#ifndef AST_H
#define AST_H

/* AST 节点类型 */
typedef struct Node {
    char *name;
    struct Node **kids;
    int    kid_cnt;
} Node;

/* AST 操作函数*/
Node* new_node(const char *name);
void  add_child(Node *p, Node *c);
void  print_tree(Node *n, int depth);
void  free_tree(Node *n);

/* 由 parser 填充 */
extern Node *ast_root;

#endif // AST_H
