
%{
#include "y.tab.h"
%}

%%
"while"                 return WHILE;
[a-zA-Z_][a-zA-Z0-9]*   return ID;
[0-9]+                  return NUM;
"=="                    return EQ;
"<="                    return LE;
">="                    return GE;
"!="                    return NE;
"++"                    return INC;
"--"                    return DEC;
[=<>+\-*/]              return yytext[0];
[();{}]                 return yytext[0];
[ \t\n]+                ;
.                       return INVALID;
%%

int yywrap() { return 1; }
