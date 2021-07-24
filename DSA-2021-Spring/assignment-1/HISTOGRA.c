#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 100010

int stack[N];
int stack2[N];
int ans[N];
int ans2[N];
int top = -1;
int top2 = -1;

void push(int i, int *stack, int *top){
	stack[++(*top)] = i;
}

int pop(int *stack, int *top){
	if((*top)<0) return -1;
	return stack[(*top)--];
}

void reset(int *top){
	(*top) = -1;
}

int main(void){

	int n;
	scanf("%d", &n);

	while(n!=0){

		int arr[n];
		for(int i=0; i<n; i++){
			scanf("%d", &arr[i]);
		}

		for(int i=0; i<n; i++){
			if(top==-1){
				ans[i] = i-1;
			}
			else if(arr[stack[top]]<arr[i]){
				ans[i] = stack[top];
			}
			else{
				while(top!=-1){
					if(arr[stack[top]]<arr[i]){
						ans[i] = stack[top];
						break;
					}
					pop(stack, &top);
				}
				if(top==-1){
					ans[i] = i-1;
				}
			}
			push(i, stack, &top);
		}
		for(int i=n-1; i>=0; i--){
			if(top==-1){
				ans[i] = i+1;
			}
			else if(arr[stack2[top2]]<arr[i]){
				ans[i] = stack2[top2];
			}
			else{
				while(top2!=-1){
					if(arr[stack2[top2]]<arr[i]){
						ans[i] = stack2[top2];
						break;
					}
					pop(stack2, &top2);
				}
				if(top==-1){
					ans[i] = i+1;
				}
			}
			push(i, stack2, &top2);
		}
		int max = 0;
		for(int i=0; i<n; i++){
			int area = (ans2[i]-ans[i]+1)*arr[i];
			if(max<area){
				max = area;
			}
		}
		printf("%d\n", max);

		scanf("%d", &n);
	}

}