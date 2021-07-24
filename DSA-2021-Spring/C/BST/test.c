#include<stdio.h>
#include "bst-unbalanced.h"

int main(void){
	BST mytree;
	createTree(&mytree);
	
	mytree.insert(7, "a", &mytree);
	mytree.insert(2, "b", &mytree);
	mytree.insert(9, "c", &mytree);
	mytree.insert(14, "d", &mytree);
	mytree.insert(1, "e", &mytree);
	mytree.insert(8, "f", &mytree);
	mytree.insert(5, "g", &mytree);
	
	mytree.printTree(&mytree);	
	printf("\n\n");

	deleteTree(&mytree);

	mytree.printTree(&mytree);
}