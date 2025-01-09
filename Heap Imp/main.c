#include <stdio.h>
#include <stdlib.h>

struct Heap
{
    int sz, cap;
    int *a;
};
typedef struct Heap Heap;

Heap *init(void)
{
    Heap *t = calloc(1, sizeof(Heap));
    t->sz = 1;
    t->cap = 10;
    t->a = malloc(t->cap*sizeof(int));

    return t;
}

#define swap(a, b) (a ^= b, b^=a, a^=b)
void hup(Heap *t)
{
    int n = t->sz - 1;
    while (n > 1 && t->a[n >> 1] > t->a[n]) 
        swap(t->a[n], t->a[n >> 1]), n >>= 1;
}

void hdown(Heap *t)
{
    int n = 1;
    while ((n << 1 | 1) < t->sz) // has both children
    {
        int s = (t->a[n << 1] < t->a[n << 1 | 1] ? n << 1 : n << 1 | 1);
        if (t->a[s] >= t->a[n]) return;
        swap(t->a[s], t->a[n]);
        n = s;
    }

    if (n << 1 < t->sz && t->a[n << 1] < t->a[n]) swap(t->a[n << 1], t->a[n]);
}

void push(Heap *t, int val)
{
    if (t->sz == t->cap) t->a = realloc(t->a, (t->cap <<= 1)*sizeof(int));
    t->a[t->sz++] = val;
    hup(t);
}

int peek(Heap *t)
{
    return t->a[1];
}

void pop(Heap *t)
{
    t->a[1] = t->a[--t->sz];
    if (t->sz <= t->cap >> 2) t->a = realloc(t->a, (t->cap >>= 1)*sizeof(int));
    hdown(t);
}

void kill(Heap *t)
{
    free(t->a);
    free(t);
}

int main(void)
{
    Heap *r = init();
    int a[] = {2, 2, -100, 23, 2, 4, 9, 3, 4, 342};
    for (int i = 0; i < sizeof(a)/sizeof(int); i++) push(r, a[i]), printf("%d ", r->sz);
    printf("\n");

    while (r->sz > 1)
    {
        printf("%d ", peek(r));
        pop(r);
    }
    printf("\n");
    // for (int i = 1; i < r->sz; i++) printf("%d ", r->a[i]);
    kill(r);

    return 0;
}