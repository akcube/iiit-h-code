#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "linkedlist.h"

void createElement(ElementType val, LinkedList *LL){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->val = val;
	ll->next = LL->head;
	LL->head = ll;
}

void freeNode(Node *n){
	if(n)
		free(n);
}

int deleteAll(ElementType val, LinkedList *LL){
	for(Node *prev = NULL, *cur = (LL->head); cur;){
		if(val == cur->val){
			if(prev){
				prev->next = cur->next;
				freeNode(cur);
				cur = prev->next;
			}
			else{
				LL->head = cur->next;
				freeNode(cur);
				cur = LL->head;
			}
						
		}
		else{
			prev = cur;
			cur = cur->next;
		}
	}
}

void printList(LinkedList *LL){

	for(Node *cur = (LL->head); cur ;cur = cur->next)
		printf("%d->", cur->val);

	printf("NULL\n");
}

int findLast(ElementType val, LinkedList *LL){	
	int idx = -1, i = 0;
	for(Node *cur = (LL->head); cur!=NULL; cur = cur->next, i++){
		if(val==cur->val)
			idx = i;
	}
	return idx;
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
	ll->findLast = &findLast;
	ll->deleteAll = &deleteAll;
	ll->printList = &printList;
}
