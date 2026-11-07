
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS

%%
input : expr '\n' { printf("Result = %d\n", $1); }
      ;

expr  : expr '+' expr { $$ = $1 + $3; }
      | expr '-' expr { $$ = $1 - $3; }
      | expr '*' expr { $$ = $1 * $3; }
      | expr '/' expr {
            if ($3 == 0) {
                printf("Division by zero\n");
                YYABORT;
            }
            $$ = $1 / $3;
        }
      | '-' expr %prec UMINUS { $$ = -$2; }
      | '(' expr ')' { $$ = $2; }
      | NUMBER { $$ = $1; }
      ;
%%

void yyerror(const char *s) {
    printf("Invalid expression\n");
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}
