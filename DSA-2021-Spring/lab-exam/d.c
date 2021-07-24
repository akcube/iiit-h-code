#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

#define tc int t; scanf("%d", &t); while(t--)
typedef long long ll;

typedef struct pair{
	ll first;
	ll second;
} pair;

#define DATA_TYPE pair
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

void createVector(VECTOR* v, uint32_t n) ;
void destroyVector(VECTOR* v) ;

void __VECRESIZE(VECTOR* v, uint32_t tab_size) ;
void __VECPUSHBACK(VECTOR* v, DATA_TYPE data) ;
uint32_t __VECGETSIZE(VECTOR* v) ;
DATA_TYPE __VECGET(VECTOR* v, uint32_t i) ;
void __VECSET(VECTOR* v, DATA_TYPE data, uint32_t i) ;
void __VECERASE(VECTOR* v, uint32_t ind) ;
DATA_TYPE __VECPOPBACK(VECTOR* v) ;


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

#define DATA_TYPE pair
//!No idempotency guards on purpose

#include <stdlib.h>
#include <stdbool.h>
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

#ifndef __HEAP_UTIL_FUNCS
#define __HEAP_UTIL_FUNCS
	
	int getRight(int) ;
	int getLeft(int) ;
	int getParent(int) ;
	int max(int, int) ;
	int min(int, int) ;

	inline int getRight(int i){	return (i<<1)+2; }
	inline int getLeft(int i){ return (i<<1)+1; }
	inline int getParent(int i){ return ((i-1)>>1)*(i!=0); }
	inline int max(int a, int b){ return (a>b)?a:b; }
	inline int min(int a, int b){ return (a<b)?a:b; }

#endif
#ifndef HEAP
	#define HEAP CAT2(heap_, DATA_TYPE)
	#define __HEAPGETTOP CAT3(__, DATA_TYPE, __heap__top)
	#define __HEAPPUSH CAT3(__, DATA_TYPE, __heap__push)
	#define __HEAPPOP CAT3(__, DATA_TYPE, __heap__pop)
	#define __HEAPIFY CAT3(__, DATA_TYPE, __heapify)
	#define __swap CAT3(__, DATA_TYPE, __swap)
	#define __EMPTY CAT3(__, DATA_TYPE, __heap__empty)
	#define __HEAP_SIFTDOWN CAT3(__, DATA_TYPE, __heap__siftdown)
	#define __heapInv CAT3(__, DATA_TYPE, __invariant)
	#define createHeap CAT3(create_, DATA_TYPE, _heap)
	#define destroyHeap CAT3(destroy_, DATA_TYPE, _heap)
#endif


typedef struct HEAP{
	DATA_TYPE *arr;
	uint32_t size;
	uint32_t table_size;
	void (*push)(DATA_TYPE val, struct HEAP *heap);
	bool (*cmpfunc)(DATA_TYPE a, DATA_TYPE b);
	DATA_TYPE (*getTop)(struct HEAP *heap);
	DATA_TYPE (*pop)(struct HEAP *heap);
	bool (*empty)(struct HEAP *heap);
} HEAP;

void __swap(DATA_TYPE *a, DATA_TYPE *b){
	DATA_TYPE temp = *a;
	*a = *b;
	*b = temp;
}

DATA_TYPE __HEAPGETTOP(HEAP *heap){
	assert(heap->size >= 0);
	return (heap->arr[0]);
}

bool __EMPTY(HEAP *heap){ return heap->size==0; }

DATA_TYPE __heapInv(DATA_TYPE a, DATA_TYPE b, HEAP *h){
	return (h->cmpfunc(a, b))?a:b;
}

void __HEAPIFY(int id, HEAP *h){
	while(h->cmpfunc(h->arr[id], h->arr[getParent(id)])){
		__swap(&(h->arr[getParent(id)]), &(h->arr[id]));
		id = getParent(id);
	}
}

void __HEAPPUSH(DATA_TYPE val, HEAP *heap){
	if(heap->size == heap->table_size){
		heap->table_size <<= 1;
		heap->arr = (DATA_TYPE*)realloc(heap->arr, ((heap->size)<<1)*sizeof(DATA_TYPE));
	}
	heap->arr[heap->size] = val;
	__HEAPIFY(heap->size++, heap);
}

