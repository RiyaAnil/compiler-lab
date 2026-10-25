#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, ip = 0;

char table[8][8] = {
    {'>', '>', '<', '<', '<', '>', '<', '>'},
    {'>', '>', '<', '<', '<', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '<', '>'},
    {'<', '<', '<', '<', '<', '=', '<', ' '},
    {'>', '>', '>', '>', ' ', '>', ' ', '>'},
    {'>', '>', '>', '>', ' ', '>', ' ', '>'},
    {'<', '<', '<', '<', '<', ' ', '<', ' '}
};

int findex(char c)
{
    switch (c)
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case 'i': return 6;
        case '$': return 7;
    }
    return -1;
}

void display()
{
    int i;

    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t%s\n", input + ip);
}

int reduce()
{
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }

    if (top >= 2 &&
        stack[top] == ')' &&
        stack[top - 1] == 'E' &&
        stack[top - 2] == '(')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    if (top >= 2 &&
        stack[top] == 'E' &&
        stack[top - 2] == 'E')
    {
        if (stack[top - 1] == '+' ||
            stack[top - 1] == '-' ||
            stack[top - 1] == '*' ||
            stack[top - 1] == '/')
        {
            top -= 2;
            stack[top] = 'E';
            return 1;
        }
    }

    return 0;
}

int main()
{
    char a, b;
    int i;

    printf("Enter expression (use i for id): ");
    scanf("%s", input);

    strcat(input, "$");
    stack[++top] = '$';

    printf("\nSTACK\t\tINPUT\n");

    while (1)
    {
        i = top;

        while (i >= 0 && stack[i] == 'E')
            i--;

        a = stack[i];
        b = input[ip];

        if (top == 1 &&
            stack[0] == '$' &&
            stack[1] == 'E' &&
            b == '$')
        {
            printf("\nAccepted\n");
            break;
        }

        if (findex(a) == -1 || findex(b) == -1)
        {
            printf("\nRejected\n");
            break;
        }

        if (table[findex(a)][findex(b)] == '<' ||
            table[findex(a)][findex(b)] == '=')
        {
            stack[++top] = b;
            ip++;
            display();
        }
        else if (table[findex(a)][findex(b)] == '>')
        {
            if (!reduce())
            {
                printf("\nRejected\n");
                break;
            }

            display();
        }
        else
        {
            printf("\nRejected\n");
            break;
        }
    }

    return 0;
}