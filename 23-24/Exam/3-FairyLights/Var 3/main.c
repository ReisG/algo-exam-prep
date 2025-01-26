#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

struct pair comp(struct pair a, struct pair b)
{
    return a.f < b.f || a.f == b.f && a.s < b.s ? a : b;
}

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

struct pair exam(struct list *g)
{
    struct pair res = {INT_MAX, INT_MAX};
    struct pair loc = {0, INT_MAX};
    for (; g; g=g->next)
    {
        loc.f++, loc.s = min(loc.s, g->key);
        res = comp(res, exam(g->sublist_head));
    }
    if (loc.f) res = comp(res, loc);
    return res;
}

int examine(struct list *garland)
{
    struct pair res = exam(garland);
    return res.f == INT_MAX ? -1 : res.s;
}

int main(void)
{
    struct list part4[] = {{4, &part4[1], NULL}, {-10, NULL, NULL}, {4, NULL, NULL}};
    struct list part3[] = {{-10, &part3[1], NULL}, {3, &part3[2], NULL}, {3, NULL, NULL}};
    struct list part2[] = {{2, &part2[1], NULL}, {2, &part2[2], &part3[0]}, {2, NULL, NULL}};
    struct list part1[] = {{20, &part1[1], &part2[0]}, {1, &part1[2], NULL}, {1, NULL, &part4[0]}};

    printf("%d", examine(part1));
}