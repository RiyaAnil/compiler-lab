
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token SWITCH CASE DEFAULT BREAK ID NUM INVALID

%%
stmt : SWITCH '(' ID ')' '{' cases default_opt '}'
       { printf("Valid SWITCH statement\n"); }
     ;

cases : cases CASE NUM ':' statements
      | /* empty */
      ;

default_opt : DEFAULT ':' statements
            | /* empty */
            ;

statements : statements statement
           | /* empty */
           ;

statement : BREAK ';'
          | ID '=' NUM ';'
          | ';'
          ;
%%

void yyerror(const char *s) {
    printf("Invalid SWITCH statement\n");
}

int main() {
    printf("Enter a SWITCH statement:\n");
    yyparse();
    return 0;
}
