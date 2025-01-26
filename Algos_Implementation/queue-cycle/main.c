#include <stdio.h>
#include <stdlib.h>

struct Queue
{
	int b, e;
	int cap;
	int *p;
};

typedef struct Queue Queue;

Queue *init(int cap)
{
	Queue *t = calloc(1, sizeof(Queue));
	t->b = t->e = cap - 1;
	t->cap = cap;
	t->p = calloc(cap, sizeof(int));
	return t;
}

void push(Queue *t, int v)
{
	t->p[t->b--] = v;
	if (t->b < 0) t->b = t->cap - 1;
}

int pop(Queue *t)
{
	int res = t->p[t->e--];
	if (t->e < 0) t->e = t->cap - 1;
	return res;
}

int isempty(Queue *t)
{
	return t->b == t->e;
}

void kill(Queue *t)
{
	free(t->p);
	free(t);
}


int main(void)
{
	Queue *t = init(4);
	push(t, 10);
	push(t, 20);
	push(t, 30);
	push(t, 100);
	while (!isempty(t)) printf("%d ", pop(t));
	kill(t);
	return 0;
}
