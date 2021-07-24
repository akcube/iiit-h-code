#include<bits/stdc++.h>
#include<time.h>

using namespace std;

typedef long long ll;

int main(int argc, char *argv[]){
	srand(time(0));
	if(!strcmp(argv[1], "linprob")){
		cout<<"linear-probing\n";
	}
	else if(!strcmp(argv[1], "quadprob")){
		cout<<"quadratic-probing\n";
	}
	else if(!strcmp(argv[1], "sepchain")){
		cout<<"separate-chaining\n";
	}
	cout<<2003<<endl<<2000<<endl;
	for(int i=0; i<2000; i++){
		cout<<"+ "<<rand()*2<<endl;
	}

}