
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token WHILE IF ELSE BREAK CONTINUE
%token ID NUM EQ LE GE NE INC DEC INVALID
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
program : stmt
        ;

stmt : WHILE '(' cond ')' stmt
     | '{' stmt_list '}'
     | ID '=' expr ';'
     | ID INC ';'
     | ID DEC ';'
     | BREAK ';'
     | CONTINUE ';'
     | ';'
     | IF '(' cond ')' stmt %prec LOWER_THAN_ELSE
     | IF '(' cond ')' stmt ELSE stmt
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
      | LE
      | GE
      | NE
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
    printf("Invalid WHILE statement\n");
}

int main() {
    printf("Enter a WHILE statement:\n");
    if (yyparse() == 0)
        printf("Valid WHILE statement\n");
    return 0;
}
