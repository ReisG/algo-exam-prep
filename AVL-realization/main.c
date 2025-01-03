#include <stdio.h>
#include <stdlib.h>

struct Avl
{
    int key, val;
    struct Avl *l, *r;
    int bal;
};

typedef struct Avl Avl;

Avl *create(int key, int val)
{
    Avl *t = calloc(1, sizeof(Avl));
    t->key = key;
    t->val = val;
    t->bal = 0;
    t->l = t->r = NULL;
    return t;
}

// show which derection search would go
int way(Avl *t, int key)
{
    if (t->key == key) return 0;
    else if (key < t->key) return -1;
    else return 1;
}

// ACcess the WAY derection leads
acway(Avl *t, int d)
{
    if (!d) return t;
    else if (d < 0) return t->l;
    else return t->r;
}

Avl *rotate(Avl *t, int d)
{
    if (!d) return t;
    else if (d < 0)
    {
        Avl *tt = t->r;
        t->r = tt->l;
        tt->l = t;
        return tt;
    }
    else
    {
        Avl *tt = t->l;
        t->l = tt->r;
        tt->r = t;
        return tt;
    }
}

Avl *insert(Avl *t, int key, int val)
{
    if (!t) return create(key, val);

    Avl *A = NULL;

    Avl *p = NULL;
    while (t && t->key != key)
    {
        p = t;
        if (!p->bal) A = p;
        t = key < t->key ? t->l : t->r;
    }

    if (t)
    {
        // this key exists just updating the value
        t->val = val;
        return;
    }

    // pushing value to appropiate child
    // cool construction (I loved it)
    *(key < p->key ? &p->l : &p->r) = create(key, val);

    Avl *r = NULL; // first vertex to start rebalancing route
    if (!A) r = t; // there was no unbalanced vertex
    else
    {
        int d1 = way(A, key);
        Avl *C = acway(A, d1);
        if (A->bal != d1) // d1 != 0
        {
            // inserted vertex balanced our vertex back
            A->bal = 0;
            r = C; // not sure, book says p
        }
        else
        {
            int d2 = way(C, key);
            Avl *B = acway(C, d2);
            if (d1 == d2)
            {
                A->bal = 0;
                r = B;
                rotate(p, -d1);
            }
            else
            {
                int d3 = way(B, key);
                r = acway(B, d3);
                if (d3 == d2)
                {
                    A->bal = 0;
                    C->bal = d1;
                } else if (d3 == -d2) A->bal = d2;
                else A->bal = 0;
                rotate(C, -d2);
                rotate(A, -d1);
            }
            
        }
    }

    while (r && r->key != key) r->bal = way(r, key), r = acway(r, r->key - key);

    // return ??? what to return
    // PROBLEM, we didn't altered real pointers
    // So after I need to use pointer to pointer
}

int main(void)
{
    printf("%d", sizeof(Avl));
    return 0;
}