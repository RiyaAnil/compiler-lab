
%{
#include "y.tab.h"
%}

%%
"for"                   return FOR;
[a-zA-Z_][a-zA-Z0-9]*    return ID;
[0-9]+                  return NUM;
"++"                    return INC;
"--"                    return DEC;
"=="                    return EQ;
"!="                    return NE;
"<="                    return LE;
">="                    return GE;
[=<>+\-*/%]             return yytext[0];
[(){};]                 return yytext[0];
[ \t\r\n]+              ;
.                       return INVALID;
%%

int yywrap() { return 1; }
