#include<stdio.h>
#include<string.h>
#include "my_stack.h"

int main(void){

	LinkedList LL;
	createList(&LL);

	char inp[100];
	do{
		scanf("%s", inp);

		if(strcmp(inp, "push")==0){
			double x, y;
			scanf("%lf %lf", &x, &y);
			LL.push(x, y, &LL);
			LL.printList(&LL);
		}
		else if(strcmp(inp, "pop")==0){
			Complex res = LL.pop(&LL);
			if(!res.success){
				printf("The stack is empty\n");
			}
			else{
				LL.printList(&LL);
			}
		}
		getchar();
	}
	while(strcmp(inp, "exit"));
	deleteList(&LL);
}