
%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

typedef struct Node {
    char value[20];
    struct Node *left, *right;
} Node;

Node *makeNode(char *value, Node *l, Node *r) {
    Node *n = malloc(sizeof(Node));
    snprintf(n->value, sizeof(n->value), "%s", value);
    n->left = l;
    n->right = r;
    return n;
}

Node *makeNum(int n) {
    char s[20];
    snprintf(s, sizeof(s), "%d", n);
    return makeNode(s, NULL, NULL);
}

void printTree(Node *n, int level) {
    int i;
    if (!n) return;
    for (i = 0; i < level; i++) printf("  ");
    printf("%s\n", n->value);
    printTree(n->left, level + 1);
    printTree(n->right, level + 1);
}
%}

%union {
    int num;
    Node *node;
}

%token <num> NUMBER
%type <node> E T F
%left '+' '-'
%left '*' '/'

%%
input : E { printf("Abstract Syntax Tree:\n"); printTree($1, 0); }
      ;

E : E '+' T { $$ = makeNode("+", $1, $3); }
  | E '-' T { $$ = makeNode("-", $1, $3); }
  | T       { $$ = $1; }
  ;

T : T '*' F { $$ = makeNode("*", $1, $3); }
  | T '/' F { $$ = makeNode("/", $1, $3); }
  | F       { $$ = $1; }
  ;

F : '(' E ')' { $$ = $2; }
  | NUMBER    { $$ = makeNum($1); }
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
