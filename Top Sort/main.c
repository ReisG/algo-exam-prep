/*
Edutorial: http://e-maxx.ru/algo/topological_sort
Task: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1246
*/

#include <stdio.h>
#include <stdlib.h>

struct vector
{
    int sz, cap;
    int *d;
};
typedef struct vector vector;

void pb(vector* t, int v)
{
    if (t->sz == t->cap) t->d = realloc(t->d, (t->cap <<= 1)*sizeof(int));
    t->d[t->sz++] = v;
}

void dfs(int v, vector *g, char *used, int *ord, int *sz)
{
    used[v]++;
    for (int i = 0; i < g[v].sz; i++)
    {
        if (used[g[v].d[i]]) continue;
        dfs(g[v].d[i], g, used, ord, sz);
    }

    ord[(*sz)++] = v + 1;
    return;
}


int main(void)
{
    int n, m;
    
    while(scanf("%d%d", &n, &m), n || m)
    {
        vector *g = calloc(n, sizeof(vector));
        int u, v;
        while (m--)
        {
            scanf("%d%d", &u, &v);
            u--, v--;
            pb(g + u, v);
        }

        int *ord = calloc(n, sizeof(int));
        char *used = calloc(n, sizeof(char));
        int sz = 0;
        for (int i = 0; i < n; i++)
        {
            if (used[i]) continue;
            dfs(i, g, used, ord, &sz);
        }

        for (int i = sz - 1; i >= 0; i--)
        {
            printf("%d ", ord[i]);
            free(g[i].d);
        }
        printf("\n");

        free(g);
        free(ord);
        free(used);
    }

    return 0;
}