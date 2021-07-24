#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

void push(int ele, Stack *s){
	if(s->top==(s->size-1))
		s->arr = realloc(s->arr, (s->size = ((s->size)<<1))*sizeof(int));
	s->arr[++(s->top)] = ele;
}

int empty(Stack *s){ return (s->top < 0); }

int pop(Stack *s){
	if(s->top >= 0) return s->arr[(s->top)--];
	return -1;
}

int peek(Stack *s){
	if(s->top >= 0) return s->arr[(s->top)];
	return -1;	
}

void createStack(int sz, Stack *s){
	s->arr = malloc(sz*sizeof(int));
	s->top = -1;
	s->size = sz;
	s->push = push;
	s->pop = pop;
	s->empty = empty; 
	s->peek = peek;
}

void deleteStack(Stack *s){
	if(s!=NULL){
		if(s->arr)
			free(s->arr);
		s->top = -1;
		s->size = 0;
	}
}
