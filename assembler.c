#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, nv = 0, nc = 0;

char tac[20][50], var[30][10], code[100][40];

void addvar(char *s)
{
    int i;

    if (!isalpha(s[0]))
        return;

    for (i = 0; i < nv; i++)
        if (strcmp(var[i], s) == 0)
            return;

    strcpy(var[nv++], s);
}

void emit(char *s)
{
    strcpy(code[nc++], s);
}

int main()
{
    int i;
    char r[10], a1[10], op[5], a2[10], lbl[10];
    char buf[40], *jmp;

    printf("Enter the no of three address statements:\n");
    scanf("%d", &n);

    printf("Enter the three address code:\n");

    for (i = 0; i < n; i++)
        scanf(" %[^\n]", tac[i]);

    for (i = 0; i < n; i++)
    {
        if (sscanf(tac[i], "if %s %s %s goto %s",
                   a1, op, a2, lbl) == 4)
        {
            addvar(a1);
            addvar(a2);

            if (strcmp(op, "<") == 0)
                jmp = "JL";
            else if (strcmp(op, ">") == 0)
                jmp = "JG";
            else if (strcmp(op, "<=") == 0)
                jmp = "JLE";
            else if (strcmp(op, ">=") == 0)
                jmp = "JGE";
            else if (strcmp(op, "==") == 0)
                jmp = "JE";
            else
                jmp = "JNE";

            sprintf(buf, "\tMOV AX, %s", a1);
            emit(buf);

            sprintf(buf, "\tCMP AX, %s", a2);
            emit(buf);

            sprintf(buf, "\t%s %s", jmp, lbl);
            emit(buf);
        }
        else if (sscanf(tac[i], "goto %s", lbl) == 1)
        {
            sprintf(buf, "\tJMP %s", lbl);
            emit(buf);
        }
        else if (tac[i][strlen(tac[i]) - 1] == ':')
        {
            emit(tac[i]);
        }
        else if (sscanf(tac[i], "%s = %s %s %s",
                        r, a1, op, a2) == 4)
        {
            addvar(r);
            addvar(a1);
            addvar(a2);

            sprintf(buf, "\tMOV AX, %s", a1);
            emit(buf);

            if (op[0] == '+')
            {
                sprintf(buf, "\tADD AX, %s", a2);
                emit(buf);
            }
            else if (op[0] == '-')
            {
                sprintf(buf, "\tSUB AX, %s", a2);
                emit(buf);
            }
            else if (op[0] == '*')
            {
                sprintf(buf, "\tMOV BX, %s", a2);
                emit(buf);
                emit("\tMUL BX");
            }
            else if (op[0] == '/')
            {
                emit("\tMOV DX, 0");

                sprintf(buf, "\tMOV BX, %s", a2);
                emit(buf);

                emit("\tDIV BX");
            }

            sprintf(buf, "\tMOV %s, AX", r);
            emit(buf);
        }
        else if (sscanf(tac[i], "%s = %s", r, a1) == 2)
        {
            addvar(r);
            addvar(a1);

            sprintf(buf, "\tMOV AX, %s", a1);
            emit(buf);

            sprintf(buf, "\tMOV %s, AX", r);
            emit(buf);
        }
    }

    printf("\n8086 Assembly Code:\n");
    printf("DATA SEGMENT\n");

    for (i = 0; i < nv; i++)
        printf("\t%s DW ?\n", var[i]);

    printf("DATA ENDS\n");
    printf("CODE SEGMENT\n");
    printf("\tASSUME CS:CODE, DS:DATA\n");
    printf("START:\tMOV AX, DATA\n");
    printf("\tMOV DS, AX\n");

    for (i = 0; i < nc; i++)
        printf("%s\n", code[i]);

    printf("\tMOV AH, 4CH\n");
    printf("\tINT 21H\n");
    printf("CODE ENDS\n");
    printf("END START\n");

    return 0;
}