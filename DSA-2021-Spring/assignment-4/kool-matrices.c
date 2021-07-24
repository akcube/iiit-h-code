#include<stdio.h>
#include<stdlib.h>

typedef long long ll;

#define int ll

typedef struct pair{
	int first;
	int second;
} pair;

signed cmpfunc(const void *a, const void *b){
	int x = *((int*)a);
	int y = *((int*)b);
	return x > y;
}

signed main(void){
	int n, k;
	scanf("%Ld %Ld", &n, &k);
	int arr[n];
	for(int i=0; i<n; i++)
		scanf("%Ld", &arr[i]);
	ll x;
	scanf("%Ld", &x);

	if(x%k != 0){
		printf("0\n");
		return 0;
	}

	x /= k;
	
	int window = 0;
	for(int i=0; i<k; i++)
		window += arr[i];

	int sums[n-k+1];
	sums[0] = window;
	for(int i=1; i<n-k+1; i++){
		window -= arr[i-1];
		window += arr[i+k-1];
		sums[i] = window;
	}
	qsort(sums, n-k+1, sizeof(ll), cmpfunc);

	pair matrices[n-k+1];
	matrices[0].first = sums[0];
	matrices[0].second = 1;
	int j=1;
	for(int i=1; i<n-k+1; i++){
		if(sums[i]!=sums[i-1]){
			matrices[j].first = sums[i];
			matrices[j++].second = 1;
		}
		else{
			matrices[j-1].second++;
		}
	}

	int ct = 0;
	for(int i=0; i<j; i++){
		int curr = matrices[i].first;
		int l = 0, r=j-1;
		int ans = -1;
		while(l<=r){
			int mid = l+(r-l)/2;
			if(curr + matrices[mid].first > x)
				r = mid-1;
			else if(curr + matrices[mid].first < x)
				l = mid+1;
			else{
				ans = mid;
				break;
			}
		}
		if(ans==-1) continue;
		else{
			ct += matrices[i].second*matrices[ans].second;
		}
	}

	printf("%Ld\n", ct);

}