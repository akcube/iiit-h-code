#include<stdio.h>
#include "betterbst.h"
#include<stdbool.h>
#include<stdlib.h>

int max(int a, int b){
	return (a>b)?a:b;
}

Node* mNode(int data, int height){
	Node *new = malloc(sizeof(Node));
	new->right = NULL;
	new->left = NULL;
	new->data = data;
	new->height = height;
	return new;
}

Node* insert(int data, Node *cur){
	
	if(cur==NULL)
		return mNode(data, 0);
	if(cur->data==data) 
		return cur;
	
	if(data < cur->data){
		cur->left = insert(data, cur->left);
		
		if(cur->right)
			cur->height = 1 + max(cur->right->height, cur->left->height);
		else
			cur->height = 1 + cur->left->height;
	}
	else{
		cur->right = insert(data, cur->right);

		if(cur->left)
			cur->height = 1 + max(cur->left->height, cur->right->height);
		else
			cur->height = 1 + cur->right->height;
	}

	return cur;
}

void deleteBST(Node *n){
	if(n==NULL) return;
	deleteBST(n->left);
	deleteBST(n->right);
	free(n);
}
