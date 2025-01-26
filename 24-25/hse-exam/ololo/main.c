#include <stdio.h>
#include <stdlib.h>

unsigned rev(unsigned x)
{
    unsigned res = 0;
    res |= (x & 0xFF) << 24;
    res |= (x & 0xFF00) << 8;
    res |= (x & 0xFF0000) >> 8;
    res |= (x & 0xFF000000) >> 24;
    return res;
}

int main(void)
{
    unsigned d;
    scanf("%u", &d);

    printf("%u\n", rev(d));
    return 0;
}
