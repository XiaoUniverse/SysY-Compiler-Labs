%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 1024
char buf[MAX_STR_LEN];
int buf_idx = 0;
int col = 1;          /* 全局列计数器 */
int start_line_num;   /* 词法单元起始行 */
int start_col_num;    /* 词法单元起始列 */

void reset_buf() {
    buf_idx = 0;
    memset(buf, 0, sizeof(buf));
}

void add_char_to_buf(char c) {
    if (buf_idx < MAX_STR_LEN - 1) {
        buf[buf_idx++] = c;
    }
}
%}
%option noyywrap yylineno
%x COMMENT_SINGLE COMMENT_MULTI STRING
%%
"//"                    { BEGIN(COMMENT_SINGLE); }
<COMMENT_SINGLE>\n      { col = 1; BEGIN(INITIAL); }
<COMMENT_SINGLE>.       { col++; }
"/*"                    { BEGIN(COMMENT_MULTI); }
<COMMENT_MULTI>"*/"     { col += 2; BEGIN(INITIAL); }
<COMMENT_MULTI>\n       { col = 1; }
<COMMENT_MULTI>[^*\n]+  { col += yyleng; }
<COMMENT_MULTI>"*"      { col++; }
[ \t\r]+                { col += yyleng; }
\n                      { col = 1; }
"void"                  { printf("(VOID, _)\n"); col += yyleng; }
"int"                   { printf("(INT, _)\n"); col += yyleng; }
"double"                { printf("(DOUBLE, _)\n"); col += yyleng; }
"float"                 { printf("(FLOAT, _)\n"); col += yyleng; }
"const"                 { printf("(CONST, _)\n"); col += yyleng; }
"if"                    { printf("(IF, _)\n"); col += yyleng; }
"else"                  { printf("(ELSE, _)\n"); col += yyleng; }
"while"                 { printf("(WHILE, _)\n"); col += yyleng; }
"return"                { printf("(RETURN, _)\n"); col += yyleng; }
"break"                 { printf("(BREAK, _)\n"); col += yyleng; }
"continue"              { printf("(CONTINUE, _)\n"); col += yyleng; }
"=="                    { printf("(==, _)\n"); col += yyleng; }
"!="                    { printf("(!=, _)\n"); col += yyleng; }
"<="                    { printf("(<=, _)\n"); col += yyleng; }
">="                    { printf("(>=, _)\n"); col += yyleng; }
"&&"                    { printf("(&&, _)\n"); col += yyleng; }
"||"                    { printf("(||, _)\n"); col += yyleng; }
"="                     { printf("(=, _)\n"); col += yyleng; }
"<"                     { printf("(<, _)\n"); col += yyleng; }
">"                     { printf("(>, _)\n"); col += yyleng; }
"!"                     { printf("(!, _)\n"); col += yyleng; }
"+"                     { printf("(+, _)\n"); col += yyleng; }
"-"                     { printf("(-, _)\n"); col += yyleng; }
"*"                     { printf("(*, _)\n"); col += yyleng; }
"/"                     { printf("(/, _)\n"); col += yyleng; }
"%%"                    { printf("(MOD, _)\n"); col += yyleng; }
"^"                     { printf("(^, _)\n"); col += yyleng; }
"("                     { printf("((, _)\n"); col += yyleng; }
")"                     { printf("(), _)\n"); col += yyleng; }
"{"                     { printf("({, _)\n"); col += yyleng; }
"}"                     { printf("(}, _)\n"); col += yyleng; }
"["                     { printf("([, _)\n"); col += yyleng; }
"]"                     { printf("(], _)\n"); col += yyleng; }
","                     { printf("(,, _)\n"); col += yyleng; }
";"                     { printf("(;, _)\n"); col += yyleng; }
\"                      {
    start_line_num = yylineno;
    start_col_num = col;
    reset_buf();
    BEGIN(STRING);
    col += yyleng;
}
<STRING> {
  \"                    {
      BEGIN(INITIAL);
      printf("(STRING, \"%s\")\n", buf);
      col += yyleng;
  }
  \\n                   { add_char_to_buf('\\'); add_char_to_buf('n'); col += 2; }
  \\t                   { add_char_to_buf('\\'); add_char_to_buf('t'); col += 2; }
  \\\"                  { add_char_to_buf('\\'); add_char_to_buf('"'); col += 2; }
  \\\\                  { add_char_to_buf('\\'); add_char_to_buf('\\'); col += 2; }
  \.                    { add_char_to_buf('\\'); add_char_to_buf(yytext[1]); col += 2; }
  \n                    { fprintf(stderr, "Error: 字符串未闭合\n"); exit(1); }
  .                     { add_char_to_buf(yytext[0]); col += 1; }
}

0[xX][0-9a-fA-F]+[uUlL]?    { printf("(NUM, %s)\n", yytext); col += yyleng; }
0[0-7]*[uUlL]?              { printf("(NUM, %s)\n", yytext); col += yyleng; }
[1-9][0-9]*[uUlL]?          { printf("(NUM, %s)\n", yytext); col += yyleng; }
([0-9]*\.[0-9]+([eE][+-]?[0-9]+)?[fF]?)|(\.[0-9]+([eE][+-]?[0-9]+)?[fF]?)|([0-9]+[eE][+-]?[0-9]+[fF]?)  { printf("(NUM, %s)\n", yytext); col += yyleng; }
[a-zA-Z_][a-zA-Z0-9_]*       { printf("(ID, \"%s\")\n", yytext); col += yyleng; }

.                            { fprintf(stderr, "错误：未知字符 '%s' at %d:%d\n", yytext, yylineno, col); exit(1); }
%%
int main(int argc, char **argv) {
    yylex();
    return 0;
}
