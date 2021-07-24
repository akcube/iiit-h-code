#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int count[21];
int setup[21];

int getMedian(int arr[21], int n){
	int ct = 0;
	for(int i=0; i<21; i++){
		ct += arr[i];
		if(ct>n/2) return i;
	}
	return -1;
}

int main(void){
	int n, k;
	scanf("%d %d", &n, &k);
	int arr[n][n];
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			scanf("%d", &arr[i][j]);

	for(int i=0; i<k; i++)
		for(int j=0; j<k; j++)
			setup[arr[i][j]]++;

	int p = k/2;
	for(int i=p; i<n-p; i++){

		for(int l=0; l<k && i-p-1 >= 0; l++){
			setup[arr[i-p-1][l]]--;
			setup[arr[i+p][l]]++;
		}
		memcpy(count, setup, sizeof(int)*21);
		printf("%d ", getMedian(count, k*k));
		for(int j=p+1; j<n-p; j++){
			for(int l=0; l<k; l++){
				count[arr[i-p+l][j-p-1]]--;
				count[arr[i-p+l][j+p]]++;
			}
			printf("%d ", getMedian(count, k*k));
		}
		printf("\n");
	}
}