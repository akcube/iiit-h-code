#include<stdio.h>
#include "linkedlist.h"


int main(void){
	LinkedList LL;
	char temp[100];
	char *op;
	createList(&LL);

	int inp;

	do{
		printf("1. Add to list\n2. Remove from list\n3. Search in list\n4. Print list\n5. Sort list\n6. Exit\n\n");
		printf("Enter choice: ");
		scanf("%d", &inp);
		printf("\n");
		getchar();
		switch(inp){
			case 1:
				printf("Enter value: ");
				scanf("%[^\n]", temp);
				getchar();
				LL.createElement(temp, &LL);
				LL.printList(&LL);
				break;

			case 2:
				printf("Enter element name: ");
				scanf("%[^\n]", temp);	
				getchar();
				LL.deleteElement(temp, &LL);
				LL.printList(&LL);
				break;

			case 3:
				printf("Enter element name: ");
				scanf("%[^\n]", temp);	
				getchar();
				op = LL.getElement(temp, &LL);
				printf("%s\n", op?op:"Not found");
				break;

			case 4:
				LL.printList(&LL);
			break;

			case 5:
				LL.insertionSortList(&LL);
				LL.printList(&LL);
			break;

			case 6: 
				deleteList(&LL);
			return 0;

			default:
				printf("Correct usage: Enter your choice between 1 and 6\n\n");
			break;
		}
		printf("\n\n");
	}while(inp != 6);
}