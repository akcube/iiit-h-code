#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

#define tc int t; scanf("%d", &t); while(t--)

int arr[100001];

int main(void){
	int q;
	scanf("%d", &q);

	for(int i=0; i<q; i++){
		int op, x;
		scanf("%d %d", &op, &x);
		if(op==1){
			arr[x]++;
		}
		else if(op==2){
			if(arr[x]>0) arr[x]--;
		}
		for(int j=0; j<100001; j++){
			if(arr[j]==0){
				printf("%d ", j);
				break;
			}
		}
	}
}