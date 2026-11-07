
%{
#include "y.tab.h"
%}

%%
"switch"                return SWITCH;
"case"                  return CASE;
"default"               return DEFAULT;
"break"                 return BREAK;
"continue"              return CONTINUE;
[a-zA-Z_][a-zA-Z0-9]*   return ID;
[0-9]+                  return NUM;
"=="                    return EQ;
"!="                    return NE;
"<="                    return LE;
">="                    return GE;
[=<>+\-*/%]             return yytext[0];
[(){}:;]                return yytext[0];
[ \t\r\n]+              ;
.                       return INVALID;
%%

int yywrap() { return 1; }
