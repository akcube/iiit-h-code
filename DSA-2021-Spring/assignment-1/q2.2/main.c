#include<stdio.h>
#include<string.h>
#include "Polynomial.h"

Poly pArr[26];

int main(void){
	char inp[100];
	do{
		scanf("%s", inp);
		if(strcmp(inp, "AddTerm")==0){
			char ch;
			int exp;
			double coeff;
			scanf(" %c %d %lg", &ch, &exp, &coeff);
			if(ch<'A'||ch>'Z'){
				printf("Failed\n");
				continue;
			}
			int f = AddTerm(&pArr[ch-'A'], exp, coeff);
			if(f) printf("Done\n");
			else printf("Failed\n");
		}
		else if(strcmp(inp, "PrintPoly")==0){
			char ch;
			scanf(" %c", &ch);
			PrintPoly(pArr[ch-'A']);
		}
		else if(strcmp(inp, "AddPolynomials")==0){
			char c1, c2, c3;
			scanf(" %c %c %c", &c1, &c2, &c3);
			int f = PolyAdd(pArr[c1-'A'], pArr[c2-'A'], &pArr[c3-'A']);
			if(f) printf("Done\n");
		}
		else if(strcmp(inp, "SubtractPolynomials")==0){
			char c1, c2, c3;
			scanf(" %c %c %c", &c1, &c2, &c3);
			int f = PolySub(pArr[c1-'A'], pArr[c2-'A'], &pArr[c3-'A']);
			if(f) printf("Done\n");
		}
		else if(strcmp(inp, "DeleteAllTerms")==0){
			char ch;
			scanf(" %c", &ch);
			int f = DeleteAllTerms(pArr[ch-'A']);
			if(f) printf("Done\n");
		}
		else if(strcmp(inp, "DeleteTermByExponent")==0){
			char ch;
			int exp;
			scanf(" %c %d", &ch, &exp);
			int f = DeleteTermByExponent(pArr[ch-'A'], exp);
			if(f) printf("Done\n");
			else printf("Failed\n");
		}
		else if(strcmp(inp, "DeletePoly")==0){
			char ch;
			scanf(" %c", &ch);
			int f = DeletePoly(&pArr[ch-'A']);
			if(f) printf("Deleted Polynomial %c\n", ch);
			else printf("Polynomial does not exist\n");
		}
		else if(strcmp(inp, "GetMiddle")==0){
			char ch;
			scanf(" %c", &ch);
			Poly a = getMiddle(pArr[ch-'A']);
			if(a==NULL){
				printf("No middle element\n");
			}
			else{
				printf("Middle element is %lg x ^ %d\n", a->coeff, a->expo);
			}
		}
		else{
			printf("Invalid input\n");
			fflush(stdin);
		}
		char ch;
		scanf("%c", &ch);
	}
	while(strcmp(inp, "exit")!=0);

	for(int i=0; i<26; i++){
		DeletePoly(&pArr[i]);
	}
}