
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token VALID INVALID

%%
input : VALID  { printf("Valid variable\n"); }
      | INVALID { printf("Invalid variable\n"); }
      ;
%%

void yyerror(const char *s) {
    printf("Invalid variable\n");
}

int main() {
    printf("Enter a variable: ");
    yyparse();
    return 0;
}
