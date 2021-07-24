#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MOD 1000000007

char a[100001];
char b[100001];

int prefixa[100001];
int prefixb[100001];

int p[100001];

int max(int a, int b);
int min(int a, int b);
void precompPowers(int n);
void calcPrefix(int len, char *str, int *prefix);
int getHash(int start, int end, int *prefix);

inline int min(int a, int b) { return (a<b)?a:b; }
inline int max(int a, int b) { return (a>b)?a:b; }

void precompPowers(int n){
	p[0] = 1;
	for(int i=1; i<=n; i++)
		p[i] = (1ll*p[i-1]*31)%MOD;
}

void calcPrefix(int len, char *str, int *prefix){
	prefix[0] = 0;
	prefix[1] = str[0];
	for(int i=2; i<=len; i++)
		prefix[i] = (prefix[i-1]+(1ll*str[i-1]*p[i-1])%MOD)%MOD;
}

inline int getHash(int start, int end, int *prefix){
	return (prefix[end+1]-prefix[start]+MOD)%MOD;
}

bool checkGenerator(int len, int n, int *prefix){
	int j;
	for(j=len; j+j<=n; j<<=1)
		if((1ll*prefix[j]*p[j])%MOD!=getHash(j, j+j-1, prefix))
			return false;
	if(j<n){
		int suffixhash = getHash(j, n-1, prefix);
		int prefixhash = getHash(0, n-j-1, prefix);
		if((1ll*prefixhash*p[j])%MOD!=suffixhash)
			return false;
	}
	return true;
}

signed main(void){
	int lena, lenb;
	scanf(" %s%n%*c", a, &lena);
	scanf(" %s%n%*c", b, &lenb);

	precompPowers(max(lena, lenb)+1);
	calcPrefix(lena, a, prefixa);
	calcPrefix(lenb, b, prefixb);
	int n = min(lena, lenb);
	int ct = 0;

	for(int i=1; i<=n; i++){
		if(lena%i!=0 || lenb%i!=0) continue;
		if(prefixa[i]!=prefixb[i]) break;
		bool generator = checkGenerator(i, lena, prefixa);
		generator &= checkGenerator(i, lenb, prefixb);
		if(generator) ct++;
	}
	printf("%d\n", ct);
}

