#ifndef STACK_H_
#define STACK_H_

typedef struct stack
{
	int x;
	int y;
	struct stack* leg;
}stack;

stack* newQue(int, int);

void push(stack**, stack*);

stack* pop(stack**);

int isEmpty(stack*);

#endif
