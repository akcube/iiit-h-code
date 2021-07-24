#ifndef _MYLINKEDLIST_
#define _MYLINKEDLIST_

#include "intelem.h"

typedef struct Node{
	int val;
	struct Node *next;
} Node;

typedef struct LinkedList{
	Node *head;
	void (*createElement)(ElementType val, struct LinkedList *LL);
	void (*printList)(struct LinkedList *LL);
	int (*deleteAll)(ElementType val, struct LinkedList *LL);
	int (*findLast)(ElementType val, struct LinkedList *LL);
} LinkedList;

void createList(struct LinkedList *ll);

void deleteList(LinkedList *ll);

#endif