#include <stdio.h>
#include <stdlib.h>

/*
    First find deg=3 it is the top

    from the top going down thoght the trunk and
    checking if branches are good (deg < 3) and trunk has
    at most 1 truck block as neighbour excluding previous node
*/

struct node
{
    int deg;
    struct node **next;
};
typedef struct node Node;


Node* reachTop(Node* n, Node* last)
{
    if (n->deg == 3) return n;
    for (Node **i = n->next; i != n->next + n->deg; i++)
    {
        if (*i == last) continue;
        Node *res = reachTop(*i, n);
        if (res) return res;
    }
    return NULL;
}


int isBranch(Node* n, Node* last)
{
    if (n->deg > 2) return 0;
    for (Node **i = n->next; i != n->next + n->deg; i++)
    {
        if (*i == last) continue;
        if (!isBranch(*i, n)) return 0;
    }
    return 1;
}

int checkDown(Node* n, Node* last)
{
    // only one child 4deg
    int deg4cnt = 0;
    Node *gon = NULL;
    for (Node **i = n->next; i != n->next + n->deg; i++)
    {
        if (*i == last) continue;
        deg4cnt += (*i)->deg == 4;
        if ((*i)->deg == 4) gon = *i;

        if ((*i)->deg != 4 && !isBranch(*i, n)) return 0;
    }
    if (deg4cnt > 1) return 0;

    return gon ? checkDown(gon, n) : 1;
}

int isFir(Node* node)
{
    node = reachTop(node, NULL);
    if (!node) return 0;

    return checkDown(node, NULL);
}

int main(void)
{

    struct node f[] = {{1, NULL}, {1, NULL}, {1, NULL}};
    struct node* fi[] = {f, f + 1, f + 2};
    struct node root = {3, fi};

    struct node* rooti = &root;
    fi[0]->next = &rooti;
    fi[1]->next = &rooti;
    fi[2]->next = &rooti;


    printf("%d", isFir(f));
    return 0;
}
