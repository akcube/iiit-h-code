#ifndef __INCL_HASHTABLE
#define __INCL_HASHTABLE

#include<stdint.h>

static const int LIN_PROB = 0;
static const int QUAD_PROB = 1;
static const int SEP_CHAIN = 2;

static const int SPEED = 3;
static const int LOAD = 4;
static const int CHECK_AND_PRINT = 5;
static const int CHECK = 6;


struct cw_node{
	int data;
	struct cw_node *next;
	int garbage[100000];
} __attribute__((aligned(16))); 

typedef struct cw_node cw_node;

typedef int p_node;

typedef struct ow_node{
	char word[32];	
} ow_node __attribute__((aligned(16)));

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
