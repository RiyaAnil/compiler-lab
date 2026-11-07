
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token IF ELSE ID NUM EQ NE LE GE INC DEC INVALID
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
program : stmt
        ;

stmt : IF '(' cond ')' stmt %prec LOWER_THAN_ELSE
     | IF '(' cond ')' stmt ELSE stmt
     | '{' stmt_list '}'
     | ID '=' expr ';'
     | ID INC ';'
     | ID DEC ';'
     | ';'
     ;

stmt_list : stmt_list stmt
          | /* empty */
          ;

cond : expr relop expr
     | expr
     ;

relop : '<'
      | '>'
      | EQ
      | NE
      | LE
      | GE
      ;

expr : expr '+' term
     | expr '-' term
     | term
     ;

term : term '*' factor
     | term '/' factor
     | term '%' factor
     | factor
     ;

factor : ID
       | NUM
       | '(' expr ')'
       ;
%%

void yyerror(const char *s) {
    printf("Invalid IF statement\n");
}

int main() {
    printf("Enter an IF statement:\n");
    if (yyparse() == 0)
        printf("Valid IF statement\n");
    return 0;
}
