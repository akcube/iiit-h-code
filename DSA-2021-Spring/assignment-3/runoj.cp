#ifndef __INCL_HASHTABLE
#define __INCL_HASHTABLE

#include<stdint.h>

static const int LIN_PROB = 0;
static const int QUAD_PROB = 1;
static const int SEP_CHAIN = 2;
static const int DICTIONARY = 8;


static const int SPEED = 3;
static const int LOAD = 4;
static const int CHECK_AND_PRINT = 5;
static const int CHECK = 6;


struct cw_node{
	int data;
	struct cw_node *next;
}; 

typedef struct cws_node{
	char data[33];
	struct cws_node *next;
} cws_node; 

typedef struct cw_node cw_node;

typedef int p_node;

typedef struct ow_node{
	char word[32];	
} ow_node;

typedef struct HashTable{
	int size;
	int table_size;
	int type;
	char *file;
	void *table;
	int misspelled_ct;
	uint64_t (*hash)(void *str, uint32_t size, uint32_t table_size);
	int (*insert)(int data, struct HashTable *ht);
	int (*search)(int data, struct HashTable *ht);
	int (*speed)(int n, char *file_in_mem, struct HashTable *ht, int mode);
} HashTable;

void createTable(HashTable *ht, const int TYPE, int init_size, uint64_t (*hash)(void*, uint32_t, uint32_t));
void deleteTable(HashTable *ht);

#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>

#define LINEAR_PROBING 0
#define QUADRATIC_PROBING 1
#define CHAINED_HASHING 2
#define SPEED 3
#define DICTIONARY 8

