#include <stdio.h>

struct list
{
    int key;
    struct list *next;
    struct list *sublist_head;
};

#define amax(a, b) ((a) = ((a) > (b) ? (a) : (b)))
int examine(struct list *garland)
{
    if (!garland) return -1;
    int res = examine(garland->sublist_head);
    amax(res, examine(garland->next));
    if (!garland->next) amax(res, garland->key);
    return res;
}

int main(void)
{
    struct list part4[] = {{4, &part4[1], NULL}, {4, NULL, NULL}};
    struct list part3[] = {{3, &part3[1], NULL}, {3, &part3[2], NULL}, {3, NULL, NULL}};
    struct list part2[] = {{2, &part2[1], NULL}, {2, &part2[2], &part3[0]}, {2, NULL, NULL}};
    struct list part1[] = {{1, &part1[1], &part2[0]}, {1, &part1[2], NULL}, {1, NULL, &part4[0]}};

    printf("%d\n", examine(NULL));
    return 0;
}