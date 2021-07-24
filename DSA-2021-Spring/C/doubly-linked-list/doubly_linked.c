#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

typedef struct Node{
	int id;
	char *str; 
	struct Node *next;
	struct Node *prev; 
} Node;

void createElement(int id, char *s, struct Node **head){
	struct Node *ll = malloc(sizeof(struct Node));
	ll->id = id;
	ll->str = malloc(strlen(s)+1);
	strcpy(ll->str, s);
	ll->next = *head;
	ll->prev = NULL;
	if(*head)
		(*head)->prev = ll;
	*head = ll;
}

int deleteElement(int id, struct Node **head){
	struct Node *cur = *head;
	struct Node *prev = NULL;
	while(cur!=NULL){
		if(cur->id==id){
			if(cur->next){
				(cur->next)->prev = prev;
			}
			if(prev){
				prev->next = NULL;
				prev->next = cur->next;
			}
			else{
				*head = cur->next;
			}
			free(cur);
			return 1;
		}
		prev = cur;
		cur = cur->next;	
	}
	return -1;
}

void printList(Node **head){
	Node *cur = *head;
	while(cur){
		printf("%s<->", cur->str);
		cur = cur->next;
	}
	printf("NULL\n");
}

char* getElement(int id, Node **head){
	struct Node *cur = *head;
	while(cur!=NULL){
		if(cur->id==id){
			return cur->str;
		}
		cur = cur->next;	
	}
	return NULL;
}

typedef struct LinkedList{
	Node *head;
	void (*createElement)(int, char *s, struct Node **h);
	void (*printList)(struct Node **h);
	int (*deleteElement)(int id, Node **h);
	char* (*getElement)(int id, Node **h);
} LinkedList;

void init(LinkedList *ll){
	ll->head = NULL;
	ll->createElement = &createElement;
	ll->getElement = &getElement;
	ll->deleteElement = &deleteElement;
	ll->printList = &printList;
}

int main(void){
	LinkedList LL;
	char *temp;
	init(&LL);
	//TESTING :( 
	LL.createElement(5, "hello-1", &LL.head);
	LL.printList(&LL.head);
	LL.createElement(4, "hello-2", &LL.head);
	LL.printList(&LL.head);
	LL.createElement(3, "hello-3", &LL.head);
	LL.printList(&LL.head);
	LL.createElement(2, "hello-4", &LL.head);
	LL.printList(&LL.head);
	LL.createElement(1, "hello-5", &LL.head);
	LL.printList(&LL.head);
	LL.deleteElement(3, &LL.head);
	LL.printList(&LL.head);
	temp = LL.getElement(2, &LL.head);
	printf("%s\n", temp?temp:"Not found");
	LL.deleteElement(1, &LL.head);
	LL.printList(&LL.head);
	temp = LL.getElement(1, &LL.head);
	printf("%s\n", temp?temp:"Not found");
}