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


int main(void)
{
    char s[] = "abacaba";
    int *p = pref(s);
    for (int i = 0; i < strlen(s); i++) printf("%d ", p[i]);
    free(p);
    return 0;
}