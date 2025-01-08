#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SZ 10000
int main(void)
{
    printf("%d\n", SZ);
    for (int i = 0; i < SZ; i++)
    {
        int k = rand() % INT_MAX;
        int data = i;
        printf("%d %d\n", k, data);
    }
    return 0;
}