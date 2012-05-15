#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


#define PROBLEM_NAME "divisor"

#define MAX_PRIME 31623

int divs[10000+10];
bool isprime[MAX_PRIME+1];
int primes[MAX_PRIME+1];
int nPrimes;
int factors[10000];

int* factorize(int n, int iPrime, int* head) {
  int* tail = head;
  if (iPrime == nPrimes) {
    *tail++ = 1;
    if (n > 1)
      *tail++ = n;
  }
  else {
    int p = primes[iPrime];
    int k = 0;
    while(n % p == 0) {
      n /= p;
      k++;
    }
    tail = factorize(n, iPrime+1, head);
    int m = tail-head;
    REP(i, k) {
      REP(j, m)
	*tail++ = *head++ * p;
    }
  }
  return tail;
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  REP(i, MAX_PRIME+1)
    isprime[i] = (i >= 2);
  nPrimes = 0;
  for(int i = 2; i <= MAX_PRIME; i++) {
    if (isprime[i]) {
      primes[nPrimes++] = i;
      for(int j = 2*i; j <= MAX_PRIME; j+=i)
	isprime[j] = false;
    }
  }

  int nCases;
  scanf("%d", &nCases);

  REP(iCase, nCases) {

    int n, k;
    scanf("%d%d", &n, &k);
    k--;

    int* tail = factorize(n, 0, factors);
    sort(factors, tail);

    printf("%d\n", factors[k]);

  }

  return 0;
}
