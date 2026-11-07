
#include <stdio.h>

int main() {
    int n, sym, start;
    int trans[10][5], isFinal[10];
    int group[10], newGroup[10];
    int i, j, k, g;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &sym);

    if (n < 1 || n > 10 || sym < 1 || sym > 5) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter transition table:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < sym; j++)
            scanf("%d", &trans[i][j]);

    printf("Enter final states (1 = final, 0 = non-final):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &isFinal[i]);

    printf("Enter start state: ");
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid start state\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < sym; j++)
            if (trans[i][j] < 0 || trans[i][j] >= n) {
                printf("Invalid transition\n");
                return 1;
            }

    for (i = 0; i < n; i++)
        group[i] = isFinal[i];

    while (1) {
        int numGroups = 0;

        for (i = 0; i < n; i++) {
            int found = -1;

            for (j = 0; j < i; j++) {
                if (group[i] != group[j])
                    continue;

                int same = 1;

                for (k = 0; k < sym; k++) {
                    if (group[trans[i][k]] !=
                        group[trans[j][k]]) {
                        same = 0;
                        break;
                    }
                }

                if (same) {
                    found = newGroup[j];
                    break;
                }
            }

            if (found == -1)
                newGroup[i] = numGroups++;
            else
                newGroup[i] = found;
        }

        int changed = 0;

        for (i = 0; i < n; i++)
            for (j = 0; j < i; j++)
                if ((group[i] == group[j]) !=
                    (newGroup[i] == newGroup[j]))
                    changed = 1;

        for (i = 0; i < n; i++)
            group[i] = newGroup[i];

        if (!changed)
            break;
    }

    int numGroups = 0;

    for (i = 0; i < n; i++)
        if (group[i] + 1 > numGroups)
            numGroups = group[i] + 1;

    printf("\n--- Minimized DFA States ---\n");
    printf("Total minimized states: %d\n\n", numGroups);

    for (g = 0; g < numGroups; g++) {
        int final = 0;

        printf("S%d = { ", g);

        for (i = 0; i < n; i++) {
            if (group[i] == g) {
                printf("q%d ", i);

                if (isFinal[i])
                    final = 1;
            }
        }

        printf("}%s\n", final ? " [FINAL]" : "");
    }

    printf("\n--- Minimized Transition Table ---\n");
    printf("State");

    for (j = 0; j < sym; j++)
        printf("\tsym%d", j);

    printf("\n");

    for (g = 0; g < numGroups; g++) {
        int rep = -1;

        for (i = 0; i < n; i++)
            if (group[i] == g) {
                rep = i;
                break;
            }

        printf("S%d", g);

        for (j = 0; j < sym; j++)
            printf("\tS%d", group[trans[rep][j]]);

        printf("\n");
    }

    printf("\nStart state: S%d\n", group[start]);

    return 0;
}
