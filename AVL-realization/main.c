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

int way(Avl *t, int key)
{
    if (t->key == key) return 0;
    else if (key < t->key) return -1;
    else return 1;
}

Avl *acway(Avl *t, int d)
{
    if (!d) return t;
    else if (d < 0) return t->l;
    else return t->r;
}

Avl *insert(Avl *t, int key, int val)
{
    if (!t) return create(key, val);

    Avl *A = NULL;

    Avl *p = NULL;
    while(t && t->key != key)
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

    *(key < p->key ? &p->l : &p->r) = create(key, val);

    Avl *r = NULL;
    if (!A) r = t;
    else
    {
        int d1 = way(p, key);
        Avl *C = acway(A, d1);
        if (A->bal != d1)
        {
            A->bal = 0;
            r = C; // !!!
        }
        else
        {
            int d2 = way(C, key);
            Avl *B = acway(C, d2);

            
        }
    }
}

int main(void)
{
    printf("%d", sizeof(Avl));
    return 0;
}