#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct list
{
    int data;
    struct list *next;
};

typedef struct list List;


/*
    Using prefix sums idea
*/
List *transform(List *head)
{
    List *l, *r, *m;
    int ls, rs, ws, ms;

    l = r = NULL; // doesn't matter
    ws = INT_MIN;

    ms = 0;
    m = NULL;

    int ns = 0;
    List *n = head;
    while (n)
    {
        ns += n->data;

        if (ws < ns - ms)
        {
            // update current segment
            l = m;
            r = n;
            ws = ns - ms;
        }

        if (ms > ns)
        {
            // update min bound
            m = n;
            ms = ns;
        }

        n = n->next;
    }

    if (!l) return head;

    List *t = l->next;
    l->next = r->next;
    r->next = head;
    return t;
}

List *create(int k)
{
    List *t = calloc(1, sizeof(List));
    t->data = k;
    t->next = NULL;
    return t;
}

int main(void)
{
    //int ar[] = {-1, -2, 2, -1};
    int ar[] = {1, -10, 100000, 1, -2};
    List *r = create(ar[0]);
    List *n = r;
    for (int i = 1; i < sizeof(ar)/sizeof(int); i++, n = n->next)
    {
        n->next = create(ar[i]);
    }

    for (n = r; n; n=n->next) printf("%d ", n->data);
    printf("\n");

    // printf("%p\n", n->next);
    r = transform(r);

    for (n = r; n; n=n->next) printf("%d ", n->data);
    printf("\n");

    while (r)
    {
        n = r->next;
        free(r);
        r = n;
    }

    return 0;
}