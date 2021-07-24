#ifndef __UNBALANCED_BST
#define __UNBALANCED_BST

typedef struct node{
	int key;
	int height;
	struct node *leftChild;
	struct node *rightChild;
} node;

typedef struct BST{
	node *root;
	int size;
} BST;

#endif