#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX], stack[MAX];
int top = -1, ip = 0, len;

void show(char action[])
{
    int i;

    printf("$");

    for (i = 0; i <= top; i++)
    {
        if (stack[i] == 'i')
            printf("id");
        else
            printf("%c", stack[i]);
    }

    printf("\t\t");

    for (i = ip; i < len; i++)
    {
        if (input[i] == 'i')
            printf("id");
        else
            printf("%c", input[i]);
    }

    printf("$\t\t%s\n", action);
}

int reduce()
{
    /* E -> id */
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        show("REDUCE E->id");
        return 1;
    }

    /* E -> (E) */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        show("REDUCE E->(E)");
        return 1;
    }

    /* E -> E*E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        show("REDUCE E->E*E");
        return 1;
    }

    /* E -> E+E, unless * is next */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E' &&
        (ip == len || input[ip] != '*'))
    {
        top -= 2;
        stack[top] = 'E';
        show("REDUCE E->E+E");
        return 1;
    }

    return 0;
}

int main()
{
    char str[MAX];
    int i;

    printf("Grammar: E -> E+E | E*E | (E) | id\n");
    printf("Enter expression: ");
    scanf("%99s", str);

    /* Convert id into i */
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'i' && str[i + 1] == 'd')
        {
            input[len++] = 'i';
            i++;
        }
        else
        {
            input[len++] = str[i];
        }
    }

    input[len] = '\0';

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    printf("-----------------------------------------------\n");

    show("INITIAL");

    while (ip < len)
    {
        /* Reduce as much as possible */
        while (reduce())
            ;

        /* Reject adjacent operands */
        if (top >= 0 &&
            (stack[top] == 'E' || stack[top] == ')') &&
            (input[ip] == 'i' || input[ip] == '('))
        {
            printf("String REJECTED.\n");
            return 0;
        }

        /* Shift next symbol */
        stack[++top] = input[ip++];
        show("SHIFT");
    }

    while (reduce())
        ;

    printf("-----------------------------------------------\n");

    if (top == 0 && stack[0] == 'E')
        printf("String ACCEPTED.\n");
    else
        printf("String REJECTED.\n");

    return 0;
}