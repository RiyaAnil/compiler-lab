
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token SWITCH CASE DEFAULT BREAK CONTINUE
%token ID NUM EQ NE LE GE INVALID

%%
program : SWITCH '(' expr ')' '{' cases default_opt '}'
          { /* Valid switch structure */ }
        ;

cases : cases case_block
      | /* empty */
      ;

case_block : CASE const_value ':' stmt_list
           ;

default_opt : DEFAULT ':' stmt_list
            | /* empty */
            ;

const_value : NUM
            | '-' NUM
            ;

stmt_list : stmt_list stmt
          | /* empty */
          ;

stmt : ID '=' expr ';'
     | BREAK ';'
     | CONTINUE ';'
     | ';'
     ;

expr : expr '+' term
     | expr '-' term
     | term
     ;

term : term '*' factor
     | term '/' factor
     | factor
     ;

factor : ID
       | NUM
       | '(' expr ')'
       ;
%%

void yyerror(const char *s) {
    printf("Invalid SWITCH statement\n");
}

int main() {
    printf("Enter a SWITCH statement:\n");
    if (yyparse() == 0)
        printf("Valid SWITCH statement\n");
    return 0;
}
