#include<stdio.h>
#include<stdlib.h>

void mergesort(int *arr, int l, int r){

	int mid = l + (r-l)/2;
	mergesort(arr, l, mid);
	mergesort(arr, mid+1, r);

}