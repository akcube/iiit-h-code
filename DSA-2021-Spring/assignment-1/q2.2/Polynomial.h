#ifndef __POLY_H
#define __POLY_H

#include "PolyElem.h"

Poly InitPoly();

int AddTerm(Poly *P,unsigned int exponent,double coeff);
int DeleteTermByExponent(Poly p, unsigned int exp);

int PolyAdd(Poly P1, Poly P2, Poly *ans);
int PolySub(Poly p1,Poly p2, Poly *ans);
Poly getMiddle(Poly p);
int DeleteAllTerms(Poly P);
int DeletePoly(Poly* P);
void PrintPoly(Poly p);

#endif