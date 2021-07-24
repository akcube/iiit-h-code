#include<stdio.h>

int hammingdis(short, short);

int main(void){
	short a, b;
	scanf("%hi %hi", &a, &b);
	printf("Hamming distance: %d\n", hammingdis(a, b));
}