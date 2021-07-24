#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef long long ll;

typedef struct node{
	int n;
	int id;
	char name[21];
} node;

int cmpfunc(const void *a, const void *b){
	node *p = (node*) a;
	node *q = (node*) b;
	if(p->n == q->n)
		return (p->id > q->id);
	return (p->n > q->n);
}

int main(void){
	int n;
	scanf("%d", &n);
	node arr[n];

	int x;
	char word[20];
	for(int i=0; i<n; i++){
		scanf("%d %s", &x, word);
		arr[i].n = x;
		arr[i].id = i;
		strcpy(arr[i].name, word);
	}
	qsort(arr, n, sizeof(node), cmpfunc);
	for(int i=0; i<n; i++){
		printf("%d %s\n", arr[i].n, arr[i].name);
	}
}