#ifndef __AVLTREE_H
#define __AVLTREE_H

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;
typedef struct AVLNode* AVLTree;
typedef AVLTree Position;

int SIZE = 0;

struct AVLNode {
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int count;
    int Height;
};

AVLTree Insert(AVLTree T, ElementType X);
AVLTree Delete(AVLTree T, ElementType X);

Position Find(AVLTree T, ElementType X);
Position FindMin(AVLTree T);
Position FindMax(AVLTree T);

ElementType GetElement(Position P);

#endif

int max(int a, int b) { return (a>b)?a:b; }
bool IsSmaller(int a, int b) { return a < b; }
bool IsLarger(int a, int b) { return a > b; }

int Height(Position P)
{
	if( P == NULL )
		return -1;
	else
		return P->Height;
}


AVLTree MakeNode(ElementType X)
{
    AVLTree T = (AVLTree)malloc(sizeof(struct AVLNode));
    assert( T != NULL);
    T->Element = X;
    T->Left = NULL;
    T->Right = NULL;
    T->count = 0;
    return T;
}


// AVLTree Insert(AVLTree T, ElementType X)
// {

//     if( T == NULL)
//         T = MakeNode(X);
//     else if ( IsSmaller(X,T->Element) ) // X < T->Element
//         T->Left = Insert(T->Left,X);
//     else if ( IsLarger(X,T->Element) )  // X > T->Element
//         T->Right = Insert(T->Right,X);
//     return T;
// }

Position SingleRotateWithLeft(Position k2)
{
	Position k1;
	
	k1 = k2->Left;
	k2->Left = k1->Right;
	k1->Right = k2;

	k2->Height = max(Height(k2->Left),Height(k2->Right)) + 1;
	k1->Height = max(Height(k1->Left),k2->Height) + 1;

	return k1; // new root
}

Position DoubleRotateWithLeft(Position k2)
{
	// Rotate between k3 and k1
	k2->Left = SingleRotateWithLeft(k2->Left);
	// Rotate between k1 and k2
	return SingleRotateWithLeft(k2);
}

//========================================================

Position SingleRotateWithRight(Position k2)
{
	Position k1;
	
	k1 = k2->Right;
	k2->Right = k1->Left;
	k1->Left = k2;

	k2->Height = max(Height(k2->Right),Height(k2->Left)) + 1;
	k1->Height = max(Height(k1->Right),k2->Height) + 1;

	return k1; // new root
}

Position DoubleRotateWithRight(Position k2)
{
	// Rotate between k3 and k1
	k2->Right = SingleRotateWithRight(k2->Right);
	// Rotate between k1 and k2
	return SingleRotateWithRight(k2);
}

//========================================================

AVLTree Insert(AVLTree T, ElementType X)
{
	
    if( T == NULL){
        T = MakeNode(X);
        SIZE++;
    }
    else if ( IsSmaller(X,T->Element) ) // X < T->Element
    {
        T->Left = Insert(T->Left,X);
		// Check if AVL Property has been violated after insertion into left subtree
		if ( (Height(T->Left) - Height(T->Right)) == 2 ) // Violation ! Adjust tree
		{
			if ( IsSmaller(X,T->Left->Element) ) // insertion into left subtree of left child of T
				T = SingleRotateWithLeft(T);
			else  // insertion into right subtree of left child of T
				T = DoubleRotateWithLeft(T);	
		}
	}
	else if ( IsLarger(X,T->Element) )  // X > T->Element
	{
	    T->Right = Insert(T->Right,X);
		// Check if AVL Property has been violated after insertion into right subtree
		if ( (Height(T->Right) - Height(T->Left)) == 2 ) // Violation ! Adjust tree
		{
			if ( IsSmaller(X,T->Right->Element) ) // insertion into left subtree of right child of T
				T = DoubleRotateWithRight(T);
			else  // insertion into right subtree of right child of T
				T = DoubleRotateWithRight(T);
		}
    }
    else{
    	T->count++;
    }
    T->Height = max(Height(T->Left), Height(T->Right)) + 1;

    return T;
	
}