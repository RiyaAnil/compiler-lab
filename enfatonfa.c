
#include <stdio.h>
#include <string.h>

int n;
int eps[10][10];
int moveA[10][10], moveB[10][10];
int closure[10][10];
int isFinal[10], newFinal[10];
int visited[10];

void dfs(int start, int state) {
    visited[state] = 1;
    closure[start][state] = 1;

    for (int j = 0; j < n; j++)
        if (eps[state][j] && !visited[j])
            dfs(start, j);
}

int main() {
    int i, j;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &eps[i][j]);

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

    for (i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i, i);
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (closure[i][j] && isFinal[j])
                newFinal[i] = 1;

    int newA[10][10] = {0}, newB[10][10] = {0};

    for (i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (closure[i][k]) {
                for (j = 0; j < n; j++) {
                    if (moveA[k][j])
                        newA[i][j] = 1;
                    if (moveB[k][j])
                        newB[i][j] = 1;
                }
            }
        }
    }

    printf("\n--- NFA without epsilon transitions ---\n");
    printf("\nNew Transition Table:\n");
    printf("State\ta\tb\n");

    for (i = 0; i < n; i++) {
        printf("q%d\t{ ", i);
        for (j = 0; j < n; j++)
            if (newA[i][j])
                printf("q%d ", j);

        printf("}\t{ ");
        for (j = 0; j < n; j++)
            if (newB[i][j])
                printf("q%d ", j);

        printf("}\n");
    }

    printf("\nNew Final States: { ");
    for (i = 0; i < n; i++)
        if (newFinal[i])
            printf("q%d ", i);

    printf("}\n");

    return 0;
}
