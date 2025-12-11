%option noyywrap nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"  
#include "parser.tab.h"     // 一定要包含这个才能识别 yylval 和 token
extern FILE *yyin;
extern int yylineno;        // ✅ 引用而非定义
extern YYSTYPE yylval;
void yyerror(const char *);
%}

%%

\n        { yylineno++; }

[0-9]+L { yylval.node = new_node("LONG_NUMBER"); return NUMBER; }
[0-9]+u { yylval.node = new_node("UNSIGNED_NUMBER"); return NUMBER; }

"int"        { return INT; }
"float"      { return FLOAT; }
"double"     { return FLOAT; }  
"void"       { return VOID; }
"print"      { return PRINT; }   
"return"     { yylval.node = new_node("return"); return RETURN; }
"while"    { yylval.node = new_node(strdup(yytext)); return WHILE; }
"if"       { yylval.node = new_node(strdup(yytext)); return IF; }
"else"     { yylval.node = new_node(strdup(yytext)); return ELSE; }
"break"     { yylval.node = new_node(strdup(yytext)); return BREAK; }
"continue"     { yylval.node = new_node(strdup(yytext)); return CONTINUE; }

[A-Za-z_][A-Za-z0-9_]*  { yylval.node = new_node(strdup(yytext)); return ID; }

0[xX][0-9A-Fa-f]+        { yylval.node = new_node("HEX"); return NUMBER; }

[Ll]?'\\[0-7]{1,3}'       { yylval.node = new_node("CHAR"); return NUMBER; }
[Ll]?'[A-Za-z0-9]'        { yylval.node = new_node("CHAR"); return NUMBER; }

[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?[fF]?    { yylval.node = new_node("FLOAT"); return NUMBER; }
[0-9]+[eE][+-]?[0-9]+[fF]?              { yylval.node = new_node("FLOAT"); return NUMBER; }

[0-9]+[Ll][Uu]?           { yylval.node = new_node("LONG_NUMBER"); return NUMBER; }
[0-9]+[Uu]               { yylval.node = new_node("UNSIGNED_NUMBER"); return NUMBER; }

[0-9]+                  { yylval.node = new_node(strdup(yytext)); return NUMBER; }

\"[^\"]*\"               { yylval.node = new_node("STRING"); return STRING; }

"="     { return ASSIGN; }
"=="    { return EQ; }
"!="    { return NE; }
"<"     { return LT; }
">"     { return GT; }
"<="    { return LE; }
">="    { return GE; }
"&&"    { return LAND; }
"||"    { return LOR; }

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MUL; }
"/" { return DIV; }
"%" { return MOD; }



"("   { return LP; }
")"   { return RP; }
"{"   { return LBRACE; }
"}"   { return RBRACE; }
"["     { return LBRACK; }
"]"     { return RBRACK; }
";"   { return SEMI; }
","   { return COMMA; }


[ \t\r]+                { /* 忽略空格、制表 */ }
"/*"[^*]*"*"[^/]*"/"     { /* 忽略注释 */ }

%%

