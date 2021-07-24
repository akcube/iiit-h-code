#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "complex.h"

typedef long long ll;

void setDimen(int n, Complex *this){
	int cur_dim = this->_dim;
	this->_dim = n;
	if(this->_val==NULL)
		this->_val = malloc(sizeof(ll)*n);
	else
		this->_val = realloc(this->_val, sizeof(ll)*n);

	for(int i=cur_dim; i<n; i++) this->_val[i] = 0;
}

void setVal(ll val, int dim, Complex *this){
	this->_val[dim] = val;
}

ll getVal(int dim, Complex *this){
	return this->_val[dim];
}

int getDim(int dim, Complex *this){
	return this->_dim;
}

void add(Complex inp, Complex *this){
	if(inp._dim > this->_dim)
		this->_val = realloc(this->_val, sizeof(ll)*inp._dim);

	for(int i=0; i < inp._dim; i++)
		this->_val[i] += inp._val[i];
}

void sub(Complex inp, Complex *this){
	if(inp._dim > this->_dim)
		this->_val = realloc(this->_val, sizeof(ll)*inp._dim);

	for(int i=0; i < inp._dim; i++)
		this->_val[i] -= inp._val[i];
}

double mod(Complex *this){
	ll sum = 0;
	for(int i=0; i < this->_dim; i++)
		sum += this->_val[i]*this->_val[i];
	printf("%lld\n", sum);
	return sqrt(sum);
}

ll dotProd(Complex inp, Complex *this){
	int n1 = inp._dim;
	int n2 = this->_dim;
	ll dot = 0;
	for(int i=0; i<n1 && i<n2; i++)
		dot += this->_val[i] * inp._val[i];
	return dot;
}

void read(int dim, Complex *this){
	this->setDimen(dim, this);
	for(int i=0; i<dim; i++){
		ll x;
		scanf("%lld", &x);
		this->setVal(x, i, this);
	}
}

void print(Complex *this){
	for(int i=0; i<this->_dim; i++){
		printf("%lld ", this->getVal(i, this));
	}
	printf("\n");
}

void initComplex(Complex *obj){
	obj->getVal = &getVal;
	obj->getDim = &getDim;
	obj->setDimen = &setDimen;
	obj->setVal = &setVal;
	obj->add = &add;
	obj->sub = &sub;
	obj->mod = &mod;
	obj->dotProd = &dotProd;
	obj->read = &read;
	obj->print = &print;
	obj->_dim = 0;
	obj->_val = NULL;
}

void destroyComplex(Complex *this){
	free(this->_val);
}
