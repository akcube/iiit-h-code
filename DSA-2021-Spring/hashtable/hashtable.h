#ifndef __HASHTABLEINCL
#define __HASHTABLEINCL

struct cw_node{
	char word[32];
	struct cw_node *next;
} __attribute__((aligned(16))); 

typedef struct cw_node cw_node;

typedef int p_node;

// typedef struct p_node{
// 	int index;
// } p_node;//__attribute__((aligned(16)));

typedef struct ow_node{
	char word[32];	
} ow_node __attribute__((aligned(16)));

typedef struct Hashtable{

} Hashtable;

void cw_load(char *);
bool check(const char *word);

#endif