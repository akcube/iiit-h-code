#include "bst.h"
#include<stdlib.h>
#include<stdio.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

int max(int a, int b){
	return (a>b)?a:b;
}

//=======================================================================

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


//=========================================================


int __finddepth(Node *curr, Node *data){
	if(curr==NULL) return -1;
	if(curr==data) return 0;
	int d = -1;
	
	d = __finddepth(curr->left, data);
	if(d!=-1) return d+1;
	
	d = __finddepth(curr->right, data);
	if(d!=-1) return d+1;

	return d;
}

void finddepth(Node *root, Node *data){
	printf("%d\n", __finddepth(root, data));
}

void bstsort(Node *curr){
	if(!curr) return;
	if(curr->left) bstsort(curr->left);
	printf("%d ", curr->data);
	if(curr->right) bstsort(curr->right);
}

int __isbst(Node *curr, int l, int r){
	
    if(!curr) return 1;
    int b = 1;

	if(curr->data > l && curr->data < r){
        b &= __isbst(curr->left, l, curr->data);
        b &= __isbst(curr->right, curr->data, r);
    }
    else{
        b = 0;
    }
	return b;
}

void isbst(Node *curr){
    printf("%d", __isbst(curr, INT_MIN, INT_MAX));
}

void inRange(Node *curr, int lower_bound, int upper_bound){
	if(curr==NULL) return;

	inRange(curr->left, lower_bound, upper_bound);
	if(curr->data >= lower_bound && curr->data <= upper_bound)
		printf("%d ", curr->data);
	inRange(curr->right, lower_bound, upper_bound);
}

int __height(Node *curr){
	if(curr==NULL) 
		return -1;
	else 
		return (max(__height(curr->left), __height(curr->right))+1);
}

void height(Node *curr){
	printf("%d\n", __height(curr));
}
