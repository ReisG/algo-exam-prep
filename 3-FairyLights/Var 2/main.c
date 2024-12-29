#include <stdio.h>
#include <stdlib.h>

struct list
{
    int key;
    struct list *next;
    struct list *sublist_head;
};

struct pair
{
    int f, s;
};

struct pair max(struct pair a, struct pair b)
{
    return a.f > b.f || a.f == b.f && a.s > b.s ? a : b;
}

struct pair exam(struct list *garland)
{
    struct pair res = {-1, -1};
    struct pair loc = {0, 0};
    for (;garland; garland = garland->next)
    {
        loc.f++, loc.s += garland->key;
        res = max(res, exam(garland->sublist_head));
    }
    if (loc.f) res = max(res, loc);
    return res;
}

int examine(struct list *garland)
{
    return exam(garland).s;
}

int main(void)
{
    struct list part4[] = {{4, &part4[1], NULL}, {4, NULL, NULL}};
    struct list part3[] = {{3, &part3[1], NULL}, {3, &part3[2], NULL}, {3, NULL, NULL}};
    struct list part2[] = {{2, &part2[1], NULL}, {2, &part2[2], &part3[0]}, {2, NULL, NULL}};
    struct list part1[] = {{1, &part1[1], &part2[0]}, {1, &part1[2], NULL}, {1, NULL, &part4[0]}};

    printf("%d", examine(part1));
    return 0;
}