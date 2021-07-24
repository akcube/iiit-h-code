#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include"hash.h"

uint64_t hashfn(void *data, uint32_t size, uint32_t table_size){
	return (*((uint32_t*)data))%table_size;
}

int main(void){
	HashTable HT;

	char mode[50];
	scanf("%s", mode);
	int n, q;
	scanf("%d %d", &n, &q);

	if(!strcmp(mode, "linear-probing"))
		createTable(&HT, LIN_PROB, 2003, hashfn);
	else if(!strcmp(mode, "quadratic-probing"))
		createTable(&HT, QUAD_PROB, 2003, hashfn);
	else if(!strcmp(mode, "separate-chaining"))
		createTable(&HT, SEP_CHAIN, 2003, hashfn);

	for(int i=0; i<q; i++){
		char m;
		int d;
		scanf(" %c %d", &m, &d);
		
		if(m=='+')
			HT.insert(d, &HT);
		else
			printf("%d\n", HT.search(d, &HT));
	}

	deleteTable(&HT);
}