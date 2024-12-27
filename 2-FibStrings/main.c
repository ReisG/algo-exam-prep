#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(a, b) ((a)^=(b), (b)^=(a), (a)^=(b))

char* fibocci(char *s)
{
    char *r = calloc(strlen(s) + 1, sizeof(char));
    char *rr = r;
    char *ss = s;

    int p = 0, n = 1, t;
    int idx = 1;
    for (idx = 0; *ss != '\0'; idx ^= 1, p = p + n, swap(n, p))
    {
        int r = 0;
        while (r < n && *ss != '\0')
        {
            if (idx & 1) *rr++ = *ss;
            ss++;
            r++;
        }
    }
    *rr = '\0';
    r = realloc(r, sizeof(char)*(strlen(r) + 1));
    free(s);
    return r;
}

int main(void)
{
    char* test = calloc(100, sizeof(char));
    strcpy(test, "abcdefghijklmnop");
    puts(test);
    test = fibocci(test);
    puts(test);
    return 0;
}