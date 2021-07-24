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
	struct Node *prev;
} Node;

typedef struct LinkedList{
	Node *head;
	Node *end;
	void (*push)(double x, double y, struct LinkedList *LL);
	void (*printList)(struct LinkedList *LL);
	Complex (*pop)(struct LinkedList *LL);
	void (*inject)(double x, double y, struct LinkedList *LL);
	Complex (*eject)(struct LinkedList *LL);
} LinkedList;

void createList(struct LinkedList *ll);

void deleteList(LinkedList *ll);

#endif