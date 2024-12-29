#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 101

int main(void)
{
    freopen("input.txt", "r", stdin);
    int cap = 10;
    int sz = 0;
    char **vec = malloc(cap*sizeof(char*));

    char user[STRLEN];
    while (scanf("%s", user) == 1)
    {
        if (sz == cap) vec = realloc(vec, (cap <<= 1) * sizeof(char*));
        vec[sz] = malloc(STRLEN*sizeof(char));
        strcpy(vec[sz++], user);
    }

    for (int i = 1; i < sz; i+=2) puts(vec[i]), free(vec[i]);
    for (int i = sz - 1 - (~sz&1); i >= 0; i-= 2) puts(vec[i]), free(vec[i]);
    free(vec);
    return 0;
}