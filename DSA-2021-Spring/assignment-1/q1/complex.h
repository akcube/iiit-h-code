#ifndef __LIB_COMPLEX_NUM
#define __LIB_COMPLEX_NUM

typedef long long ll;

typedef struct Complex{
	int _dim;
	ll *_val;

	ll (*getVal)(int dim, struct Complex *this);
	int (*getDim)(int dim, struct Complex *this);

	void (*setDimen)(int n, struct Complex *this);
	void (*setVal)(ll val, int dim, struct Complex *this);
	
	void (*add)(struct Complex inp, struct Complex *this);
	void (*sub)(struct Complex inp, struct Complex *this);
	double (*mod)(struct Complex *this);
	ll (*dotProd)(struct Complex inp, struct Complex *this);

	void (*read)(int dim, struct Complex *this);
	void (*print)(struct Complex *this);

} Complex;

void initComplex(Complex *obj);
void destroyComplex(Complex *this);


#endif