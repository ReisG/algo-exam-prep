#include <stdio.h>
#include <stdlib.h>

struct Tree
{
    short k;
    struct Tree *l, *r;
};

struct TreeRaw
{
    short k;
    short l, r;
};

typedef struct Tree Tree;
typedef struct TreeRaw TreeRaw;

int read3(FILE *f, short *k, short *l, short *r)
{
    return fread(k, sizeof(*k), 1, f) == 1
    && fread(l, sizeof(*l), 1, f) == 1
    && fread(r, sizeof(*r), 1, f) == 1;
}

Tree *createTree(short v, TreeRaw *ar, int sz)
{
    if (v >= sz || v < 0) return NULL;

    Tree *root = calloc(1, sizeof(TreeRaw));
    root->k = ar[v].k;
    root->l = createTree(ar[v].l, ar, sz);
    root->r = createTree(ar[v].r, ar, sz);

    return root;
}

#define max(a, b) ((a) > (b) ? (a) : (b))
void curv(Tree *t, int *l, int *r, int *w)
{
    *l = *r = *w = 0;
    int li, ri, wi;

    if (t->l)
    {
        curv(t->l, &li, &ri, &wi);
        *l = ri + 1;
        *w = wi;
    }

    if (t->r)
    {
        curv(t->r, &li, &ri, &wi);
        *r = li + 1;
        *w = max(*w, wi);
    }

    *w = max(*w, max(*l, *r));
}

void kill(Tree *t)
{
    if (!t) return;
    kill(t->l);
    kill(t->r);
    free(t);
}

int main(void)
{
    FILE *fin = fopen("input.bin", "r");
    int cap = 10, sz = 0;
    TreeRaw *ar = calloc(cap, sizeof(TreeRaw));

    short ki, li, ri;
    while (read3(fin, &ki, &li, &ri))
    {
        if (sz == cap) ar = realloc(ar, (cap <<= 1)*sizeof(TreeRaw));
        ar[sz].k = ki;
        ar[sz].l = li;
        ar[sz++].r = ri;
    }
    ar = realloc(ar, (cap = sz)*sizeof(TreeRaw));

    // constructing tree itself
    Tree *root = createTree(0, ar, sz);
    
    // don't need array anymore
    free(ar);

    int l, r, w;
    curv(root, &l, &r, &w);
    printf("%d\n", w);

    kill(root);
    return 0;
}