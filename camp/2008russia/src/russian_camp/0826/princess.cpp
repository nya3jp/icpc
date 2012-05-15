#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

int main() {

  long double ld[50];

  ld[0] = 0;
  for(int k = 1; k < 50; k++) {
    ld[k] = pow((long double)(k+1)/k, k*(k+1));
  }

  if (!freopen("princess.in", "r", stdin))
    abort();
  if (!freopen("princess.out", "w", stdout))
    abort();

  long long n;
  cin >> n;

  int k = 0;
  while(ld[k+1] <= n)
    k++;
  k++;

  long double x = k*pow( (long double)n, (long double)1.0/k);

  printf("%.6f\n", (double)x);

  return 0;
}

