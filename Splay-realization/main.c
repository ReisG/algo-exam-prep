#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Spl
{
    int k, data;
    struct Spl *l, *r;
};

typedef struct Spl Spl;

void swap(Spl **a, Spl **b)
{
    Spl *c = *a;
    *a = *b;
    *b = c;
}

Spl *rotate(Spl *t, int der)
{
    if (der == 0) return t;
    if (der < 0)
    {
        Spl *tt = t->r;
        t->r = tt->l;
        tt->l = t;
        return tt;
    }
    else
    {
        Spl *tt = t->l;
        t->l = tt->r;
        tt->r = t;
        return tt;
    }
}

int sgn(int key)
{
    if (key < 0) return -1;
    else if (key > 0) return 1;
    return 0;
}

int dir(Spl *t, int key)
{
    return sgn(key - t->k);
}

Spl *splay(Spl *t, int k)
{
    Spl *p = NULL;
    Spl *n = t;

    // going down
    while (n && n->k != k)
    {
        if (k < n->k) swap(&n->l, &p);
        else swap(&n->r, &p);
        swap(&n, &p);
    }

    // n = n ? n : p;

    Spl *ch, *gch;
    ch = gch = NULL;

    if (n) ch = n;
    n = p;

    while (n)
    {
        // fixing top structure
        Spl *up = ch;
        swap(k < n->k ? &n->l : &n->r, &up);

        if (ch && (gch || !up)) // if we have collected children or we have nowhere to go
        {
            if (!gch && !up) /*otherwise gch collected*/
            {
                // case 1: vertex nearby the root single rotation
                n = rotate(n, -dir(n, k));
            }
            else if (dir(n, k) == dir(ch, k))
            {
                // on the same side
                n = rotate(n, -dir(n, k));
                n = rotate(n, -dir(n, k));
            }
            else
            {
                // case 3: different sides
                *(dir(n, k) < 0 ? &n->l : &n->r) = rotate(ch, -dir(ch, k));
                n = rotate(n, -dir(n, k));
            }

            // action happend, rewriting pointers
            ch = gch = NULL;
        }

        // going up
        gch = ch;
        ch = n;
        n = up;
    }

    return ch;
}

Spl *look_up(Spl **t, int k)
{
    if (!*t) return NULL;
    *t = splay(*t, k);
    if ((*t)->k == k) return (*t);
    else return NULL; // error not found
}

Spl *create(int key, int data)
{
    Spl *n = calloc(1, sizeof(Spl));
    n->k = key;
    n->data = data;
    n->l = n->r = NULL;
    return n;
}

void insert(Spl **t, int key, int data)
{
    if (!*t)
    {
        *t = create(key, data);
        return;
    } 

    *t = splay(*t, key);
    if ((*t)->k == key)
    {
        // just update
        (*t)->data = data;
        return;
    }

    Spl *n = create(key, data);
    if (key < (*t)->k)
    {
        n->r = *t;
        n->l = (*t)->l;
        (*t)->l = NULL;
    }
    else
    {
        n->l = *t;
        n->r = (*t)->r;
        (*t)->r = NULL;
    }

    *t = n;
}

void delete(Spl **t, int key)
{
    if (!*t) return;

    *t = splay(*t, key);

    if ((*t)->k != key) return;

    if (!(*t)->l)
    {
        Spl *tt = *t;
        *t = (*t)->r;
        free(tt);
        return;
    }

    (*t)->l = splay((*t)->l, INT_MAX);
    (*t)->l->r = (*t)->r;

    Spl *tt = *t;
    *t = (*t)->l;
    free(tt);
}

void clear(Spl *t)
{
    if (!t) return;

    clear(t->l);
    clear(t->r);
    free(t);
}

int main(void)
{
    char com = 'Z';
    Spl *root = NULL;

    while (scanf("%c", &com), com != 'F')
    {
        if (com == 'A')
        {
            int k, d;
            scanf("%d%d", &k, &d);
            insert(&root, k, d);
        }
        else if (com == 'D')
        {
            int k;
            scanf("%d", &k);
            delete(&root, k);
        }
        else if (com == 'S')
        {
            int k;
            scanf("%d", &k);
            Spl *t = look_up(&root, k);
            if (t) printf("%d %d\n", k, t->data);
        }
        // else printf("Unknown com\n");
    }

    clear(root);
    return 0;
}

/*
A 10 20 
A 20 30 
S 10
10 20
A 9 10
S 9
*/
