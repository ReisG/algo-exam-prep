#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(a, b) (a^=b, b^=a, a^=b)
char *fibocci(char* s)
{
    int cap = 10;
    int sz = 0;
    char *res = malloc(cap);

    int i = 0;
    int p = 1, n = 0;
    for (; s[i] != '\0'; p = p+n, swap(n, p))
    {
        if (i > n) continue;
        do
        {
            if (sz == cap) res = realloc(res, cap <<= 1);
            res[sz++] = s[i];
        } while (i++ != n && s[i] != '\0');

        if (s[i] != '\0')
        {
            if (sz == cap) res = realloc(res, cap <<= 1);
            res[sz++] = ' ';
        }
    }

    if (sz == cap) res = realloc(res, cap <<= 1);
    res[sz++] = s[i];
    res = realloc(res, cap = sz);

    free(s);
    return res;
}

int main(void)
{
    char *res = malloc(1000);
    strcpy(res, "abcdefghijklmnop");
    res = fibocci(res);
    puts(res);
    free(res);
    return 0;
}