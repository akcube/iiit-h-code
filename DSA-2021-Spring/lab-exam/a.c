#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

#define tc int t; scanf("%d", &t); while(t--)

typedef struct state{
	char s[5];
	int p, a, m, k;
} state;

int cmpfunc(const void *a, const void *b){
	state *x = (state *)a;
	state *y = (state *)b;

	if(x->p != y->p) return x->p < y->p;
	if(x->a != y->a) return x->a < y->a;
	if(x->m != y->m) return x->m < y->m;
	if(x->k != y->k) return x->k < y->k;
	return 1;
}

int main(void){
	int n;
	scanf("%d", &n);
	
	state arr[n];
	for(int i=0; i<n; i++){
		scanf(" %s %d %d %d %d", arr[i].s, &arr[i].p, &arr[i].a, &arr[i].m, &arr[i].k);
	}

	qsort(arr, n, sizeof(state), cmpfunc);

	for(int i=0; i<n; i++){
		printf("%s ", arr[i].s);
	}

}