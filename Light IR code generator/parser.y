%code top {
#define YYDEBUG 1
}


%code requires {
#include "ast.h"
}

%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern char *yytext;


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
    if (!n) return;
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
    fprintf(stderr, "Parse error on line %d: %s, token = %s\n", yylineno, s, yytext);
    exit(1);
}
%}

/* 解决 dangling-else */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%union {
    char *string;
    Node *node;
}

%token <string> ID STRING INT_CONST FLOAT_CONST
%token VOID INT FLOAT CONST IF ELSE WHILE RETURN BREAK CONTINUE
%token EQ NE LT GT LE GE ASSIGN PLUS MINUS MUL DIV MOD NOT LAND LOR
%token LP RP LBRACE RBRACE LBRACK RBRACK SEMI COMMA 

%type <node>
  CompUnit CompUnitItem
  Decl ConstDecl ConstDefList ConstDef ConstInitVal ConstInitValList
  VarDecl VarDefList VarDef InitVal InitValList
  FuncDef FuncFParams FuncFParam FuncRParams
  BType Block BlockItem Item
  ConstSubscriptList LVal
  Stmt Exp LOrExp LAndExp EqExp RelExp AddExp MulExp UnaryExp PrimaryExp
  ConstExp NUMBER ExpList FuncType

