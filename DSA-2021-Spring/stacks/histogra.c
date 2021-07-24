#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
#define int ll

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

long long max(long long a, long long b){
	return (a>b)?a:b;
}

signed main(void){
	Stack s;
	
	int n;
	scanf("%lld", &n);

	while(n!=0){
		
		int arr[n], rightmin[n], leftmin[n];
		for(int i=0; i<n; i++)
			scanf("%lld", &arr[i]);
		
		for(int i=0; i<n; i++){	leftmin[i] = -1;	rightmin[i] = n; }

		createStack(2, &s);
		for(int i=0; i<n; i++){
			while(!s.empty(&s) && arr[s.peek(&s)] >= arr[i])
				s.pop(&s);
			if(!s.empty(&s))
				leftmin[i] = s.peek(&s);
			s.push(i, &s);
		}
		deleteStack(&s);

		createStack(2, &s);
		for(int i=n-1; i>=0; i--){
			while(!s.empty(&s) && arr[s.peek(&s)] >= arr[i])
				s.pop(&s);
			if(!s.empty(&s))
				rightmin[i] = s.peek(&s);
			s.push(i, &s);
		}
		deleteStack(&s);

		// for(int i=0; i<n; i++) printf("%lld ", leftmin[i]);
		// printf("\n");

		// for(int i=0; i<n; i++) printf("%lld ", rightmin[i]);
		// printf("\n");

		long long ma = 0;
		for(int i=0; i<n; i++){
			ma = max(ma, 1ll*arr[i]*(rightmin[i]-leftmin[i]-1));
		}
		printf("%lld\n", ma);
		scanf("%lld", &n);
	}

	
}