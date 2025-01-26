#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // freopen("input.txt", "r", stdin);
    int cap = 10;
    int sz = 0;
    short user;
    short *vec = malloc(cap * sizeof(short));
    while (scanf("%d", &user) == 1)
    {
        if (sz == cap) vec = realloc(vec, (cap <<= 1)*sizeof(short));
        vec[sz++] = user;
    }

    // we have captured jump
    short jump = vec[--sz];
    vec = realloc(vec, (cap=sz)*sizeof(short));

    int now = 0;
    int steps = 0;
    while (now < sz - 1)
    {
        int go = now + jump;
        while (now < go && go < sz - 1 && vec[go] < vec[go + 1]) go--;
        if (go == now)
        {
            steps = -1;
            break;
        }
        now = go;
        steps++;
    }


    printf("%d\n", steps);
    free(vec);
    return 0;
}