#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


struct SystemUnit
{
    int id;
    int left_id;
    int right_id;
    uint32_t config;
};


struct SystemStructure 
{
    struct SystemUnit unit;
    struct SystemStructure *left, *right;
};

// for testing
void output(struct SystemStructure *root)
{
    if (!root) return;

    printf("%d %d %d %u\n", 
            root->unit.id, 
            root->unit.left_id, 
            root->unit.right_id, 
            root->unit.config);

    output(root->left);
    output(root->right);
}


int main(void)
{
    FILE* fin = fopen("input.bin", "r");

    int cap = 10, sz = 0;
    struct SystemStructure *ar = calloc(cap, sizeof(struct SystemStructure));
    // why not??

    struct SystemUnit buf;
    while (fread(&buf, sizeof(struct SystemUnit), 1, fin) == 1)
    {
        if (sz == cap) ar = realloc(ar, (cap <<= 1)*sizeof(struct SystemUnit));
        ar[sz++].unit = buf;
    }
    ar = realloc(ar, (cap = sz)*sizeof(struct SystemStructure));

    char *isch = calloc(cap, sizeof(char));

    // creating tree structure
    for (int i = 0; i < sz; i++)
    {
        int s = ar[i].unit.left_id;
        if (s) for (int j = 0; j < sz; j++)
        {
            if (ar[j].unit.id != s) continue;
            ar[i].left = ar + j;
            isch[j]++;
            break;
        }
        else ar[i].left = NULL;

        s = ar[i].unit.right_id;
        if (s) for (int j = 0; j < sz; j++)
        {
            if (ar[j].unit.id != s) continue;
            ar[i].right = ar + j;
            isch[j]++;
            break;
        }
        else ar[i].right = NULL;
    }

    // looking for root
    int r;
    for (r = 0; r < sz && isch[r]; r++);

    struct SystemStructure *root = ar + r;

    output(root);

    // clearing mem
    free(ar);

    fclose(fin);
}