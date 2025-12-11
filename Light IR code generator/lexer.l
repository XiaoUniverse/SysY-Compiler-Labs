
%{
#include "parser.tab.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int yylex();
extern char* yytext;

%}

%option yylineno
%option noyywrap

D [0-9]
L [a-zA-Z_]
H [a-fA-F0-9]
E [Ee][+-]?{D}+ 
FS (f|F|l|L)
IS (u|U|l|L)*

%%

"int"       { return INT; }
"void"      { return VOID; }
"return"    { return RETURN; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"float"     { return FLOAT; }
"const"     { return CONST; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }

"("         { return LP; }
")"         { return RP; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
"["         { return LBRACK; }
"]"         { return RBRACK; }
";"         { return SEMI; }
","         { return COMMA; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return MOD; }
"="         { return ASSIGN; }
"!"         { return NOT; }

"<"         { return LT; }
">"         { return GT; }
"=="        { return EQ; }
"!="        { return NE; }
"<="        { return LE; }
">="        { return GE; }
"&&"        { return LAND; }
"||"        { return LOR; }



{L}({L}|{D})* {
    yylval.string = strdup(yytext);
    return ID;
}


{D}+{IS}? {
    yylval.string = strdup(yytext);
    return INT_CONST;
}


{D}+{E}{FS}? {
    yylval.string =strdup(yytext);
    return FLOAT_CONST;
}


{D}+"."{D}*({E})?{FS}? {
    yylval.string =strdup(yytext);
    return FLOAT_CONST;
}

0[xX]{H}+{IS}? {
    yylval.string = strdup(yytext);
    return INT_CONST;
}

\"(\\.|[^\\\"])*\" {
    yylval.string = strdup(yytext);
    return STRING; 
}


"//".*        { /* ignore */ }

"/*"([^*]|\*+[^*/])*\*+"/" { /* ignore */ }

[ \t\n\r]+    { /* ignore */ }

.             { printf("UNKNOWN: %s\n", yytext); }

%%
