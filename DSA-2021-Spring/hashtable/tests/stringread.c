#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>

#define N 3

int main(void){

	char *arr = malloc(N);
	arr[0] = 'x';
	do{
		int x = fread(arr, N, 1, stdin);
		arr[N-1] = 0;
		printf("%d\n", x);
		printf("%s", arr);
	}while(arr[0]!='a');
	
	printf("hi\n");
	


}