
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {
    "int", "float", "char", "if", "else",
    "while", "for", "return", "void"
};

int isKeyword(char word[]) {
    int i;

    for (i = 0; i < 9; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main() {
    char input[5000], token[100];
    int i = 0, j, line = 1, ch;

    printf("Enter source code (Ctrl+D to end):\n");

    /* Read multiple lines */
    while ((ch = getchar()) != EOF && i < 4999)
        input[i++] = ch;

    input[i] = '\0';
    i = 0;

    while (input[i] != '\0') {

        if (input[i] == '\n') {
            line++;
            i++;
        }
        else if (isspace((unsigned char)input[i])) {
            i++;
        }
        else if (isalpha((unsigned char)input[i]) ||
                 input[i] == '_') {

            j = 0;

            while (isalnum((unsigned char)input[i]) ||
                   input[i] == '_') {
                if (j < 99)
                    token[j++] = input[i];
                i++;
            }

            token[j] = '\0';

            if (isKeyword(token))
                printf("%s : Keyword\n", token);
            else
                printf("%s : Identifier\n", token);
        }
        else if (isdigit((unsigned char)input[i])) {

            j = 0;

            while (isdigit((unsigned char)input[i]) ||
                   input[i] == '.') {
                if (j < 99)
                    token[j++] = input[i];
                i++;
            }

            token[j] = '\0';
            printf("%s : Number\n", token);
        }
        else if (strchr("+-*/%=<>!", input[i])) {
            printf("%c : Operator\n", input[i]);
            i++;
        }
        else if (strchr(";,(){}[]", input[i])) {
            printf("%c : Special symbol\n", input[i]);
            i++;
        }
        else {
            printf("%c : Unknown symbol\n", input[i]);
            i++;
        }
    }

    return 0;
}

