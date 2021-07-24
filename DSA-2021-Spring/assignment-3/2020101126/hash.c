#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include "hash.h"

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
