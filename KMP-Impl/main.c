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

// repetition
int *pref2(char *s)
{
    int n = strlen(s);
    int *p = malloc(n*sizeof(int));
    p[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }

    return p;
}

int *z_func2(char *s)
{
    int n = strlen(s);
    int *z = malloc(n*sizeof(int));
    z[0] = 0;
    int l, r;
    l = r = 0;

    for (int i = 1; i < n; i++)
    {
        z[i] = 0;
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r)
        {
            r = i + z[i];
            l = i;
        }
    }

    return z;
}

#define p 29
#define m 1000000123

int *pows;

int *pol_hash(char *s) // size of hash is larger by one
{
    int n = strlen(s) + 1;
    int *h = calloc(n, sizeof(int));
    // primes greater than 256: 251 257 263 269 271 277 281
    // primes greater than 26: 29 31 37 41 43 47 53 59 61 67 71
    // numbers for module for modulo 10^9+7 1000000123 1000000321 2^64
    
    h[0] = 0;
    for (int i = 0; i < n; i++) h[i + 1] = ((p*h[i] + s[i] - 'a') % m + m) % m;
    
    return h;
}

int sub_hash(int *h, int l, int r) // [l, r)
{
    return ((h[r] - h[l]*pows[r - l]) % m + m) % m;
}


int main(void)
{
    // prep pows
    int pm = 1000000;
    pows = calloc(pm, sizeof(int));
    pows[0] = 1;
    for (int i = 1; i < pm; i++) pows[i] = (pows[i - 1]*p % m + m) % m;

    char s1[] = "abacaba";
    char s2[] = "roabacas";
    int *hash1 = pol_hash(s1); // z_func2(s); // pref2(s); //pref(s);
    int *hash2 = pol_hash(s2);

    printf("%d\n", sub_hash(hash1, 0, 3) == sub_hash(hash2, 2, 6));

    // for (int i = 0; i < strlen(s); i++) printf("%d ", p[i]);
    
    free(hash1);
    free(hash2);
    free(pows);

    return 0;
}