#include <stdio.h>
#include <stdlib.h>

int foo(void)
{
    printf("start of foo");
    exit(0);
    printf("end of foo");
}

int main(void)
{
    foo();
    printf("Main end");
    return 0;
}

/*
experiment results: exit terminates program
whereever it is. stores in stdlib.h
*/