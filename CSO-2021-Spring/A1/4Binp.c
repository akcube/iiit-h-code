#include<stdio.h>

char arr[32];
int freq[26];

void freqcnt(char*, int*);

int main(void){
	scanf("%s", arr);

	freqcnt(arr, freq);

	for(int i=0; i<26; i++){
		printf("%c: %d\n", 65+i, freq[i]);
	}
	printf("\n");
}