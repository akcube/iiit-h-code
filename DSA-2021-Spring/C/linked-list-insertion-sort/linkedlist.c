#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "linkedlist.h"

void createElement(char *s, LinkedList *LL){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->str = strdup(s);
	ll->next = LL->head;
	ll->prev = NULL;
	if(LL->head)
		(LL->head)->prev = ll;
	LL->head = ll;
}

void freeNode(Node *n){
	free(n->str);
	free(n);
}

int deleteElement(char *content, LinkedList *LL){
	
	for(Node *prev = NULL, *cur = (LL->head); cur; prev = cur, cur = cur->next){
		if(strcmp(content, cur->str)==0){
			if(cur->next){
				(cur->next)->prev = prev;
			}
			if(prev){
				prev->next = NULL;
				prev->next = cur->next;
			}
			else{
				(LL->head) = cur->next;
			}
			freeNode(cur);
			return 1;
		}
	}
	return -1;
}

void printList(LinkedList *LL){

	for(Node *cur = (LL->head); cur ;cur = cur->next)
		printf("%s<->", cur->str);

	printf("NULL\n");
}

char *getElement(char *content, LinkedList *LL){
	
	for(Node *cur = (LL->head); cur!=NULL; cur = cur->next)
		if(strcmp(content, cur->str)==0)
			return cur->str;

	return NULL;
}


void insertionSortList(LinkedList *LL){
	if(LL->head == NULL)
		return;
	
	Node *cur = LL->head->next;
	Node *trv, *cnext;

	while(cur!=NULL){
		trv = LL->head;
		cnext = cur->next;

		do{
			if(strcmp(trv->str, cur->str) > 0){
				Node *cprev = cur->prev;
				cprev->next = cur->next;
				
				if(cur->next!=NULL)
					cur->next->prev = cprev;

				if(trv->prev != NULL){
					trv->prev->next = cur;
				}
				else{
					LL->head = cur;
				}

				cur->prev = trv->prev;
				trv->prev = cur;
				cur->next = trv;
				break;
			}
			trv = trv->next;
		}
		while(trv!=cnext);

		cur = cnext;
	}
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
	ll->createElement = &createElement;
	ll->getElement = &getElement;
	ll->deleteElement = &deleteElement;
	ll->printList = &printList;
	ll->insertionSortList = &insertionSortList;
}
