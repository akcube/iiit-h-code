#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

#define tc int t; scanf("%d", &t); while(t--)


int stack[10000000];
int top = -1;

int *check = NULL;

void push(int i){ 
	stack[++top] = i; 
}
int pop() { 
	if(top<0) return *check;
	return stack[top--]; 
}
bool isEmpty(){ return !(top >= 0); }
int peek() { 
	if(top<0) *check = 1;
	return stack[top]; 
}

bool isLC = false;
bool isIC = false;

char match(char a, char b){
	if(a=='(' && b==')') return true;
	if(a=='[' && b==']') return true;
	if(a=='{' && b=='}') return true;
	if(b=='(' && a==')') return true;
	if(b=='[' && a==']') return true;
	if(b=='{' && a=='}') return true;
	return false;
}

int main(void){

	int n;
	scanf("%d", &n);
	char str[n+100];
	scanf(" %s", str);

	bool isBalanced = true;

	for(int i=0; i<n && isBalanced; i++){
		if(isLC){
			if(str[i]==';'){
				isLC = false;
				continue;
			}
		}

		if(isIC){
			if(i+1>=n) continue;
			else if(str[i]=='*' && str[i+1]=='/'){
				isIC = false;
				i++;
				continue;
			}
		}


		if(str[i]=='/'){
			if(i+1>=n) continue;
			else if(str[i+1]=='/') { isLC = true; i++; }
			else if(str[i+1]=='*') { isIC = true; i++; }
			continue;
		}

		if(isIC || isLC) continue;

		switch(str[i]){
			case '(':
			case '{':
			case '[':
				push(str[i]);
			break;

			case ')':
			case ']':
			case '}':
				if(isEmpty()) isBalanced = false;
				else if(!match(pop(), str[i]))
					isBalanced = false;
			break;
		}

	}

	if(isBalanced && isEmpty()){
		printf("Yes\n");
	}
	else{
		printf("No\n");
	}

}