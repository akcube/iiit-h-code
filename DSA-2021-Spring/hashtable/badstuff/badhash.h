#ifndef __HASH_C
#define __HASH_C
#define ll long long
typedef struct hashChaining hashChaining;
typedef struct tableEntry tableEntry;

struct tableEntry {
	int length;
	char* string;
	struct tableEntry* next;
};

struct hashChaining {
	tableEntry** chains;
}; 

ll hash(char*);
hashChaining* createhashChaining(); 
void insert(hashChaining*,char*);
double averageCollisions(hashChaining*);
int find(hashChaining*,char*);
#endif