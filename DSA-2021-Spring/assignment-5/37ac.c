#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>

#define DATA_TYPE int

//!No idempotency guards on purpose

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#ifndef DATA_TYPE
	#error Requires DATA_TYPE to be defined
    #define DATA_TYPE int
#endif

#ifndef __MACRO_CONCAT_UTILS
#define __MACRO_CONCAT_UTILS

#define _CAT2(x,y) x ## y
#define CAT2(x,y) _CAT2(x,y)
#define CAT3(x,y,z) CAT2(x,CAT2(y,z))

#endif

#ifndef VECTOR
	#define VECTOR CAT2(vector_, DATA_TYPE)
	#define __VECRESIZE CAT3(__, DATA_TYPE, __vec__resize)
	#define __VECPUSHBACK CAT3(__, DATA_TYPE, __vec__pushback)
	#define __VECGETSIZE CAT3(__, DATA_TYPE, __vec__size)
	#define __VECGET CAT3(__, DATA_TYPE, __vec__get)
	#define __VECSET CAT3(__, DATA_TYPE, __vec__set)
	#define __VECERASE CAT3(__, DATA_TYPE, __vec__erase)
	#define __VECPOPBACK CAT3(__, DATA_TYPE, __vec__popback)
	#define createVector CAT3(create_, DATA_TYPE, _vector)
	#define destroyVector CAT3(destroy_, DATA_TYPE, _vector)
#endif

typedef struct VECTOR{
	DATA_TYPE* arr;
	uint32_t cur_size;
	uint32_t table_size;

	void (*push_back)(struct VECTOR*, DATA_TYPE);
	uint32_t (*size)(struct VECTOR*);
	DATA_TYPE (*pop_back)(struct VECTOR*);
	DATA_TYPE (*get)(struct VECTOR*, uint32_t);
	void (*set)(struct VECTOR*, DATA_TYPE, uint32_t);
	void (*erase)(struct VECTOR*, uint32_t);
} VECTOR;

void createVector(VECTOR* v, uint32_t n);
void destroyVector(VECTOR* v);

void __VECRESIZE(VECTOR* v, uint32_t tab_size){
    v->arr = (DATA_TYPE*) realloc(v->arr, (tab_size)*(sizeof(DATA_TYPE)));
    v->table_size = tab_size;
}

void __VECPUSHBACK(VECTOR* v, DATA_TYPE data){
    
    if(v->cur_size == v->table_size)
        __VECRESIZE(v, (v->table_size<<1));

    v->arr[v->cur_size++] = data;
}

uint32_t __VECGETSIZE(VECTOR* v){
    return v->cur_size;
}

DATA_TYPE __VECGET(VECTOR* v, uint32_t i){
	
	assert(i>=0 && i<v->cur_size);
    
    return v->arr[i];
}

void __VECSET(VECTOR* v, DATA_TYPE data, uint32_t i){

   	assert(i>=0 && i<v->cur_size);

    v->arr[i] = data;
}

void __VECERASE(VECTOR* v, uint32_t ind){
    
    for(uint32_t i=ind;i<v->cur_size-1;i++)
        v->arr[i] = v->arr[i+1];

    v->cur_size--;

    if(v->cur_size <= (v->table_size)>>2)
        __VECRESIZE(v, v->table_size>>1);
}

DATA_TYPE __VECPOPBACK(VECTOR* v){
    assert(v->cur_size>=0);
    DATA_TYPE retVal = v->arr[v->cur_size-1];
    __VECERASE(v, v->cur_size-1);
    return retVal;
}

void createVector(VECTOR* v, uint32_t n){
    v->arr = (DATA_TYPE*)malloc(sizeof(DATA_TYPE)*n);
    assert(v->arr != NULL);

    v->cur_size = 0;
    v->table_size = n;

    v->size = __VECGETSIZE;
    v->push_back = __VECPUSHBACK;
    v->get = __VECGET;
    v->set = __VECSET;
    v->erase = __VECERASE;
    v->pop_back = __VECPOPBACK;
}

