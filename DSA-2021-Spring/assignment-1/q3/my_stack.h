#ifndef _MYLINKEDLIST_
#define _MYLINKEDLIST_

typedef struct Complex{
	int success;
	double x;
	double y;
} Complex;

typedef struct Node{
	double x;
	double y;
	struct Node *next;
} Node;

typedef struct LinkedList{
	Node *head;
	void (*push)(double x, double y, struct LinkedList *LL);
	void (*printList)(struct LinkedList *LL);
	Complex (*pop)(struct LinkedList *LL);
} LinkedList;

void createList(struct LinkedList *ll);

void deleteList(LinkedList *ll);

#endif