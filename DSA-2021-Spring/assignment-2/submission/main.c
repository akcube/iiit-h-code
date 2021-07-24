#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "bst.h"

typedef long long ll;

Node *root;

void swap(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
}

int randomBST(int n){
	int *arr = malloc(sizeof(int)*n);
	for(int i=0; i<n; i++){
		arr[i] = i+1;
	}
	for(int i=0; i<n; i++){
		swap(&arr[i], &arr[rand()%(i+1)]);
	}
	for(int i=0; i<n; i++){
		root = insert(arr[i], root);
	}
	free(arr);
	return root->height;
}

void avgDepth(){
	srand(time(0));
	int m[4] = {10, 50, 100, 1000};
	int n[4] = {10, 50, 100, 1000};
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			ll sum = 0;
			for(int k=0; k<m[i]; k++){
				sum += randomBST(n[j]);
				deleteBST(root);
				root = NULL;
			}
			printf("%lf ", (double)sum/m[i]);
		}
		printf("\n");
	}
}

int main(void){
	avgDepth();
}