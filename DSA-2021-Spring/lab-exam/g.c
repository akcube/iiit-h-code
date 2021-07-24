#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

#define tc int t; scanf("%d", &t); while(t--)

#ifndef __UNBALANCED_BST
#define __UNBALANCED_BST

typedef struct node{
	int crp;
	int ct;
	int height;
	int count;
	int subtree_sz;
	struct node *leftChild;
	struct node *rightChild;
} node;

typedef struct BST{
	node *root;
	int size;
} BST;

#endif

int max(int a, int b){
	return (a>b)?a:b;
}

node* mnode(int crp, int ct, int height){
	node *new = malloc(sizeof(node));
	new->rightChild = NULL;
	new->leftChild = NULL;
	new->crp = crp;
	new->ct = ct;
	new->count = 0;
	new->subtree_sz = 0;
	new->height = height;
	return new;
}

node* __insert(int crp, int ct, node *cur){
	
	if(cur==NULL)
		return mnode(crp, ct, 0);
	if(cur->crp==crp) {
		cur->count++;
		return cur;
	}
	
	if(crp < cur->crp){
		cur->leftChild = __insert(crp, ct, cur->leftChild);
		
		if(cur->rightChild)
			cur->height = 1 + max(cur->rightChild->height, cur->leftChild->height);
		else
			cur->height = 1 + cur->leftChild->height;
		cur->subtree_sz++;
	}
	else{
		cur->rightChild = __insert(crp, ct, cur->rightChild);

		if(cur->leftChild)
			cur->height = 1 + max(cur->leftChild->height, cur->rightChild->height);
		else
			cur->height = 1 + cur->rightChild->height;
		cur->subtree_sz++;
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

int main(void){
	
	int q, t;
	scanf("%d %d", &q, &t);

	for(int i=0; i<q; i++){
		char query;
		int crp, ct;
		scanf(" %c", &query);
		if(query=='+'){

		}
	}

}