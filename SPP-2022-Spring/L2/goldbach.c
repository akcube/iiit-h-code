#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define N 10000000
#define TOT_PRIMES 664579
int lp[N+1];
int pr[664579];

bool is_prime(int p);
inline bool is_prime(int p) { return p >= 2 && lp[p] == p; }

void prec(){
  int psz = 0;
  for (int i=2; i <= N; ++i) {
      if (lp[i] == 0) {
          lp[i] = i;
          pr[psz++] = i;
      }
      for (int j=0; j < psz && pr[j] <= lp[i] && i*pr[j] <= N; ++j) {
          lp[i * pr[j]] = pr[j];
      }
  }
}

bool verify_odd_goldbach(int n) {
  assert(n%2 == 1);
  for(int i=0; i<TOT_PRIMES; i++)
    for(int j=i; j<TOT_PRIMES; j++)
      if(is_prime(n - (pr[i] + pr[j]))){
        // printf("%d: %d + %d + %d\n", n, pr[i], pr[j], n - (pr[i]+pr[j]));
        return true;
      }
  return false;
}

bool verify_even_goldbach(int n) {
  assert(n%2 == 0);
  for(int i=0; i<TOT_PRIMES; i++)
    if(is_prime(n - pr[i])){
      // printf("%d: %d + %d\n", n, pr[i], n - pr[i]);
      return true;
    }
  return false;
}

bool verify_goldbach(int n){
  return (n%2 == 0) ? verify_even_goldbach(n) : verify_odd_goldbach(n);
}

int main(void) {
  prec();
  for(int i=6; i<=5000; i++){
    if(i % 500 == 0) printf("Goldbach verified till: %d\n", i);
    if(!verify_goldbach(i)){
      printf("Goldbach failed for: %d\n", i);
      return 0;
    }
  }
}