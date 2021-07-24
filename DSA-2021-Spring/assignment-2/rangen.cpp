#include<bits/stdc++.h>
#include<time.h>

using namespace std;

typedef long long ll;

int main(void){
	int n;
	cin>>n;
	vector<int> ran(n);
	iota(ran.begin(), ran.end(), 0);
	srand(time(0));
	random_shuffle(ran.begin(), ran.end());
	cout<<n<<" ";
	for(auto x:ran) cout<<x<<" ";
}