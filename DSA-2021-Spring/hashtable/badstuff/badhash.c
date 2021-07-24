#define ll long long
#define ull unsigned long long
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "badhash.h"
#include "bloom_filter.h"

const ull tableSize = 200000; // Smallest prime above 2000

ull hashHorner(char* str, int n) {
	ull p = 33;
	ull hashValue = 0;
	for (int i = n - 1; i >= 0; i--) {
		hashValue = (hashValue * p + ((str[i]|0x20) - 'a' + 1)) % tableSize;
		//hashValue = (hashValue + ((str[i]|0x20) + 1))%tableSize;
	}
	return hashValue;
}

ull hashModulus(ull x, int n){
	return x % n;
}

tableEntry* createEntry(char* str,int n) {
	tableEntry* temp = (tableEntry*) malloc(sizeof(tableEntry));

	temp->length = n;
	temp->string = (char*)malloc((temp->length + 1) * sizeof(char));
	temp->next = NULL;
	strcpy(temp->string, str);
	return temp;
}

hashChaining* createhashChaining() {
	hashChaining* ht = (hashChaining*) malloc(sizeof(hashChaining));
	ht->chains = (tableEntry**) malloc(tableSize * sizeof(tableEntry*));
	
	// Dummy nodes
	for (int i = 0; i < tableSize; i++) {
		ht->chains[i] = (tableEntry*) malloc(sizeof(tableEntry));
		ht->chains[i]->length = 0;
		ht->chains[i]->string = NULL;
		ht->chains[i]->next = NULL;
	}
	
	return ht;
}

int find(hashChaining* ht, char* str) {
	int n = strlen(str);
	ull hashValue = hashHorner(str, n);
    tableEntry* head = ht->chains[hashValue]->next;	
    char temp[48];
    for(int i=0; i<=n; i++){
    	if(!str[i]){
    		temp[i] = 0;
    		break;
    	}
    	temp[i] = (str[i]|0x20);
    }
	while(head != NULL){
		if(strcmp(head->string, temp) == 0) return 1;
		head = head->next;
	}


	return 0;
}
void insertInTable(hashChaining* ht, tableEntry* t, int pos) {
	tableEntry* head = ht->chains[pos];
	t->next = head->next;	
	head->next = t;
}


void insert(hashChaining* ht, char* str) {
	int n = strlen(str);
	#ifdef WITHBLOOM
		bloomAdd((unsigned char*)str);
	#endif
	tableEntry* node = createEntry(str, n);
	ull hashValue = hashHorner(str, n);	

	insertInTable(ht, node, hashValue);		
}

double averageCollisions(hashChaining* ht) {
	double collisions = 0;
	ll lists = 0;
	for(int i = 0; i < tableSize; i++) {
		tableEntry* iterator = ht->chains[i]->next;	
		int size = 0;
		//printf("%d\n", i);
		while(iterator!=NULL) {
			size++;
			iterator = iterator->next;
			//printf("%s\n",iterator->string);
		}	
		if (size > 1) { 
			collisions += size - 1;
			lists++;
		}
	}
	printf("%lf %lld\n",collisions,lists);
	return collisions / lists;
}
