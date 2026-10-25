#include <stdio.h>
#include <string.h>
#include <ctype.h>

char p[20][20], F[26][30], G[26][30];
int n, change;

/* Add a symbol if it is not already present */
int add(char *s, char c)
{
    if (strchr(s, c))
        return 0;

    int l = strlen(s);
    s[l] = c;
    s[l + 1] = '\0';

    return 1;
}

/* Find FIRST of all non-terminals */
void first()
{
    int i, j, k, nullable;

    do
    {
        change = 0;

        for (i = 0; i < n; i++)
        {
            char *s = F[p[i][0] - 'A'];

            for (j = 3; p[i][j]; j++)
            {
                char c = p[i][j];

                if (c == '#')
                {
                    change |= add(s, '#');
                    break;
                }

                if (!isupper(c))
                {
                    change |= add(s, c);
                    break;
                }

                for (k = 0; F[c - 'A'][k]; k++)
                    if (F[c - 'A'][k] != '#')
                        change |= add(s, F[c - 'A'][k]);

                nullable = strchr(F[c - 'A'], '#') != NULL;

                if (!nullable)
                    break;

                if (!p[i][j + 1])
                    change |= add(s, '#');
            }
        }
    } while (change);
}

/* Find FOLLOW of all non-terminals */
void follow()
{
    int i, j, k, nullable;

    add(G[p[0][0] - 'A'], '$');

    do
    {
        change = 0;

        for (i = 0; i < n; i++)
        {
            for (j = 3; p[i][j]; j++)
            {
                char c = p[i][j], *s;

                if (!isupper(c))
                    continue;

                s = G[c - 'A'];
                nullable = 1;

                for (k = j + 1; p[i][k]; k++)
                {
                    char x = p[i][k];

                    if (x == '#')
                        continue;

                    if (!isupper(x))
                    {
                        change |= add(s, x);
                        nullable = 0;
                        break;
                    }

                    for (int t = 0; F[x - 'A'][t]; t++)
                        if (F[x - 'A'][t] != '#')
                            change |= add(s, F[x - 'A'][t]);

                    if (!strchr(F[x - 'A'], '#'))
                    {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable)
                    for (k = 0; G[p[i][0] - 'A'][k]; k++)
                        change |= add(s, G[p[i][0] - 'A'][k]);
            }
        }
    } while (change);
}

/* Display a set */
void print(char *s)
{
    int i;

    printf("{");

    for (i = 0; s[i]; i++)
    {
        if (i)
            printf(", ");

        if (s[i] == '#')
            printf("ε");
        else
            printf("%c", s[i]);
    }

    printf("}\n");
}

int main()
{
    int i;
    char used[26] = {0};

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g. S->AB, A->#):\n");

    for (i = 0; i < n; i++)
    {
        scanf("%19s", p[i]);
        used[p[i][0] - 'A'] = 1;
    }

    first();
    follow();

    printf("\nFIRST and FOLLOW sets:\n");

    for (i = 0; i < 26; i++)
    {
        if (used[i])
        {
            printf("FIRST(%c) = ", 'A' + i);
            print(F[i]);

            printf("FOLLOW(%c) = ", 'A' + i);
            print(G[i]);
        }
    }

    return 0;
}