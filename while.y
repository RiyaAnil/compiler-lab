
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token WHILE ID NUM EQ LE GE NE INC DEC INVALID

%%
stmt : WHILE '(' cond ')' body
       { printf("Valid WHILE statement\n"); }
     ;

body : ';'
     | '{' '}'
     | ID '=' expr ';'
     | ID INC ';'
     | ID DEC ';'
     | stmt
     ;

cond : expr relop expr
     ;

relop : '<' | '>' | EQ | LE | GE | NE;

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
       ;
%%

void yyerror(const char *s) {
    printf("Invalid WHILE statement\n");
}

int main() {
    printf("Enter a WHILE statement: ");
    yyparse();
    return 0;
}
