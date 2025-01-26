#include <stdio.h>
#include <stdlib.h>

static int A;

static int *bless(int *ptr)
{
    if (*ptr > 0) return ptr;

    printf("zero:%d\n", *ptr);
    exit(0);
}

static int *cursed(int E)
{
    int B = -2;
    extern int C;
    static int D = 4;
    int *ret = 0;


    if (E) {
        static int E = 5;
    } else {
        int C = -3;
        static int D = -4;
        ret = &C;
    }
    return bless(ret);
}

int C = 3;

int main(void)
{
    printf("%ld\n", cursed(A));
    printf("%ld\n", &C);
    printf("FUCK you\n");
}