#ifndef __UNBALANCED_BST
#define __UNBALANCED_BST

typedef struct Node{
	int data;
	int height;
	struct Node *left;
	struct Node *right;
} Node;

Node* insert(int key, Node *cur);
void deleteBST(Node *n);

#endif