uint64_t defHash(void *data, uint32_t size, uint32_t table_size){
	char *str = (char*) data;
	uint64_t hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

// void rehashQuad(HashTable *ht){
// 	int *table = (int*)ht->table;
// 	int *arr = (int*) malloc(sizeof(p_node*)*(ht->table_size*2));		
// 	memset(arr, 0, sizeof(p_node*)*(ht->table_size*2));
// 	for(int i=0; table[i]; i++){
// 		if(table[i]){
// 			uint64_t idx = ht->hash(&table[i], sizeof(int), (ht->table_size)*2);
// 			p_node node = arr[idx];
// 			for(int i=0; node; i++)
// 				node = arr[idx=(idx+i+i+1)%(ht->table_size*2)];
// 			arr[idx] = table[i];
// 		}
// 	}
// 	free(table);
// 	ht->table = arr;
// 	ht->table_size *= 2;
// }

int quadraticSearch(int key, HashTable *ht){
	int *table = (int*)ht->table;
	uint64_t idx = ht->hash(&key, sizeof(int), ht->table_size);
	p_node node = table[idx];

	for(int i=0; node; i++){
		if(node==key)
			return idx;
		node = table[idx=(idx+i+i+1)%ht->table_size];
	}
	return -1;
}

int quadraticInsert(int data, HashTable *ht){
	int *table = (int*)ht->table;
	ht->size++;
	// if(((double)ht->size/ht->table_size) >= 0.5){
	// 	rehashQuad(ht);
	// }

	uint64_t idx = ht->hash(&data, sizeof(int), ht->table_size);
	p_node node = table[idx];
	int ct = 0; 
	for(int i=0; node; i++, ct++)
		node = table[idx=(idx+i+i+1)%ht->table_size];
	table[idx] = data;
	return ct;
}

int linearSearch(int key, HashTable *ht){
	int *table = (int*)ht->table;
	uint64_t idx = ht->hash(&key, sizeof(int), ht->table_size);
	p_node node = table[idx];
	for(int i=0; node; i++){
		if(node==key)
			return idx%ht->table_size;
		node = table[(++idx)%ht->table_size];
	}
	return -1;
}

int linearInsert(int data, HashTable *ht){
	int *table = (int*)ht->table;
	ht->size++;
	uint64_t idx = ht->hash(&data, sizeof(int), ht->table_size);
	p_node node = table[idx];
	int ct = 0;
	for(;node; ct++)
		node = table[(++idx)%ht->table_size];
	table[(idx)%ht->table_size] = data;
	return ct++;
}

int chainedSearch(int key, HashTable *ht){
	uint64_t idx = ht->hash(&key, sizeof(int), ht->table_size);
	cw_node **table = (cw_node**) ht->table;
	cw_node *node = table[idx];
	for(int i=0; node; i++){
		if(node->data == key)
			return i;
		node = node->next;
	}
	return -1;
}

int chainedInsert(int data, HashTable *ht){
	ht->size++;
	uint64_t idx = ht->hash(&data, sizeof(int), ht->table_size);
	cw_node **table = (cw_node**) ht->table;
	cw_node *node = table[idx];
	cw_node *newn = (cw_node*) malloc(sizeof(cw_node));
	newn->next = NULL;
	newn->data = data;
	int ct = 0;
	if(!node)
		table[idx] = newn;
	else{
		for(;node->next; ct++)
			node = node->next;
		node->next = newn;
	}
	return ct;
}

// int chainedWordInsert(char *data, HashTable *ht){
// 	ht->size++;
// 	int len = strlen(data);
// 	uint64_t idx = ht->hash(&data, len, ht->table_size);
// 	cws_node **table = (cws_node**) ht->table;
// 	cws_node *node = table[idx];
// 	cws_node *newn = (cws_node*) malloc(sizeof(cws_node));
// 	newn->next = NULL;
// 	strcpy(newn->data, data);
// 	int ct = 0;
// 	if(!node)
// 		table[idx] = newn;
// 	else{
// 		for(;node->next; ct++)
// 			node = node->next;
// 		node->next = newn;
// 	}
// 	return ct;
// }

// int chainedWordSearch(char *key, HashTable *ht){
// 	int len = strlen(key);
// 	uint64_t idx = ht->hash(key, len, ht->table_size);
// 	cws_node **table = (cws_node**) ht->table;
// 	cws_node *node = table[idx];
// 	for(int i=0; node; i++){
// 		if(strcmp(node->data, key)==0)
// 			return i;
// 		node = node->next;
// 	}
// 	return -1;
// }

//======================================================================================

#ifndef _MURMURHASH3_H_
#define _MURMURHASH3_H_

#include <stdint.h>


#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FORCE_INLINE inline
#endif

static FORCE_INLINE uint32_t rotl32 ( uint32_t x, int8_t r )
{
  return (x << r) | (x >> (32 - r));
}

static FORCE_INLINE uint64_t rotl64 ( uint64_t x, int8_t r )
{
  return (x << r) | (x >> (64 - r));
}

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

//-----------------------------------------------------------------------------
// Block read - if your platform needs to do endian-swapping or can only
// handle aligned reads, do the conversion here

#define getblock(p, i) (p[i])

//-----------------------------------------------------------------------------
// Finalization mix - force all bits of a hash block to avalanche

static FORCE_INLINE uint32_t fmix32 ( uint32_t h )
{
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

//----------

static FORCE_INLINE uint64_t fmix64 ( uint64_t k )
{
  k ^= k >> 33;
  k *= BIG_CONSTANT(0xff51afd7ed558ccd);
  k ^= k >> 33;
  k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
  k ^= k >> 33;

  return k;
}

#endif

int speed(int n, char *file_in_mem, HashTable *ht, int mode){
	int *Table = (p_node*) ht->table;
	int word_count = 0;
    uint64_t k1, h1;
    h1 = 0;
    uint32_t prev_i = 1;
    uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
    int curlen = 0;
    int i;
    int misspelled = 0;
    if(mode==LOAD)
    	ht->file = file_in_mem;
    for(i=0; word_count<n;)
    {	//0x4040404040404040

    	uint64_t len;
        if(mode==LOAD)
        	len = (*((uint64_t*)&file_in_mem[i])) ^ 0x0A0A0A0A0A0A0A0A;
        else 
        	len = (*((uint64_t*)&file_in_mem[i])) ^ 0x2020202020202020;
    	len = (len-0x0101010101010101) & ~(len) & 0x8080808080808080;
        len =  ((__builtin_ffsl(len))>>3)-1;

        if(len==-1){
            k1 = *((uint64_t*)&file_in_mem[i]);
            k1 *= c1; k1  = ROTL64(k1,31);
            h1 ^= k1;
			h1 = ROTL64(h1,27);
			h1 = ((h1<<2)+h1)+0x52dce729;	
            i += 8;
            curlen += 8;
            continue;
        }
        
        curlen += len;
        uint8_t *tail = (uint8_t*)&file_in_mem[i];
        k1 = 0;
        switch(len){
        	case  8: k1 ^= (uint64_t)(tail[7]) << 56;
 			case  7: k1 ^= (uint64_t)(tail[6]) << 48;
  			case  6: k1 ^= (uint64_t)(tail[5]) << 40;
  			case  5: k1 ^= (uint64_t)(tail[4]) << 32;
  			case  4: k1 ^= (uint64_t)(tail[3]) << 24;
  			case  3: k1 ^= (uint64_t)(tail[2]) << 16;
  			case  2: k1 ^= (uint64_t)(tail[1]) << 8;
  			case  1: k1 ^= (uint64_t)(tail[0]) << 0;
           	         k1 *= c1; 
                     k1  = ROTL64(k1,31); 
                     h1 ^= k1;
        }

        h1 ^= curlen;
        h1 = fmix64(h1);

        i += len+1;
        
        //file_in_mem[i-1] = 0;
		// printf("%d -> %d | %ld -> %d | %d\n", prev_i, i, len, curlen, word_count);
		// if(prev_i<i)
		// 	puts
		//usleep(1000);
        
        h1 = h1&(ht->table_size-1);

        if(mode==LOAD){
   	   		file_in_mem[i-1] = ' ';
	       	for(int j=1;Table[h1]!=0;j++){
            	h1 = (h1 * 11400714819323198485llu) >> 45;
       			//h1 = (hashval + j*j)&NN;
        	}
        	Table[h1] = prev_i;
    	}
    	else if(mode>=CHECK_AND_PRINT){
    		bool miss = true;
    		for(int j=1;Table[h1]!=0;j++){
    			//printf("%s | %s\n", &file_in_mem[prev_i-1], &(ht->file[Table[h1]-1]));
    			if(memcmp(&file_in_mem[prev_i-1], &(ht->file[Table[h1]-1]), curlen+1)==0){
    				miss = false;
    				break;		
    			}
            	h1 = (h1 * 11400714819323198485llu) >> 45;
        	}
        	if(miss){
				misspelled++;
				if(mode&1){
					file_in_mem[i-1] = 0;
    				printf("%s\n", &file_in_mem[prev_i-1]);
    			}
    		}
    	}
        word_count++;
        h1 = 0;
        curlen = 0;
        prev_i = i + 1;
    }
    ht->misspelled_ct = misspelled;
    return i;
}


//======================================================================================

void createTable(HashTable *ht, const int TYPE, int init_size, uint64_t (*hash)(void*, uint32_t, uint32_t)){
	ht->size = 0;
	ht->table_size = init_size;
	ht->type = TYPE;

	if(hash)
		ht->hash = hash;
	else 
		ht->hash = defHash;

	switch(TYPE){
		case CHAINED_HASHING:
			ht->table = (cw_node**) malloc(sizeof(cw_node*)*init_size);
			memset(ht->table, 0, sizeof(cw_node*)*init_size);
			ht->insert = chainedInsert;
			ht->search = chainedSearch;
			break;

		case QUADRATIC_PROBING:
			ht->table = (p_node*) malloc(sizeof(p_node*)*init_size);		
			memset(ht->table, 0, sizeof(p_node*)*init_size);
			ht->insert = quadraticInsert;
			ht->search = quadraticSearch;
			break;

		case LINEAR_PROBING:
			ht->table = (p_node*) malloc(sizeof(p_node*)*init_size);	
			memset(ht->table, 0, sizeof(p_node*)*init_size);
			ht->insert = linearInsert;
			ht->search = linearSearch;
			break;

		case SPEED:
			ht->table = (p_node*) malloc(sizeof(p_node)*init_size);
			memset(ht->table, 0, sizeof(p_node)*init_size);
			ht->speed = speed;
			break;

		case DICTIONARY:
			ht->table = (cws_node**) malloc(sizeof(cws_node*)*init_size);	
			memset(ht->table, 0, sizeof(cws_node*)*init_size);
			ht->insert = linearInsert;
			ht->search = linearSearch;
			break;
	}

}

void deleteNode(cw_node *head){
	if(!head) return;
	deleteNode(head->next);
	free(head);
}

void deleteTable(HashTable *ht){
	if(ht->type == CHAINED_HASHING){
		cw_node **table = (cw_node**) ht->table;
		for(int i=0; i<ht->table_size; i++){
			deleteNode(table[i]);
		}
	}
	free(ht->table);
}


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MOD 1000000007

char a[100001];
char b[100001];

int prefixa[100001];
int prefixb[100001];

int p[100001];

int max(int a, int b);
int min(int a, int b);
void precompPowers(int n);
void calcPrefix(int len, char *str, int *prefix);
int getHash(int start, int end, int *prefix);

inline int min(int a, int b) { return (a<b)?a:b; }
inline int max(int a, int b) { return (a>b)?a:b; }

void precompPowers(int n){
	p[0] = 1;
	for(int i=1; i<=n; i++)
		p[i] = (1ll*p[i-1]*31)%MOD;
}

void calcPrefix(int len, char *str, int *prefix){
	prefix[0] = 0;
	prefix[1] = str[0];
	for(int i=2; i<=len; i++)
		prefix[i] = (prefix[i-1]+(1ll*str[i-1]*p[i-1])%MOD)%MOD;
}

inline int getHash(int start, int end, int *prefix){
	return (prefix[end+1]-prefix[start]+MOD)%MOD;
}

bool checkGenerator(int len, int n, int *prefix){
	int j;
	for(j=len; j+j<=n; j<<=1)
		if((1ll*prefix[j]*p[j])%MOD!=getHash(j, j+j-1, prefix))
			return false;
	if(j<n){
		int suffixhash = getHash(j, n-1, prefix);
		int prefixhash = getHash(0, n-j-1, prefix);
		if((1ll*prefixhash*p[j])%MOD!=suffixhash)
			return false;
	}
	return true;
}

signed main(void){
	int lena, lenb;
	scanf(" %s%n%*c", a, &lena);
	scanf(" %s%n%*c", b, &lenb);

	precompPowers(max(lena, lenb)+1);
	calcPrefix(lena, a, prefixa);
	calcPrefix(lenb, b, prefixb);
	int n = min(lena, lenb);
	int ct = 0;

	for(int i=1; i<=n; i++){
		if(lena%i!=0 || lenb%i!=0) continue;
		if(prefixa[i]!=prefixb[i]) break;
		bool generator = checkGenerator(i, lena, prefixa);
		generator &= checkGenerator(i, lenb, prefixb);
		if(generator) ct++;
	}
	printf("%d\n", ct);
}

