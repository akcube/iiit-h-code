#ifndef __MYSTACK_
#define __MYSTACK_

typedef struct Stack{
	int top;
	int size;
	void (*push)(int ele, struct Stack *s);
	int (*empty)(struct Stack *s); 
	int (*pop)(struct Stack *s);
	int (*peek)(struct Stack *s);
	int *arr;
} Stack;

void createStack(int sz, Stack *s);
void deleteStack(Stack *s);

#endif