void __HEAP_SIFTDOWN(int id, HEAP *h){

	DATA_TYPE ma;
	if(getLeft(id) >= h->size) return;
	else if(getRight(id) >= h->size) {
		ma = h->arr[getLeft(id)];
		if(h->cmpfunc(ma, h->arr[id]))
			__swap(&(h->arr[id]), &(h->arr[getLeft(id)]));
		return;
	}

	ma = __heapInv(h->arr[getRight(id)], h->arr[getLeft(id)], h);
	
	while(h->cmpfunc(ma, h->arr[id])){
		if(h->cmpfunc(h->arr[getRight(id)], h->arr[getLeft(id)])){
			__swap(&(h->arr[id]), &(h->arr[getRight(id)]));
			id = getRight(id);
		}
		else{
			__swap(&(h->arr[id]), &(h->arr[getLeft(id)]));
			id = getLeft(id);
		}
		
		if(getLeft(id) >= h->size) break;
		else if(getRight(id) >= h->size) {
			ma = h->arr[getLeft(id)];
			if(h->cmpfunc(ma, h->arr[id]))
				__swap(&(h->arr[id]), &(h->arr[getLeft(id)]));
			break;
		}

		ma = __heapInv(h->arr[getRight(id)], h->arr[getLeft(id)], h);
	}
}

DATA_TYPE __HEAPPOP(HEAP *heap){
	assert(heap->size!=0);
	DATA_TYPE top = __HEAPGETTOP(heap);
	__swap(&(heap->arr[0]), &(heap->arr[heap->size-1]));
	heap->size--;
	__HEAP_SIFTDOWN(0, heap);
	return top;
}

void createHeap(uint32_t n, bool (*cmpfunc)(DATA_TYPE, DATA_TYPE), HEAP *heap){
	heap->arr = (DATA_TYPE*) malloc(sizeof(DATA_TYPE)*n);
	heap->size = 0;
	heap->table_size = n;
	heap->push = __HEAPPUSH;
	heap->pop = __HEAPPOP;
	heap->getTop = __HEAPGETTOP;
	heap->cmpfunc = cmpfunc;
	heap->empty = __EMPTY;
}

void destroyHeap(HEAP *heap){
	free(heap->arr);
	heap->size = 0;
}

#undef DATA_TYPE
#undef HEAP
#define int ll
			 
#define INFTY 1000000000000000

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

bool cmpfunc(pair a, pair b){
    return a.second < b.second;
}

pair make_pair(int a, int b){
    pair p;
    p.first = a;
    p.second = b;
    return p;
}

heap_pair pq;

int dijkstra(int s, int n, vector_pair *adj, int *hospitals){

	int dis[n];
	for(int i=0; i<n; i++) dis[i] = INFTY;

	dis[s] = 0;
    create_pair_heap(500, cmpfunc, &pq);
    pq.push(make_pair(s, 0), &pq);

    while(!pq.empty(&pq)){
        pair top = pq.pop(&pq);
        int node = top.first;
        int curr_d = top.second;

        if(hospitals[node]==true){
        	adj[s].push_back(&adj[s], make_pair(node, curr_d));
        	return curr_d;
        }

        if(dis[node] != curr_d) continue;

        for(int i=0; i<adj[node].size(&adj[node]); i++){
            pair e = adj[node].get(&adj[node], i);
            if(dis[node] + e.second < dis[e.first]){
                dis[e.first] = dis[node] + e.second;
                pq.push(make_pair(e.first, dis[e.first]), &pq);
            }
        }
    }
    destroy_pair_heap(&pq);
    return INFTY;
}

signed main(void){

	int n, m;
	scanf("%lld %lld", &n, &m);
	vector_pair adj[n];
	for(int i=0; i<n; i++)
		create_pair_vector(&adj[i], 10);
		

	for(int i=0; i<m; i++){
		int f, t, w;
		scanf("%lld %lld %lld", &f, &t, &w);
		pair edge;
		f--, t--;
		edge.first = t;
		edge.second = w;
		adj[f].push_back(&adj[f], edge);
		swap(&f, &edge.first);
		adj[f].push_back(&adj[f], edge);
	}

	int b;
	scanf("%lld", &b);
	int hospitals[n];
	memset(hospitals, 0, sizeof(int)*n);
	for(int i=0; i<b; i++){
		int x;
		scanf("%lld", &x);
		hospitals[--x] = 1;
	}

	for(int i=0; i<n; i++){
		if(hospitals[i]) printf("%d ", 0);
		else{
			int len = dijkstra(i, n, adj, hospitals);
			printf("%lld ", len);
		}
	}
	printf("\n");



}