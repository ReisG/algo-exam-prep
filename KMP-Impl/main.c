#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* pref(char *s)
{
    int n = strlen(s);
    int *res = calloc(n, sizeof(int));

    for (int i = 1; i < n; i++)
    {
        int j = res[i - 1];
        while (j > 0 && s[i] != s[j]) j = res[j - 1];
        if (s[i] == s[j]) j++;
        res[i] = j;
    }
    return res;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
int *z_func(char *s)
{
    int n = strlen(s);
    int *res = calloc(n, sizeof(int));
    int l, r;
    l = r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i < r) res[i] = min(r - i, res[i - l]);
        while (i + res[i] < n && s[i + res[i]] == s[res[i]]) res[i]++;
        if (i + res[i] > r)
        {
            r = i + res[i];
            l = i;
        }
    }
    return res;
}

int main(void)
{
    char s[] = "abacaba";
    int *p = z_func(s); //pref(s);
    for (int i = 0; i < strlen(s); i++) printf("%d ", p[i]);
    free(p);
    return 0;
}