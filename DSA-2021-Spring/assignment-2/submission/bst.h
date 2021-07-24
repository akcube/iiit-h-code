#ifndef __UNBALANCED_BST
#define __UNBALANCED_BST

typedef struct Node{
	int data;
	int height;
	struct Node *left;
	struct Node *right;
} Node;

void finddepth(Node *root, Node *data);
void bstsort(Node *curr);
void inRange(Node *curr, int lower_bound, int upper_bound);
void height(Node *curr);
void isbst(Node *curr);
Node* insert(int data, Node *cur);
void deleteBST(Node *n);

#endif