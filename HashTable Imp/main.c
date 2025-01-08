#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct HTCont
{
    void *key;
    void *data;
    struct HTCont *next;
};

struct HashTable
{
    size_t sz;                              // nubmer of buckets
    struct HTCont **buckets;                // table
    size_t (*hashf)(void *, size_t);                // hashing function
    int (*comp)(void *, void *);            // comparing function (0 - equal)
    void (*killkey)(void *);
    void (*killdata)(void *);
};


struct HashTable *init( size_t sz, 
                        size_t (*hashf)(void *, size_t),
                        int (*comp)(void *, void *),
                        void (*killkey)(void *),
                        void (*killdata)(void *)) 
{
    struct HashTable *self = calloc(1, sizeof(struct HashTable));
    self->sz = sz;
    self->buckets = calloc(sz, sizeof(struct HTCont*));
    self->hashf = hashf;
    self->comp = comp;
    self->killkey = killkey;
    self->killdata = killdata;
    return self;
}


void insert(struct HashTable *T, void *key, void *data)
{
    size_t h = (*T->hashf)(key, T->sz);
    struct HTCont *n = T->buckets[h];
    
    for (; n; n = n->next) if (!(*T->comp)(n->key, key))
    {
        // equal
        (*T->killdata)(n->data);
        n->data = data;
        n = n->next;
        return;
    }

    // haven't found matching key
    // creating new on head
    struct HTCont *t = calloc(1, sizeof(struct HTCont));
    t->key = key;
    t->data = data;
    t->next = T->buckets[h];
    T->buckets[h] = t;
}


void *get(struct HashTable *T, void *key)
{
    size_t h = (*T->hashf)(key, T->sz);
    struct HTCont *n = T->buckets[h];

    for (; n; n = n->next) if (!(*T->comp)(n->key, key))
    {
        return n->data;
    }

    return NULL;
}

int comp(void *a, void *b)
{
    return *(int*)a - *(int*)b;
}

size_t hashmult(void *a, size_t m)
{
    #define phi 0.6180339887498949 // (sqrt(5) - 1) / 2
    double r = (*(int*)a*phi);
    r = r - (long long) r;
    size_t res = m * r;
    return res;
    #undef phi
}

size_t hashdiv(void *a, size_t m)
{
    return (size_t)(*(int*)a) % m;
}

void destroy(struct HashTable *T)
{
    for (int i = 0; i < T->sz; i++)
    {
        struct HTCont *n = T->buckets[i], *p = NULL;
        while (n)
        {
            p = n;
            n = n->next;
            (*T->killkey)(p->key);
            (*T->killdata)(p->data);
            free(p);
        }
    }

    free(T->buckets);
    free(T);
}

int main(void)
{
    struct HashTable *ht = init(100000, &hashmult, &comp, &free, &free);

    int *k, *data;
    for (int i = 1; i < 10000; i++)
    {
        k = malloc(sizeof(int));
        data = malloc(sizeof(int));
        *k = rand() % INT_MAX;
        *data = i;
        insert(ht, k, data);
    }

    // want to see filling profile
    int rr = 0;
    for (int i = 0; i < ht->sz; i++)
    {
        int len = 0;
        for (struct HTCont *n = ht->buckets[i]; n; len++, n = n->next);
        rr = (rr > len ? rr : len);
    }
    printf("MAX in bucket: %d\n", rr);


    void *ttt = get(ht, &k);
    if (ttt) printf("%d\n", *(int*)ttt);
    else printf("NOT FOUND\n");

    destroy(ht);
    return 0;
}