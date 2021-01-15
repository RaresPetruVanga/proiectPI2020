#include <stdlib.h>
#include "Queue.h"

stack* newQue(int x, int y)
{
	stack* p = (stack*)malloc(sizeof(stack));

	p->x = x;

	p->y = y;

	p->leg = NULL;

	return p;
}

void push(stack** src, stack* p)
{
	p->leg = (*src);

	(*src) = p;
}

stack* pop(stack** src)
{
	stack* p = (*src);

	(*src) = (*src)->leg;

	p->leg = NULL;

	return p;
}

int isEmpty(stack* src)
{
	return src != NULL;
}
