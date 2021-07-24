#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "my_stack.h"

void push(double x, double y, LinkedList *LL){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->x = x;
	ll->y = y;
	ll->next = LL->head;
	LL->head = ll;
}

void freeNode(Node *n){
	if(n)
		free(n);
}

Complex pop(LinkedList *LL){
	Complex returnval;
	if(LL->head==NULL) {
		returnval.success = 0;
	}
	else{
		returnval.x = LL->head->x;
		returnval.y = LL->head->y;
		returnval.success = 1;
		Node *tmp = LL->head;
		LL->head = LL->head->next;
		free(tmp);
	}
	return returnval;
}

void printList(LinkedList *LL){

	for(Node *cur = (LL->head); cur ;cur = cur->next)
		printf("{%lg, %lg}->", cur->x, cur->y);

	printf("NULL\n");
}

void deleteList(LinkedList *ll){
	Node *head = ll->head;
	for(Node *trv = head; trv; head = trv){
		trv = head->next;
		freeNode(head);
	}
}

void createList(LinkedList *ll){
	ll->head = NULL;
	ll->push = &push;
	ll->printList = &printList;
	ll->pop = &pop;
}
