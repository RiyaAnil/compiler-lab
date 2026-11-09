%{
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

[a-zA-Z][a-zA-Z0-9]* {
    yylval.str = strdup(yytext);
    return ID;
}

[0-9]+ {
    yylval.str = strdup(yytext);
    return ID;
}

[ \t]+      ;
\n          { return '\n'; }
[-+*/()]    { return yytext[0]; }
.           { return yytext[0]; }

%%

int yywrap(void) {
    return 1;
}
