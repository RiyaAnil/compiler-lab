
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {
    "int", "float", "char", "if", "else",
    "while", "for", "return", "void"
};

int isKeyword(char *word) {
    int i;
    for (i = 0; i < 9; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

int main() {
    char input[1000], token[100];
    int i = 0, j, line = 1;

    printf("Enter the source code (Ctrl+D to end):\n");

    while (fgets(token, sizeof(token), stdin)) {
        /* Read complete input below using character scanning */
        break;
    }

    strcpy(input, token);

    while (input[i] != '\0') {
        if (input[i] == '\n') {
            line++;
            i++;
        } else if (isspace((unsigned char)input[i])) {
            i++;
        } else if (isalpha((unsigned char)input[i]) ||
                   input[i] == '_') {
            j = 0;
            while (isalnum((unsigned char)input[i]) ||
                   input[i] == '_')
                token[j++] = input[i++];
            token[j] = '\0';

            printf("%s : %s\n", token,
                   isKeyword(token) ? "Keyword" : "Identifier");
        } else if (isdigit((unsigned char)input[i])) {
            j = 0;
            while (isdigit((unsigned char)input[i]) ||
                   input[i] == '.')
                token[j++] = input[i++];
            token[j] = '\0';
            printf("%s : Number\n", token);
        } else if (strchr("+-*/%=<>!", input[i])) {
            printf("%c : Operator\n", input[i++]);
        } else if (strchr(";,(){}[]", input[i])) {
            printf("%c : Special symbol\n", input[i++]);
        } else {
            printf("%c : Unknown symbol\n", input[i++]);
        }
    }

    return 0;
}
