#include<bits/stdc++.h>
#include<time.h>

using namespace std;

int main(void){

	srand(time(0));

	int n = 10;

	string arr[n];

	for(int i=0; i<n; i++){
		int strlen = rand()%10+1;
		arr[i] = "";
		for(int j=0; j<strlen; j++){
			int strcase = rand()%2;
			arr[i] += (char) 'A' + (rand()%26) + (strcase*32);
		}
		cout<<arr[i]<<endl;
	}

	cout<<endl;

	for(int i=0; i<n; i++){
		for(int j=0; j<(int)arr[i].length(); j++){
			if(j<4) cout<<arr[i][j];
			else cout<<"#";
		}
		cout<<endl;
	}

}