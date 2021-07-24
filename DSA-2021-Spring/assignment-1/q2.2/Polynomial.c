#include "Polynomial.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h> 
#include <assert.h>

Poly InitPoly()
{
    Poly P = (Poly)malloc(sizeof(PTerm));
    assert(P!=NULL);
    P->next = NULL;
    return P;
}

int AddTerm(Poly *P_in,unsigned int exponent,double coeff)
{
    Poly T; 
    Poly P = *P_in;
    T = InitPoly();
    T->expo = exponent;
    T->coeff = coeff;
    if(T==NULL) return 0;
    if(*P_in == NULL){
        *P_in = T;
    }
    else{
        Poly prev = NULL; 
        while(P!=NULL && exponent < P->expo){
            prev = P;
            P = P->next;
        }
        if(P==NULL){
            prev->next = T;
        }
        else if(P->expo==exponent){
            free(T);
            P->coeff = coeff;
        }
        else if(prev==NULL){
            T->next = P;
            *P_in = T;
        }
        else{
            prev->next = T;
            T->next = P;
        }
    }
    return 1;
}

Poly performOp(Poly p1, Poly p2, int sub){
    Poly ans = NULL;
    while(p1!=NULL && p2!=NULL){
        if(p1->expo == p2->expo){
            if(!sub)
                AddTerm(&ans, p1->expo, p1->coeff + p2->coeff);
            else
                AddTerm(&ans, p1->expo, p1->coeff - p2->coeff);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->expo > p2->expo){
            AddTerm(&ans, p1->expo, p1->coeff);
            p1 = p1->next;
        }
        else{
            if(!sub)
                AddTerm(&ans, p2->expo, p2->coeff);
            else 
                AddTerm(&ans, p2->expo, -(p2->coeff));
            p2 = p2->next;
        }
    }
    while(p1!=NULL){
        AddTerm(&ans, p1->expo, p1->coeff);
        p1 = p1->next;
    }
    while(p2!=NULL){
        if(!sub)
            AddTerm(&ans, p2->expo, p2->coeff);
        else
            AddTerm(&ans, p2->expo, -(p2->coeff));
        p2 = p2->next;
    }
    return ans;
}

int DeleteTermByExponent(Poly p, unsigned int exp){
    while(p!=NULL){
        if(p->expo == exp){
            p->coeff = 0;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

int PolyAdd(Poly p1,Poly p2, Poly *ans){
    DeletePoly(ans);  
    if(p1==NULL || p2==NULL) {
        printf("One or more of the inputs don't exist\n");
        return 0;
    }
    *ans = performOp(p1, p2, 0);  
    return 1;
}

int PolySub(Poly p1,Poly p2, Poly *ans){
    DeletePoly(ans);  
    if(p1==NULL || p2==NULL) {
        printf("One or more of the inputs don't exist\n");
        return 0;
    }
    *ans = performOp(p1, p2, 1);  
    return 1;
}

int DeleteAllTerms(Poly p){
    if(p==NULL){
        printf("Polynomial does not exist\n");
        return 0;
    }
    while(p!=NULL){
        p->coeff = 0;
        p=p->next;
    }
    return 1;
}

Poly getMiddle(Poly p){
    Poly prev = p;
    int i = 1;
    while(p!=NULL){
        if(p->coeff==0){
            p=p->next;
            continue;
        }
        if(i%2==1 && i>2){
            prev = prev->next;
        }
        i++;
        p=p->next;
    }
    return prev;
}

int DeletePoly(Poly *p){
    if(*p==NULL) return 0;
    Poly head = *p;
    Poly tmp = head;
    while(head!=NULL){
        head = head->next;
        free(tmp);
        tmp = head;
    }
    *p = NULL;
    return 1;
}

void PrintPoly(Poly p){
    int flag = 0;
    if(p==NULL){
        printf("Polynomial does not exist\n");
        return;
    }
    while(p!=NULL){
        if(p->coeff!=0){
            if(p->expo==INT_MAX){
                p = p->next;
                continue;
            }
            if(flag==0){
                printf("%lg", p->coeff);
            }
            else{
                if(p->coeff<0)
                    printf(" - %lg", -(p->coeff));
                else
                    printf(" + %lg", p->coeff);
            }
            if(p->expo!=0 && p->expo!=1)
                printf("x^%d", p->expo);
            else if(p->expo==1)
                printf("x");
            flag = 1;
        }
        p = p->next;
    }
    if(!flag) printf("0");
    printf("\n");
}



