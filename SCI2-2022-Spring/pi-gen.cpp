#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

bool simulate(int n){

	ld x = (ld)(rand()%1001)/1000;
	ld y = (ld)(rand()%1001)/1000;

	return (x*x + y*y <= 1);
}

int main(void){


	int iters = 1000;
	int n = 10000;
	srand(time(0));

	for(int i=1; i<=n; i++) cout<<i<<" ";
	cout<<endl;

	for(int i=1; i<=n; i++){
		int t = i;
		ld p = 0.0;
		while(t--)
			p += simulate(i);
		p = 4*p/i;
		cout<<p<<" ";
	}
	cout<<endl;
}