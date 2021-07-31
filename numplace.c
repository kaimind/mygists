#include <stdio.h>
#include <time.h>

void display(int t[])
{
    int i, j = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%d, ", t[i * 9 + j]);
        }
        printf("\n");
    }
}

int emptyIndex(int t[])
{
    int i, j, k = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            k = i * 9 + j;
            if (t[k] == 0)
            {
                return k;
            }
        }
    }

    return -1;
}

void inLine(int t[], int p[], int e)
{
    int i, j, k = 0;
    j = e - e % 9;
    for (i = 0; i < 9; i++)
    {
        k = t[i + j];
        if (k > 0)
        {
            p[k - 1] = 0;
        }
    }
}

void inRow(int t[], int p[], int e)
{
    int i, j, k = 0;
    j = e % 9;
    for (i = 0; i < 9; i++)
    {
        k = t[i * 9 + j];
        if (k > 0)
        {
            p[k - 1] = 0;
        }
    }
}

void inBlock(int t[], int p[], int e)
{
    int i, j, k, m, n = 0;

    m = e / 9;
    n = e % 9;

    m = m - m % 3;
    n = n - n % 3;

    for (i = m; i < m + 3; i++)
    {
        for (j = n; j < n + 3; j++)
        {
            k = t[i * 9 + j];
            if (k > 0)
            {
                p[k - 1] = 0;
            }
        }
    }
}

int solve(int t[])
{
    int i, e = 0;

    e = emptyIndex(t);
    if (e >= 0)
    {
        int p[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

        inRow(t, p, e);
        inLine(t, p, e);
        inBlock(t, p, e);

        for (i = 0; i < 9; i++)
        {
            if (p[i] != 0)
            {
                t[e] = i + 1;

                if (solve(t) == 0)
                {
                    return 0;
                }
            }
        }

        t[e] = 0;
        return 1;
    }

    return 0;
}

int main(void)
{
    int s;
    double dly;
    clock_t start, end;

    int t[81] = {
        8, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 3, 6, 0, 0, 0, 0, 0,
        0, 7, 0, 0, 9, 0, 2, 0, 0,
        0, 5, 0, 0, 0, 7, 0, 0, 0,
        0, 0, 0, 0, 4, 5, 7, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 3, 0,
        0, 0, 1, 0, 0, 0, 0, 6, 8,
        0, 0, 8, 5, 0, 0, 0, 1, 0,
        0, 9, 0, 0, 0, 0, 4, 0, 0};

    printf("--------question-------\n");
    display(t);

    start = clock();
    s = solve(t);
    end = clock();

    if (s == 0)
    {
        printf("--------answer----------\n");
        display(t);
    }
    else
    {
        printf("no answer!\n");
    }

    dly = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("-----------------------\n");
    printf("time using: %lf\n", dly);

    return 0;
}
