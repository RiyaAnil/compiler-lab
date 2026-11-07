
#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 30

char states[MAX][LEN];
int eps[MAX][MAX];
int visited[MAX];

int find_state(char name[]) {
    for (int i = 0; i < MAX; i++) {
        if (strcmp(states[i], name) == 0)
            return i;
    }
    return -1;
}

void epsilon_closure(int s, int n) {
    int stack[MAX], top = -1;

    memset(visited, 0, sizeof(visited));

    visited[s] = 1;
    stack[++top] = s;

    while (top >= 0) {
        int u = stack[top--];

        for (int v = 0; v < n; v++) {
            if (eps[u][v] && !visited[v]) {
                visited[v] = 1;
                stack[++top] = v;
            }
        }
    }

    printf("Epsilon closure of %s = { ", states[s]);

    for (int i = 0; i < n; i++) {
        if (visited[i])
            printf("%s ", states[i]);
    }

    printf("}\n");
}

int main() {
    int n;
    char from[LEN], symbol[LEN], to[LEN];

    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the states:\n");
    for (int i = 0; i < n; i++)
        scanf("%29s", states[i]);

    memset(eps, 0, sizeof(eps));

    printf("Enter transitions (from symbol to).\n");
    printf("Enter -1 to stop:\n");

    while (1) {
        scanf("%29s", from);

        if (strcmp(from, "-1") == 0)
            break;

        scanf("%29s %29s", symbol, to);

        int u = find_state(from);
        int v = find_state(to);

        if (u == -1 || v == -1) {
            printf("Invalid state!\n");
            return 1;
        }

        if (strcmp(symbol, "e") == 0)
            eps[u][v] = 1;
    }

    for (int i = 0; i < n; i++)
        epsilon_closure(i, n);

    return 0;
}
