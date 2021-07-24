#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef long long ll;

int min(int a, int b){return (a<b)?a:b;}
int max(int a, int b){return (a>b)?a:b;}

int cmpfunc(const void *a, const void *b){
	int *p = (int*) a;
	int *q = (int*) b;
	return *p > *q;
}

int main(void){
	int n, q, k;
	scanf("%d %d %d", &n, &q, &k);

	int arr[n];
	for(int i=0; i<n; i++){
		scanf("%d", &arr[i]);
	}

	int sortedarr[n];
	memcpy(sortedarr, arr, sizeof(int)*n);
	qsort(sortedarr, n, sizeof(int), cmpfunc);

	for(int i=0; i<q; i++){
		int val, x;
		scanf("%d %d", &x, &val);
		int sindex = 0;
		int l = 0;
		int r = n-1;
		while(l<=r){
			int mid = l+(r-l)/2;
			if(sortedarr[mid]>val){
				r = mid-1;
			}
			else{
				sindex = mid;
				l = mid+1;
			}
		}
		int ct = 0;
		for(int i=max(0, sindex-k); i<min(min(n, sindex+k+1), x); i++){
			if(i>x)break;
			if(arr[i]>val) ct++;
		}
		ct += max(0, x-(sindex+k+1));
		printf("%d\n", ct);
	}

}