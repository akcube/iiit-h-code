#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include"../hash.h"

int main(void){

	char *input = (char*) malloc(33*(1100000)+50);
	fread(input, 33*(1100000)+50, 1, stdin);

	int n;

	HashTable HT;
	createTable(&HT, SPEED, 524288, NULL);

	sscanf(input, "%d", &n);
	while(*input=='\n' || isdigit(*input)) input++;

	int ret = HT.speed(n, input, &HT, LOAD);

	input = input+ret;

	sscanf(input, "%d", &n);
	while(*input=='\n' || isdigit(*input)) input++;
	char *cur;
	for(cur = input; *cur!='\n' && *cur != 0; cur++);
	*cur = ' ';

	HT.speed(n, input, &HT, CHECK);
	printf("%d\n", HT.misspelled_ct);
	HT.speed(n, input, &HT, CHECK_AND_PRINT);

	deleteTable(&HT);
}