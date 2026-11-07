
%{
#include <stdio.h>
%}

%%
.*riya.*    { printf("Rejected\n"); }
.*          { printf("Accepted\n"); }
\n          ;
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}
