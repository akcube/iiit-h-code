#include<bits/stdc++.h>

using namespace std;

#define N  4096000
#define NN 4095999

bitset<4096000> bs;

//djb2
unsigned long h1(unsigned char *str){
    unsigned long djb2 = 5381;
    int c;
    while ((c = *str++))
        djb2 = ((djb2 << 5) + djb2) + c; /* djb2 * 33 + c */
    return djb2&NN;
}

//sdbm
unsigned long h2(unsigned char *str){
    unsigned long sdbm = 0;
    int c;
    while ((c = *str++))
        sdbm = c + (sdbm << 6) + (sdbm << 16) - sdbm;
    return sdbm;
}

//fnv-1a
unsigned long h3(unsigned char *str){
    unsigned long fnv1a = 0xcbf29ce484222325;
    int c;
    while ((c = *str++))
        fnv1a = (fnv1a^c)*0x100000001b3;
    return fnv1a;
}

//void ult hash
void hashfn(unsigned char *str, unsigned long *h1, unsigned long *h2, unsigned long *h3){
    unsigned long djb2 = 5381;
    unsigned long sdbm = 0;
    unsigned long fnv1a = 0xcbf29ce484222325;
    int c;
    while ((c = *str++)!='\n'&&c!='\0'){
  	    djb2 = ((djb2 << 5) + djb2) + (c|0x20); /* djb2 * 33 + (c|0x20) */
        sdbm = (c|0x20) + (sdbm << 6) + (sdbm << 16) - sdbm;
        fnv1a = (fnv1a^(c|0x20))*0x100000001b3;
    }
    *h1 = djb2&NN;
    *h2 = sdbm&NN;
    *h3 = fnv1a&NN;
}

void bloomAdd(unsigned char *word){
	unsigned long h1, h2, h3;
	hashfn(word, &h1, &h2, &h3);
	bs.set(h1, true);
	bs.set(h2, true);
	bs.set(h3, true);
}

bool bloomCheck(unsigned char *word){
	unsigned long h1, h2, h3;
	hashfn(word, &h1, &h2, &h3);
	return (bs[h1] && bs[h2] && bs[h3]);
}