#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *p;
int tcount = 0, n = 0;

struct
{
    char op[8], a1[20], a2[20], res[20];
} q[50];

void emit(char *op, char *a1, char *a2, char *res)
{
    strcpy(q[n].op, op);
    strcpy(q[n].a1, a1);
    strcpy(q[n].a2, a2);
    strcpy(q[n].res, res);
    n++;
}

void skip()
{
    while (*p == ' ')
        p++;
}

void newtemp(char *t)
{
    sprintf(t, "t%d", ++tcount);
}

void expr(char *r);

void factor(char *r)
{
    int i = 0;
    skip();

    if (*p == '(')
    {
        p++;
        expr(r);
        skip();

        if (*p == ')')
            p++;
    }
    else if (*p == '-')
    {
        char a[20];
        p++;
        factor(a);
        newtemp(r);
        emit("uminus", a, "", r);
    }
    else
    {
        while (isalnum(*p) || *p == '_')
            r[i++] = *p++;

        r[i] = '\0';
    }
}

void term(char *r)
{
    char op[2] = {0}, b[20], t[20];

    factor(r);

    for (skip(); *p == '*' || *p == '/'; skip())
    {
        op[0] = *p++;
        factor(b);
        newtemp(t);
        emit(op, r, b, t);
        strcpy(r, t);
    }
}

void expr(char *r)
{
    char op[2] = {0}, b[20], t[20];

    term(r);

    for (skip(); *p == '+' || *p == '-'; skip())
    {
        op[0] = *p++;
        term(b);
        newtemp(t);
        emit(op, r, b, t);
        strcpy(r, t);
    }
}

int main()
{
    char line[100], lhs[20] = "", res[20];
    char *eq;

    printf("Enter an expression: ");
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';

    p = line;
    eq = strchr(line, '=');

    if (eq)
    {
        *eq = '\0';
        sscanf(line, "%19s", lhs);
        p = eq + 1;
    }

    expr(res);
    skip();

    if (*p != '\0')
    {
        printf("Invalid expression.\n");
        return 1;
    }

    if (eq)
        emit("=", res, "", lhs);

    printf("\nThree Address Code:\n");

    for (int i = 0; i < n; i++)
    {
        if (!strcmp(q[i].op, "="))
            printf("%s = %s\n", q[i].res, q[i].a1);
        else if (!strcmp(q[i].op, "uminus"))
            printf("%s = -%s\n", q[i].res, q[i].a1);
        else
            printf("%s = %s %s %s\n",
                   q[i].res, q[i].a1, q[i].op, q[i].a2);
    }

    printf("\nQuadruples:\n");
    printf("%-6s%-8s%-8s%-8s%-8s\n",
           "No.", "Op", "Arg1", "Arg2", "Result");

    for (int i = 0; i < n; i++)
        printf("%-6d%-8s%-8s%-8s%-8s\n",
               i, q[i].op, q[i].a1, q[i].a2, q[i].res);

    return 0;
}