void destroyVector(VECTOR *v){
    free(v->arr);
    v->cur_size = v->table_size = 0;
}

#undef DATA_TYPE
#undef VECTOR

int stack[100000];
int top = -1;

void push(int i){ stack[++top] = i; }
int pop() { return stack[top--]; }
int stacksize() { return top+1; }

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int n, m;

int findset(int *dsu, int v){
	if(dsu[v]==v) return v;
	else return dsu[v] = findset(dsu, dsu[v]);
}

void make_union(int *dsu, int a, int b){
	a = findset(dsu, a);
	b = findset(dsu, b);
	if(a>b){
		dsu[b] = a;	
	}
	else{
		dsu[a] = b;
	}
}

void dfs1(vector_int *adj, int v, bool *vis){
	if(vis[v]) return;
	vis[v] = true;

	for(int i=0; i<adj[v].size(&adj[v]); i++){
		int e = adj[v].get(&adj[v], i);
		dfs1(adj, e, vis);
	}
	push(v);
}

int dfs2(vector_int *adj, int v, bool *vis, int *dsu, int parent){
	if(vis[v]) return 0;
	vis[v] = true;

	make_union(dsu, v, parent);
	int ct = 0;
	for(int i=0; i<adj[v].size(&adj[v]); i++){
		int e = adj[v].get(&adj[v], i);
		ct += dfs2(adj, e, vis, dsu, parent);
	}
	return ct+1;
}

int main(void){
	scanf("%d %d", &n, &m);

	vector_int adj[n];
	vector_int adjt[n];
	vector_int sccg[n];

	for(int i=0; i<n; i++){
		create_int_vector(&adj[i], 100);
		create_int_vector(&adjt[i], 100);
		create_int_vector(&sccg[i], 100);
	}

	for(int i=0; i<m; i++){
		int from, to;
		scanf("%d %d", &from, &to);
		from--, to--;
		adj[from].push_back(&adj[from], to);
		swap(&from, &to);
		adjt[to].push_back(&adjt[from], to);
	}

	bool vis[n];
	memset(vis, 0, n);

	for(int i=0; i<n; i++){
		if(!vis[i])
			dfs1(adj, i, vis);
	}

	int dp[n];
	memset(vis, 0, n);
	int dsu[n];
	for(int i=0; i<n; i++) dsu[i] = i;
	// for(int i=0; i<n; i++) dp[i] = 1;
	for(int i=0; i<n; i++){
		int v = pop();
		if(!vis[v]){
			int ct = dfs2(adjt, v, vis, dsu, v);
			dp[v] = ct;
		}
	}

	for(int i=0; i<n; i++){
		int newi = findset(dsu, i);
		for(int j=0; j<adj[i].size(&adj[i]); j++){
			
			int to = findset(dsu, adj[i].get(&adj[i], j));
			if(newi != to)
				sccg[newi].push_back(&sccg[newi], to);
			//printf("%d %d\n", newi+1, findset(dsu, adj[i].get(&adj[i], j))+1);
		}
	}

	int topo[n];
	memset(vis, 0, n);
	top = -1;
	for(int i=0; i<n; i++){
		if(vis[i] || sccg[i].size(&sccg[i])==0) continue;
		dfs1(sccg, i, vis);
	}
	int len = 0;
	for(int i=0; top>=0; i++){
		topo[len=i] = pop();
	}
	len++;	

	memset(vis, 0, n);
	int vmax = 0;
	int maxct = 0;
	while(len>0){
		int v = topo[--len];
		for(int j=0; j<sccg[v].size(&sccg[v]); j++){
			int to = sccg[v].get(&sccg[v], j);
			dp[v] += dp[to];
		}
		if(dp[v] > maxct || (dp[v]==maxct && vmax > v)){
			vmax = v;
			maxct = dp[v];
		}
	}

	printf("%d\n", vmax+1);

}
