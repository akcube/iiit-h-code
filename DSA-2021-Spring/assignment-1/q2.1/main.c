#include<stdio.h>
#include "linkedlist.h"


int main(void){
	LinkedList LL;
	int temp;
	
	createList(&LL);
	int op;
	int inp;

	do{
		printf("1. Add to list\n2. Remove all from list\n3. Find last in list\n4. Print list\n5. Exit\n\n");
		printf("Enter choice: ");
		scanf("%d", &inp);
		printf("\n");
		getchar();
		switch(inp){
			case 1:
				printf("Enter value: ");
				scanf("%d", &temp);
				LL.createElement(temp, &LL);
				LL.printList(&LL);
				break;

			case 2:
				printf("Enter element name: ");
				scanf("%d", &temp);	
				LL.deleteAll(temp, &LL);
				LL.printList(&LL);
				break;

			case 3:
				printf("Enter element name: ");
				scanf("%d", &temp);	
				op = LL.findLast(temp, &LL);
				printf("%d\n", op);
				break;

			case 4:
				LL.printList(&LL);
			break;

			case 5: 
				deleteList(&LL);
			return 0;

			default:
				printf("Correct usage: Enter your choice between 1 and 6\n\n");
			break;
		}
		printf("\n\n");
	}while(inp != 6);
}