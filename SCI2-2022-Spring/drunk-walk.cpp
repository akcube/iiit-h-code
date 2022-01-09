#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

ld simulate(int n){

	int p1, p2; 
	p1 = p2 = 0;
	for(int i=0; i<n; i++){
		if(rand()%2 == 0) p1++;
		else p1--;
		if(rand()%2 == 0) p2++;
		else p2--;
	}
	return ((p1 == p2)?1.0:0.0);
}

int main(void){


	int iters = 10000;
	int n = 100;
	srand(time(0));

	for(int i=0; i<=n; i++) cout<<i<<" ";
	cout<<endl;

	for(int i=0; i<=n; i++){
		int t = iters;
		ld p = 0.0;
		while(t--)
			p += simulate(i);
		p = p/iters;
		cout<<p<<" ";
	}
	cout<<endl;
}