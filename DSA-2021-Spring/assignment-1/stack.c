#include <stdio.h>
#include <stdbool.h>

typedef long long ll;

int stack[1000];
int top = -1;

void push(char x){
	top++;
	if(x=='(') stack[top] = 1;
}

bool pop(){
	if(top==-1) return false;
	else top--;
	return true;
}

void reset(){
	top=-1;
}

int main(void){


	int t;
	scanf("%d", &t);

	while(t--){
		char inp[1000];
		int n;
		scanf("%s%n", inp, &n);
		reset();
		bool pos = true;
		for(int i=0; i<n; i++){
			switch(inp[i]){
				case '(':
					push('(');
				break;
				case ')':
					if(!pop())
						pos = false;
				break;
			}
		}
		if(top!=-1) pos=false;

		if(pos){
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}
	}	

}