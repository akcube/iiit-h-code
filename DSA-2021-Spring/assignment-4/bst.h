#ifndef __UNBALANCED_BST
#define __UNBALANCED_BST

typedef struct node{
	int key;
	int height;
	int ct;
	struct node *leftChild;
	struct node *rightChild;
} node;

typedef struct BST{
	node *root;
	int size;
	void (*insert)(long long key, struct BST *bst);
	long long (*getCount)(long long key, struct BST *bst);
} BST;

void deleteBST(BST *bst);
void createBST(BST *bst);

#endif