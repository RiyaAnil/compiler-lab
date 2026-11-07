
%{
#include "y.tab.h"
%}

%%
"switch"                return SWITCH;
"case"                  return CASE;
"default"               return DEFAULT;
"break"                 return BREAK;
[a-zA-Z_][a-zA-Z0-9]*   return ID;
[0-9]+                  return NUM;
[=]                     return '=';
[(){}:;]                return yytext[0];
[ \t\n]+                ;
.                       return INVALID;
%%

int yywrap() { return 1; }
