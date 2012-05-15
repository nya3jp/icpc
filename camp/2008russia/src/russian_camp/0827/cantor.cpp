#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

#define NAME "cantor"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

int main() {

  const int K = 1000000;

  for(int n = 4; n <= 4; n++) {
    double s = 0;
    REP(i, K)
      s += pow(f((double)i/K), (double)n) / K;
    printf("%.10f\n", s);
    for(int p = 1; p <= 1000; p++) {
      for(int q = p; q <= 1000; q++) {
	if (abs(s-(double)p/q) < 0.0001)
	  printf("  %d/%d = %.10f\n", p, q, (double)p/q);
      }
    }
  }

  return 0;

  if (!freopen(NAME ".in", "r", stdin))
    abort();
  if (!freopen(NAME ".out", "w", stdout))
    abort();

  return 0;
}
