#include <stdio.h>

/*
Theorem: if string has border of length k
it also has period of length n - k
https://neerc.ifmo.ru/wiki/index.php?title=%D0%9F%D0%B5%D1%80%D0%B8%D0%BE%D0%B4_%D0%B8_%D0%B1%D0%BE%D1%80%D0%B4%D0%B5%D1%80,_%D0%B8%D1%85_%D1%81%D0%B2%D1%8F%D0%B7%D1%8C
*/

int main(void)
{
    int pref[] = {0, 0, 1, 0, 1, 2, 1, 2, 3, 4};
    int n = sizeof(pref) / sizeof(int);
    int j = n;

    while (j > 0)
    {
        printf("%d\n", n - pref[j - 1]);
        j = pref[j - 1];
    }

    return 0;
}