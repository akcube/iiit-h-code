#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct node{
	int val;
	struct node *next;
} node;

node *head;

void insert(int input){
	node *newNode = (node*) malloc(sizeof(node));
	newNode->val = input;

	newNode->next = head;
	head = newNode;
}

bool del(int input){
	node *trv = head;
	node *prev = NULL;
	while(trv!=NULL){
		if(trv->val==input){
			if(prev==NULL){
				head = trv->next;
				free(trv);
				return true;
			}
			else{
				prev->next = trv->next;
				free(trv);
				return true;
			}	
		}
		prev = trv;
		trv = trv->next;
	}
	return false;
}

int find(int input){
	node *trv = head;
	int id = 0;
	while(trv!=NULL){
		if(trv->val==input){
			return id;
		}
		id++;
		trv = trv->next;
	}
	return -1;
}

void print(){
	node *trv = head;
	while(trv!=NULL){
		printf("%d->", trv->val);
		trv=trv->next;
	}
	printf("\n");
}

int main(void){
	
	insert(2);
	insert(3);
	insert(9);
	insert(1);
	insert(3);
	print();
	printf("%d\n", find(9));
	printf("%d\n", find(0));
	del(2);
	del(3);
	print();
}