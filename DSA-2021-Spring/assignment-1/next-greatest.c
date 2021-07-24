#include <stdio.h>
#include <stdbool.h>

int stack[3000005];
int top = -1;

void push(int x){
	stack[++top] = x;
}

bool pop(){
	if(top<0) return false;
	top--;
	return true;
}

bool isempty(){
	if(top<0) return true;
	return false;
}

int gettop(){
	if(top<0) return -1;
	return stack[top];
}

int arr[2000005];
int ans[2000005]; 

signed main(void){

	int n;
	scanf("%d", &n);

	for(int i=0; i<n; i++){
		scanf("%d", &arr[i]);
	}

	for(int i=0; i<n; i++) ans[i] = -1;

	for(int i=n-1; i>=0; i--){
		if(gettop()<=arr[i]){
			while(pop()){
				if(gettop()>arr[i]){
					ans[i] = gettop();
					break;
				}
			}
			
		}
		else{
			ans[i] = gettop();
		}
		push(arr[i]);
	}

	for(int i=0; i<n; i++){
		printf("%d ", ans[i]);
	}
	printf("\n");

}