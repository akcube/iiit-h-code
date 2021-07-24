#include <stdio.h>
#include <string.h>
#include "complex.h"

typedef long long ll;

typedef enum operation {TYPE_ADD, TYPE_SUB, TYPE_MOD, TYPE_DOT, ERROR} Operation;

int main(void){

	char inp[100];
	scanf("%s", inp);

	Operation op;
	if(strcmp(inp, "ADD")==0) op = TYPE_ADD;
	else if(strcmp(inp, "SUB")==0) op = TYPE_SUB;
	else if(strcmp(inp, "MOD")==0) op = TYPE_MOD;
	else if(strcmp(inp, "DOT")==0) op = TYPE_DOT;
	else {
		printf("Error, invalid input\n");
		return 0;
	}

	int dim;
	scanf("%d", &dim);

	Complex a, b;
	initComplex(&a); 
	initComplex(&b);

	switch(op){
		case TYPE_ADD: 
			a.read(dim, &a);
			b.read(dim, &b);

			a.add(b, &a);
			a.print(&a);
		break;

		case TYPE_SUB:
			a.read(dim, &a);
			b.read(dim, &b);

			a.sub(b, &a);
			a.print(&a);
		break;

		case TYPE_MOD:	
			a.read(dim, &a);
			printf("%lf\n", a.mod(&a));			
		break;

		case TYPE_DOT:
			a.read(dim, &a);
			b.read(dim, &a);
			printf("%lld\n", a.dotProd(b, &a));
		break;
	}

	destroyComplex(&a);
	destroyComplex(&b);
}