%start CompUnit

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
  : FuncType ID LP FuncFParams RP Block
      {
        $$=new_node("FuncDef");
        add_child($$,$1);
        add_child($$,new_node($2));
        add_child($$,new_node("("));
        add_child($$,$4);
        add_child($$,new_node(")"));
        add_child($$,$6);
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

FuncType
  :VOID                           {$$=new_node("FuncType");add_child($$,new_node("VOID"));}
  |INT                            {$$=new_node("FuncType");add_child($$,new_node("INT"));}
  |FLOAT                          {$$=new_node("FuncType");add_child($$,new_node("FLOAT"));}
  ;

BType
  : INT    { $$=new_node("BType"); add_child($$,new_node("int")); }
  | FLOAT  { $$=new_node("BType"); add_child($$,new_node("float")); }
  ;


ConstDefList
  : ConstDef                     { $$=new_node("ConstDefList"); add_child($$,$1); }
  | ConstDefList COMMA ConstDef  { $$=$1; add_child($$,$3); }
  ;

ConstDef
  : ID ConstSubscriptList ASSIGN ConstInitVal
      {
        $$=new_node("ConstDef");
        add_child($$,new_node($1));
        add_child($$,$2);
        add_child($$,new_node("="));
        add_child($$,$4);
      }
  ;

ConstSubscriptList
  : /* empty */                         { $$=new_node("ConstSubscriptList"); add_child($$,new_node("epsilon")); }
  | ConstSubscriptList LBRACK ConstExp RBRACK
      {
        $$=new_node("ConstSubscriptList");
        add_child($$, $1);
        add_child($$, new_node("["));
        add_child($$, $3);
        add_child($$, new_node("]"));
      }
  ;

ConstInitVal
  : ConstExp
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
  : /* empty */                          { $$=new_node("ConstInitValList"); add_child($$,new_node("epsilon")); }
  |ConstInitVal                          { $$=new_node("ConstInitValList"); add_child($$,$1); }
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
  : VarDef                        { $$=new_node("VarDefList"); add_child($$,$1); }
  | VarDefList COMMA VarDef       { $$=$1; add_child($$,$3); }
  ;

VarDef
  : ID ConstSubscriptList
      {
        $$=new_node("VarDef");
        add_child($$,new_node($1));
        add_child($$,$2);
      }
  | ID ConstSubscriptList ASSIGN InitVal
      {
        $$=new_node("VarDef");
        add_child($$,new_node($1));
        add_child($$,$2);
        add_child($$,new_node("="));
        add_child($$,$4);
      }
  ;

InitVal
  : Exp
      { $$=new_node("InitVal"); add_child($$, $1); }
  | LBRACE InitValList RBRACE
      {
        $$=new_node("InitVal");
        add_child($$,new_node("{"));
        add_child($$,$2);
        add_child($$,new_node("}"));
      }
  ;

InitValList
  : /* empty */                   { $$=new_node("InitValList"); add_child($$,new_node("epsilon")); }
  | InitVal                       { $$=new_node("InitValList"); add_child($$,$1); }
  | InitValList COMMA InitVal     { $$=$1; add_child($$,$3); }
  ;





FuncFParams
  : /* empty */                     { $$=new_node("FuncFParams"); add_child($$,new_node("epsilon")); }
  | FuncFParams COMMA FuncFParam   { $$=$1; add_child($$,new_node(",")); add_child($$,$3); }
  | FuncFParam                     { $$=new_node("FuncFParams"); add_child($$, $1); }
  ;

FuncFParam
  : BType ID
      {
        $$=new_node("FuncFParam");
        add_child($$,$1);
        add_child($$,new_node($2));
      }
  | BType ID LBRACK RBRACK ExpList
      {
        $$=new_node("FuncFParam");
        add_child($$,$1);
        add_child($$,new_node($2));
        add_child($$,new_node("["));
        add_child($$,new_node("]"));
        add_child($$,$5);
      }
  ;

ExpList
  : /* empty */                  {$$=new_node("ExpList");  add_child($$,new_node("epsilon"));}
  | ExpList LBRACK Exp RBRACK
    {
      $$ = $1;
      add_child($$, new_node("("));
      add_child($$, $3);
      add_child($$, new_node(")"));
    }

  ;


FuncRParams
  : Exp                          { $$=new_node("FuncRParams"); add_child($$, $1); }
  | FuncRParams COMMA Exp        { $$=$1; add_child($$,new_node(",")); add_child($$,$3); }
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
  : Decl { $$=$1;}
  | Stmt { $$=$1; }
  ;

Stmt
  : LVal ASSIGN Exp SEMI
      {
        $$=new_node("Stmt");
        add_child($$, $1);
        add_child($$, new_node("="));
        add_child($$, $3);
        add_child($$, new_node(";"));
      }
  
  | Exp SEMI
      {
        $$=new_node("Stmt");
        add_child($$, $1);
        add_child($$, new_node(";"));
      }

  | SEMI
      {
        $$=new_node("Stmt");
        add_child($$, new_node(";"));
      }

  | Block 
       { 
        $$=new_node("Stmt");
        add_child($$,$1);
       }

  | IF LP LOrExp RP Stmt %prec LOWER_THAN_ELSE
      {
        $$=new_node("Stmt");
        add_child($$, new_node("if"));
        add_child($$, new_node("("));
        add_child($$,$3);
        add_child($$, new_node(")"));
        add_child($$,$5);
      }
  | IF LP LOrExp RP Stmt ELSE Stmt
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
   | WHILE LP LOrExp RP Stmt
      {
        $$=new_node("Stmt");
        add_child($$, new_node("while"));
        add_child($$, new_node("("));
        add_child($$,$3);
        add_child($$, new_node(")"));
        add_child($$,$5);
      }

  
  | BREAK SEMI
      {
        $$=new_node("Stmt");
        add_child($$, new_node("break"));
        add_child($$, new_node(";"));
      }

  | CONTINUE SEMI
      {
        $$=new_node("Stmt");
        add_child($$, new_node("continue"));
        add_child($$, new_node(";"));
      }

  | RETURN Exp SEMI
      {
        $$=new_node("Stmt");
        add_child($$, new_node("return"));
        add_child($$,$2);
        add_child($$, new_node(";"));
      }
  | RETURN SEMI
      {
        $$=new_node("Stmt");
        add_child($$, new_node("return"));
        add_child($$, new_node(";"));
      }
  ;
  
LVal
  : ID ExpList
      {
        $$=new_node("LVal");
        add_child($$,new_node($1));
        add_child($$,$2);
      }
  ;

Exp
  : AddExp                { $$=new_node("Exp"); add_child($$, $1); }
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
  : PrimaryExp            { $$=new_node("UnaryExp"); add_child($$, $1); }
  | PLUS UnaryExp        {
        $$=new_node("UnaryExp");
        add_child($$, new_node("+"));
        add_child($$, $2);
    }
  | MINUS UnaryExp       {
        $$=new_node("UnaryExp");
        add_child($$, new_node("-"));
        add_child($$, $2);
    }
  | NOT UnaryExp
    {
      $$=new_node("UnaryExp");
      add_child($$, new_node("!"));
      add_child($$, $2);
    } 
  | ID LP RP
    {
       $$=new_node("UnaryExp");
       add_child($$,new_node($1));
       add_child($$,new_node("("));
       add_child($$,new_node(")"));
    }
  
  | ID LP FuncRParams RP
    {
       $$=new_node("UnaryExp");
       add_child($$,new_node($1));
       add_child($$,new_node("("));
       add_child($$,$3);
       add_child($$,new_node(")"));
    }
  ;

PrimaryExp
  : LP Exp RP            {
        $$=new_node("PrimaryExp");
        add_child($$, new_node("("));
        add_child($$, $2);
        add_child($$, new_node(")"));
    }
  | LVal                  { $$=new_node("PrimaryExp"); add_child($$, $1); }
  | NUMBER                {
        $$=new_node("PrimaryExp");
        add_child($$,$1);
    }
  ;

NUMBER
  : INT_CONST             {$$=new_node("NUMBER");add_child($$,new_node($1));}
  | FLOAT_CONST           {$$=new_node("NUMBER");add_child($$,new_node($1));}

ConstExp
  : AddExp                {$$=new_node("ConstExp");add_child($$,$1);}

%%
