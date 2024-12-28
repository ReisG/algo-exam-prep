#include <stdio.h>
#include <stdlib.h>

/*
    Сначала выйдем к стволу, то есть найдём ноду deg=4
    из неё пойдём по нодам deg=4 до ноды deg=3
    
    из ноды deg3 запускаем следующую проверку
    идём по стволу и проверяем, правильные ли ветки
*/

struct node
{
    int deg;
    struct node **next;
};
typedef struct node Node;

Node* reachTrunk(Node* n, Node* last)
{
    if (n->deg == 4 || n->deg == 3) return n;
    for (Node **i = n->next; i != n->next + n->deg; i++)
    {
        if (*i == last) continue;
        Node *res = reachTrunk(*i, n);
        if (res) return res;
    }
    return NULL;
}

Node* reachTop(Node* n, Node* last)
{
    if (n->deg == 3) return n;
    for (Node **i = n->next; i != n->next + n->deg; i++)
    {
        if (*i == last || (*i)->deg != 4 && (*i)->deg != 3) continue;
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

        if (!isBranch(*i, n)) return 0;
    }
    if (deg4cnt > 1) return 0;

    return gon ? checkDown(gon, n) : 1;
}

int isFir(Node* node)
{
    node = reachTrunk(node, NULL);
    if (!node) return 0;

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