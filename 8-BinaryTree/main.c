/*
We will consider t2 as splay tree
we will splay t2 by the root of t1
if there is vertex with same key then we run checking function
for left and right child.

The problem is that t2 will be changed

Using codebase from https://www.geeksforgeeks.org/introduction-to-splay-tree-data-structure/
Should learn it by heart

This approuch leads to memleak if tree is allocated in heap
This won't lead to leaks if tree is being allocated onto stack
*/


#include <stdio.h>
#include <stdlib.h>

struct tree;
typedef struct tree Tree;

struct tree
{
    int x;
    Tree *left, *right;
};
/*
Tree* rightrot(Tree *t)
{
    Tree *tt = t->left;
    t->left = tt->right;
    tt->right = t;
    return tt;
}

Tree* leftrot(Tree *t)
{
    Tree *tt = t->right;
    t->right = tt->left;
    tt->left = t;
    return tt;
}
*/

void rightrot(Tree *t)
{
    Tree *tt = t->left;
    t->left = tt->right;
    tt->right = tt;

    // swaping
    Tree *r = calloc(1, sizeof(Tree));
    memcpy(r, t, sizeof(Tree));
    memcpy(t, tt, sizeof(Tree));
    memcpy(tt, r, sizeof(Tree));
    free(r);
}

void leftrot(Tree *t)
{
    Tree *tt = t->right;
    t->right = tt->left;
    tt->left = tt;

    Tree *r = calloc(1, sizeof(Tree));
    memcpy(r, t, sizeof(Tree));
    memcpy(t, tt, sizeof(Tree));
    memcpy(tt, r, sizeof(Tree));
    free(r);
}

//Tree* splay(Tree *root, int key)
void splay(Tree *root, int key)
{
    if (!root || root->x == key) return; //root;
    if (key < root->x)
    {
        if (!root->left) return;// root;
        if (key < root->left->x)
        {
            // root->left->left = splay(root->left->left, key);
            splay(root->left->left, key);
            // root = rightrot(root);
            rightrot(root);
        }
        else if (root->left->x < key)
        {
            // root->left->right = splay(root->left->right, key);
            splay(root->left->right, key);
            if (root->left->right) leftrot(root->left);// root->left = leftrot(root->left);
        }
        root->left ? rightrot(root) : root;
        return;
    }
    else
    {
        if (!root->right) return;// root;
        if (root->right->x < key)
        {
            // root->right->right = splay(root->right->right, key);
            splay(root->right->right, key);
            // root = leftrot(root);
            leftrot(root);
        }
        else if (key < root->right->x)
        {
            //root->right->left = splay(root->right->left, key);
            splay(root->right->left, key);
            // if (root->right->left) root->right = rightrot(root->right);
            rightrot(root->right);
        }
        root->right ? leftrot(root) : root;
        return;
    }
}

int is_subset(int size, Tree *t1, Tree *t2)
{
    if (!t1) return 1;
    if (!t2) return 0;

    // t2 = splay(t2, t1->x);
    splay(t2, t1->x);
    if (t2->x != t1->x) return 0;

    return is_subset(1, t1->left, t2->left) && is_subset(1, t1->right, t2->right);
}

void print_tree(Tree *t)
{
    if (!t) return;
    print_tree(t->left);
    printf("%d ", t->x);
    print_tree(t->right);
}

int main(void)
{
    Tree t1_5 = {6, 0, 0};
    Tree t1_4 = {3, 0, 0};
    Tree t1_3 = {5, &t1_4, &t1_5};
    Tree t1_2 = {2, 0, &t1_3};
    Tree t1 = {1, 0, &t1_2};

    Tree t2_5 = {5, 0, 0};
    Tree t2_4 = {4, 0, &t2_5};
    Tree t2_3 = {3, 0, &t2_4};
    Tree t2_2 = {2, 0, &t2_3};
    Tree t2 = {1, 0, &t2_2};

    printf("%d", is_subset(1, &t1, &t2));
    // print_tree(&t2);
    return 0;
}
