#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

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

node *createNode(int key, char *val, node *parent){
	node *new = malloc(sizeof(node));
	new->key = key;
	//new->subtree_size = st_sz;
	new->val = strdup(val);
	new->parent = parent;
	new->leftc = NULL;
	new->rightc = NULL;
	return new;
}

void printrec(node *n){
	if(n){
		printrec(n->leftc);
		printf("Key: %3d, Value: %s\n", n->key, n->val);
		printrec(n->rightc);
	}
}

void printTree(BST *bst){
	node *root = bst->root;
	printrec(root);
}

char *search(int key, BST *bst){
	for(node *cur = bst->root; cur; cur = (key > cur->key)?cur->leftc:cur->rightc){
		if(cur->key == key)
			return cur->val;
	}
	return NULL;
}

node** whichChild(node *child){
	if(child->key > child->parent->key)
		return &(child->parent->leftc);
	else
		return &(child->parent->rightc);
}

void delete(int key, BST *bst){
	node *delnode = NULL;
	
	for(node *cur = bst->root; cur; cur = (key > cur->key)?cur->leftc:cur->rightc){
		if(cur->key == key){
			delnode = cur;
			break;
		} 
	}

	if(delnode){
		if(delnode->leftc && delnode->rightc){
			node *repl;
			for(node *trv = delnode->leftc; trv; repl = trv, trv = trv->rightc);
			if(repl != delnode->leftc){
				free(delnode->val);
				delnode->key = repl->key;
				delnode->val = strdup(repl->val);
				*(whichChild(repl)) = NULL;
				free(repl->val);
				free(repl);
			}
			else{
				if(delnode->parent)
					*(whichChild(delnode)) = repl;
				else{
					repl->rightc = delnode->rightc;
					delnode->rightc->parent = repl;
					repl->parent = NULL;
					bst->root = repl;
				}
				free(delnode->val);
				free(delnode);
			}
		}
		else{
			if(delnode->parent)
				*(whichChild(delnode)) = (node*)((uintptr_t)delnode->leftc ^ (uintptr_t)delnode->rightc);
			else{
				bst->root = (node*)((uintptr_t)delnode->leftc ^ (uintptr_t)delnode->rightc);
			}
			free(delnode->val);
			free(delnode);
		}
	}

}

void insert(int key, char *value, BST *bst){
	node *cur = bst->root;
	if(!cur){
		//create root node
		bst->root = createNode(key, value, NULL);
		return;
	}
	node *prev;
	while(cur){
		prev = cur;
		//cur->subtree_size++;
		if(key > cur->key)
			cur = cur->leftc;
		else
			cur = cur->rightc;
	}

	if(key > prev->key)
		prev->leftc = createNode(key, value, prev);
	else 
		prev->rightc = createNode(key, value, prev);
}

void delrec(node *n){
	if(n){
		delrec(n->leftc);
	
		node *temp = n->rightc;
		free(n->val);
		free(n);

		delrec(temp);
	}
}

void deleteTree(BST *bst){
	node *root = bst->root;
	delrec(root);
	bst->root = NULL;
}

void createTree(BST *bst){
	bst->root = NULL;
	bst->printTree = &printTree;
	bst->search = &search;
	bst->delete = &delete;
	bst->insert = &insert;
}
