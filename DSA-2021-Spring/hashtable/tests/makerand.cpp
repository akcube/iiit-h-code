#include<bits/stdc++.h>
#include<time.h>

using namespace std;


int main(void){
	srand(time(0));
	for(int i=0; i<10000000; i++){
		int len = rand()%36;
		string x = "";
		for(int j=0; j<len; j++){
			x += "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand()%52];
		}
		cout<<x<<" ";
		if(rand()%100 < 10)
			cout<<endl;
	}
}