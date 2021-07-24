#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

#define tc int t; scanf("%d", &t); while(t--)
typedef long long ll;

int cmpfunc(const void *a, const void *b){
	long long *x = (long long*)a;
	long long *y = (long long*)b;
	return *x<*y;
}

signed main(void){

	long long n;
	scanf("%lld", &n);

	long long arr[2*n];
	for(int i=0; i<2*n; i++){
		scanf("%lld", &arr[i]);
	}

	qsort(arr, 2*n, sizeof(long long), cmpfunc);
	long long sum1 = 0;
	long long sum2 = 0;

	for(int i=0; i<n; i++) sum1 += arr[i];
	for(int i=n; i<2*n; i++) sum2 += arr[i];

	printf("%lld", sum1-sum2);
}