
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *left, *right;
} Node;

Node *root;

Node *create(char *v, Node *l, Node *r) {
    Node *n = malloc(sizeof(Node));
    n->value = strdup(v);
    n->left = l;
    n->right = r;
    return n;
}

void print(Node *n, int level) {
    if (!n) return;

    for (int i = 0; i < level; i++)
        printf(" ");

    printf("%s\n", n->value);
    print(n->left, level + 1);
    print(n->right, level + 1);
}

int yylex(void);
int yyerror(const char *s);
%}

%union {
    char *str;
    struct Node *node;
}

%token <str> ID
%type <node> E T F

%left '+' '-'
%left '*' '/'

%%

input:
    E'\n' { root = $1; }
    ;

E:
      E '+' T { $$ = create("+", $1, $3); }
    | E '-' T { $$ = create("-", $1, $3); }
    | T       { $$ = $1; }
    ;

T:
      T '*' F { $$ = create("*", $1, $3); }
    | T '/' F { $$ = create("/", $1, $3); }
    | F       { $$ = $1; }
    ;

F:
      '(' E ')' { $$ = $2; }
    | ID        { $$ = create($1, NULL, NULL); }
    ;

%%

int main() {
    printf("Enter expression: ");

    if (yyparse() == 0) {
        printf("\nAbstract Syntax Tree:\n");
        print(root, 0);
    }

    return 0;
}

int yyerror(const char *s) {
    printf("Invalid expression\n");
    return 0;
}

