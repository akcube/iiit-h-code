#include<stdio.h>
#include "bst.h"
#include<stdbool.h>
#include<stdlib.h>

long long max(long long a, long long b){
	return (a>b)?a:b;
}

node* mnode(long long key, long long height){
	node *new = malloc(sizeof(node));
	new->rightChild = NULL;
	new->leftChild = NULL;
	new->key = key;
	new->ct = 0;
	new->height = height;
	return new;
}

node* __insert(long long key, node *cur){
	
	if(cur==NULL)
		return mnode(key, 0);
	if(cur->key==key){ 
		cur->ct = cur->ct+1;
		return cur;
	}
	
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

node *__search(long long key, node *curr){

	if(!curr) return NULL;
	if(curr->key==key) return curr;

	if(key < curr->key) 
		return __search(key, curr->leftChild);
	else 
		return __search(key, curr->rightChild);
}

void __deleteBST(node *n){
	if(n==NULL) return;
	__deleteBST(n->leftChild);
	__deleteBST(n->rightChild);
	free(n);
}

long long getCount(long long key, BST *bst){
	node *found = __search(key, bst->root);
	if(found==NULL) return 0;
	else return found->ct;
}

void insert(long long key, BST *bst){
	if(bst->root==NULL) 
		bst->root = mnode(key, 0);
	else
		bst->root = __insert(key, bst->root);
}

void deleteBST(BST *bst){
	if(bst->root==NULL) return;
	__deleteBST(bst->root);
	bst->root = NULL;
}

void createBST(BST *bst){
	bst->root = NULL;
	bst->size = 0;
	bst->insert = insert;
	bst->getCount = getCount;
}
