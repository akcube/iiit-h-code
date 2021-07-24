#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#ifndef _MYLINKEDLIST_
#define _MYLINKEDLIST_

typedef struct Node{
	int a;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct LinkedList{
	Node *head;
	Node *end;
	void (*push)(int a, struct LinkedList *LL);
	void (*printList)(struct LinkedList *LL);
	int (*pop)(struct LinkedList *LL);
	void (*inject)(int a, struct LinkedList *LL);
	int (*eject)(struct LinkedList *LL);
} LinkedList;

void createList(struct LinkedList *ll);

void deleteList(LinkedList *ll);

#endif

void push(int a, LinkedList *LL){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->a = a;
	ll->next = LL->head;
	ll->prev = NULL;
	if(LL->head == NULL) LL->end = ll;
	else LL->head->prev = ll;
	LL->head = ll;
}

void inject(int a, LinkedList *LL){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->a = a;
	ll->next = NULL;
	ll->prev = LL->end;
	if(LL->end == NULL) LL->head = ll;
	else LL->end->next = ll;
	LL->end = ll;
}

void freeNode(Node *n){
	free(n);
}

int pop(LinkedList *LL){
	int returnval;
	if(LL->head==NULL){
		return -1;
	}
	else{
		Node *tmp = LL->head;
		returnval = tmp->a;
		LL->head = LL->head->next;
		if(LL->head == NULL) LL->end = NULL;
		else LL->head->prev = NULL;
		free(tmp);
	}
	return returnval;
}

int eject(LinkedList *LL){
	int returnval;
	if(LL->end==NULL) {
		return -1;
	}
	else{
		Node *tmp = LL->end;
		returnval = tmp->a;
		LL->end = LL->end->prev;
		if(LL->end == NULL) LL->head = NULL;
		else LL->end->next = NULL;
		free(tmp);
	}
	return returnval;
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
	ll->pop = &pop;
	ll->inject = &inject;
	ll->eject = &eject;
}
