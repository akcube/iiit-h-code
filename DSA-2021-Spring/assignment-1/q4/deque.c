#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "deque.h"

void push(double x, double y, LinkedList *LL){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->x = x;
	ll->y = y;
	ll->next = LL->head;
	ll->prev = NULL;
	if(LL->head == NULL) LL->end = ll;
	else LL->head->prev = ll;
	LL->head = ll;
}

void inject(double x, double y, LinkedList *LL){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->x = x;
	ll->y = y;
	ll->next = NULL;
	ll->prev = LL->end;
	if(LL->end == NULL) LL->head = ll;
	else LL->end->next = ll;
	LL->end = ll;
}

void freeNode(Node *n){
	free(n);
}

Complex pop(LinkedList *LL){
	Complex returnval;
	if(LL->head==NULL){
		returnval.success = 0;
	}
	else{
		returnval.x = LL->head->x;
		returnval.y = LL->head->y;
		returnval.success = 1;
		Node *tmp = LL->head;
		LL->head = LL->head->next;
		if(LL->head == NULL) LL->end = NULL;
		else LL->head->prev = NULL;
		free(tmp);
	}
	return returnval;
}

Complex eject(LinkedList *LL){
	Complex returnval;
	if(LL->end==NULL) {
		returnval.success = 0;
	}
	else{
		returnval.x = LL->end->x;
		returnval.y = LL->end->y;
		returnval.success = 1;
		Node *tmp = LL->end;
		LL->end = LL->end->prev;
		if(LL->end == NULL) LL->head = NULL;
		else LL->end->next = NULL;
		free(tmp);
	}
	return returnval;
}

void printList(LinkedList *LL){

	for(Node *cur = (LL->head); cur ;cur = cur->next)
		printf("{%lg, %lg}<->", cur->x, cur->y);

	printf("NULL\n");
}

void deleteList(LinkedList *ll){
	Node *head = ll->head;
	for(Node *trv = head; trv; head = trv){
		trv = head->next;
		freeNode(head);
	}
	ll->head = NULL;
	ll->end = NULL;
}

void createList(LinkedList *ll){
	ll->head = NULL;
	ll->end = NULL;
	ll->push = &push;
	ll->printList = &printList;
	ll->pop = &pop;
	ll->inject = &inject;
	ll->eject = &eject;
}
