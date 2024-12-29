#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ifs(char* s)
{
    char *res = calloc(10 + strlen(s), 1), *r = res;

    if (s[0] == 0) return res;
    if (s[0] == 'm' || s[0] == 's' || s[0] == 'u')
    {
        strcpy(res, "msu");
        strcat(res, s);
        return r;
    }

    if ('1' <= s[0] && s[0] <= '3')
    {
        strcpy(res, "cmc");
        res++;
    }

    if ('1' <= s[0] && s[0] <= '6')
    {
        strcpy(res, s);
        strcat(res, "cs");
    }

    strcat(res, "chill");
    return r;
}

int main(void)
{
    char s[] = "5ello";
    char *ss = ifs(s);
    puts(ss);

    free(ss);
    return 0;
}