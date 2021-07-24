#ifndef _MY_UNBALANCED_BST_
#define _MY_UNBALANCED_BST_

typedef struct node{
	int key;
	//int subtree_size;
	char *val;
	struct node *parent;
	struct node *leftc;
	struct node *rightc;
}node;

typedef struct BST{
	node *root;
	void (*printTree)(struct BST *bst);
	char* (*search)(int key, struct BST *bst);
	void (*delete)(int key, struct BST *bst);
	void (*insert)(int key, char *value, struct BST *bst);
} BST; 


void printTree(struct BST *bst);

char *search(int key, struct BST *bst);

void delete(int key, struct BST *bst);

void insert(int key, char *value, struct BST *bst);

void deleteTree(struct BST *bst);

void createTree(struct BST *bst);

#endif