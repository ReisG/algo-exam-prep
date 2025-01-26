#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    FILE *fin = fopen("input.bin", "r");

    unsigned buf;
    while (1)
    { 
        buf = 0;
        if (fread((char*)&buf + 3, sizeof(char), 1, fin) != 1) break;
        if (fread((char*)&buf + 1, sizeof(char), 1, fin) != 1) break;
        if (fread((char*)&buf + 0, sizeof(char), 1, fin) != 1) break;
        printf("%u ", buf);
    }

    fclose(fin);
    return 0;
}