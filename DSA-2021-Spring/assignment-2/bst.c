#include<stdio.h>
#include "bst.h"
#include<stdbool.h>
#include<stdlib.h>

int max(int a, int b){
	return (a>b)?a:b;
}

node* mnode(int key, int height){
	node *new = malloc(sizeof(node));
	new->rightChild = NULL;
	new->leftChild = NULL;
	new->key = key;
	new->height = height;
	return new;
}

node* __insert(int key, node *cur){
	
	if(cur==NULL)
		return mnode(key, 0);
	if(cur->key==key) 
		return cur;
	
	if(key < cur->key){
		cur->leftChild = __insert(key, cur->leftChild);
		
		if(cur->rightChild)
			cur->height = 1 + max(cur->rightChild->height, cur->leftChild->height);
		else
			cur->height = 1 + cur->leftChild->height;
	}
	else{
		cur->rightChild = __insert(key, cur->rightChild);

		if(cur->leftChild)
			cur->height = 1 + max(cur->leftChild->height, cur->rightChild->height);
		else
			cur->height = 1 + cur->rightChild->height;
	}

	return cur;
}

node *__search(int key, node *curr){

	if(curr->key==key) return curr;
	if(!curr) return NULL;

	if(key < curr->key) 
		return __search(key, curr->leftChild);
	else 
		return __search(key, curr->rightChild);
}

int __getDepth(node *curr, int key, int depth){
	if(curr->key==key) return depth;
	if(key < curr->key) 
		return __getDepth(curr->leftChild, key, depth+1);
	else 
		return __getDepth(curr->rightChild, key, depth+1);
}

void __printInOrder(node *curr){
	if(!curr) return;
	
	if(curr->leftChild) __printInOrder(curr->leftChild);
	printf("%d ", curr->key);
	if(curr->rightChild) __printInOrder(curr->rightChild);
}

bool __isBST(node *curr){
	if(!curr) return true;
	bool isbst = true;
	if(curr->leftChild){
		if(curr->key > curr->leftChild->key)
			isbst &= __isBST(curr->leftChild);
		else 
			return false;
	}
	if(curr->rightChild){
		if(curr->key < curr->rightChild->key)
			isbst &= __isBST(curr->rightChild);
		else
			return false;
	}
	return isbst;
}

void __deleteBST(node *n){
	if(n==NULL) return;
	__deleteBST(n->leftChild);
	__deleteBST(n->rightChild);
	free(n);
}

void __inRange(node *curr, int lower_bound, int upper_bound){
	if(curr==NULL) return;
	if(curr->key >= lower_bound)
		__inRange(curr->leftChild, lower_bound, upper_bound);
	if(curr->key >= lower_bound && curr->key <= upper_bound)
		printf("%d ", curr->key);
	if(curr->key <= upper_bound)
		__inRange(curr->rightChild, lower_bound, upper_bound);
}

bool isBST(BST *bst){
	if(bst->root==NULL) return false;
	else return __isBST(bst->root);
}

void insert(int key, BST *bst){
	if(bst->root==NULL) 
		bst->root = mnode(key, 0);
	else
		bst-> root = __insert(key, bst->root);
}

int getDepth(BST *bst, node *p){
	if(bst->root==NULL || p==NULL) return -1;
	else 
		return __getDepth(bst->root, p->key, 0);
}

int height(BST *bst){
	if(bst->root==NULL) 
		return 0;
	else 
		return bst->root->height;
}

void printInOrder(BST *bst){
	if(bst->root==NULL) printf("Empty tree\n");
	else __printInOrder(bst->root);
	printf("\n");
}

void inRange(BST *bst, int lower_bound, int upper_bound){
	if(bst->root == NULL) printf("Empty tree\n");
	else __inRange(bst->root, lower_bound, upper_bound);
	printf("\n");
}

void deleteBST(BST *bst){
	if(bst->root==NULL) return;
	__deleteBST(bst->root);
	bst->root = NULL;
}

