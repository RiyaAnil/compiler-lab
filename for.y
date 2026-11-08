
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token FOR ID NUM INC DEC EQ NE LE GE INVALID

%%

program : /* empty */
        | program statement
        ;
        
statement : FOR '(' init ';' cond ';' update ')' stmt
          { printf("Valid FOR statement\n"); }
        ;

init : ID '=' expr
     | /* empty */
     ;

cond : expr relop expr
     | expr
     | /* empty */
     ;

update : ID INC
       | ID DEC
       | INC ID
       | DEC ID
       | ID '=' expr
       | /* empty */
       ;

stmt : ';'
     | ID '=' expr ';'
     | ID INC ';'
     | ID DEC ';'
     | '{' stmt_list '}'
     ;

stmt_list : stmt_list stmt
          | /* empty */
          ;

relop : '<' | '>' | EQ | NE | LE | GE;

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
    printf("Invalid FOR statement\n");
}

int main() {
    printf("Enter a FOR statement:\n");
    yyparse();
    return 0;
}
