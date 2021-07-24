#ifndef _MYLINKEDLIST_
#define _MYLINKEDLIST_

typedef struct Node{
	char *str;
	struct Node *next;
	struct Node *prev; 
} Node;

typedef struct LinkedList{
	Node *head;
	void (*createElement)(char *s, struct LinkedList *LL);
	void (*printList)(struct LinkedList *LL);
	int (*deleteElement)(char* content, struct LinkedList *LL);
	char* (*getElement)(char* content, struct LinkedList *LL);
	void (*insertionSortList)(struct LinkedList *LL);
} LinkedList;

void createElement(char *s, struct LinkedList *LL);

int deleteElement(char *content, struct LinkedList *LL);

void printList(struct LinkedList *LL);

char* getElement(char *content, struct LinkedList *LL);

void createList(struct LinkedList *ll);

void deleteList(LinkedList *ll);

void insertionSortList(LinkedList *LL);

#endif