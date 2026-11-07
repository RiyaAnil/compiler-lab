
#include <stdio.h>
#include <string.h>

int n;
int moveA[10][10], moveB[10][10];
int isFinal[10];

int dfaSet[1024][10];
int dfaCount = 0;

int findState(int set[10]) {
    for (int i = 0; i < dfaCount; i++) {
        int same = 1;

        for (int j = 0; j < n; j++)
            if (dfaSet[i][j] != set[j])
                same = 0;

        if (same)
            return i;
    }

    memcpy(dfaSet[dfaCount], set, sizeof(int) * n);
    dfaCount++;

    return dfaCount - 1;
}

int main() {
    int i, j, start;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);

    if (n < 1 || n > 10) {
        printf("Invalid number of states\n");
        return 1;
    }

    printf("Enter transition matrix for symbol 'a':\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &moveA[i][j]);

    printf("Enter transition matrix for symbol 'b':\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &moveB[i][j]);

    printf("Enter final states (1 = final, 0 = not final):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &isFinal[i]);

    printf("Enter start state (0-indexed): ");
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid start state\n");
        return 1;
    }

    int startSet[10] = {0};
    startSet[start] = 1;

    findState(startSet);

    int dfaTransA[1024], dfaTransB[1024];
    int done = 0;

    while (done < dfaCount) {
        int setA[10] = {0};
        int setB[10] = {0};

        for (i = 0; i < n; i++) {
            if (dfaSet[done][i]) {
                for (j = 0; j < n; j++) {
                    if (moveA[i][j])
                        setA[j] = 1;

                    if (moveB[i][j])
                        setB[j] = 1;
                }
            }
        }

        dfaTransA[done] = findState(setA);
        dfaTransB[done] = findState(setB);

        done++;
    }

    printf("\n--- DFA States ---\n");

    for (i = 0; i < dfaCount; i++) {
        int isDfaFinal = 0;

        printf("D%d = { ", i);

        for (j = 0; j < n; j++) {
            if (dfaSet[i][j]) {
                printf("q%d ", j);

                if (isFinal[j])
                    isDfaFinal = 1;
            }
        }

        printf("}%s\n", isDfaFinal ? " [FINAL]" : "");
    }

    printf("\n--- DFA Transition Table ---\n");
    printf("State\ta\tb\n");

    for (i = 0; i < dfaCount; i++)
        printf("D%d\tD%d\tD%d\n",
               i, dfaTransA[i], dfaTransB[i]);

    return 0;
}
