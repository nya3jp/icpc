#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "subway"

#define NO_SOLUTION "No solution"

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  cin >> n >> m;

  int k = max(10*n-9*m-10, 0);
  int a = 1+m-n;

  if (a <= 0 || k > 3*n-2*m-3 || 2*k > 2*n-m) {
    puts(NO_SOLUTION);
    return 0;
  }

  int f = n-k-(a+1);

  int circles[a];
  for(int rem = f, i = 0; i < a; i++) {
    circles[i] = rem / (a-i);
    rem -= circles[i];
  }

  int p = a+2;
  printf("%d\n", a);
  REP(ia, a) {
    printf("%d %d %d", circles[ia]+2, ia+1, ia+2);
    REP(i, circles[ia]) {
      printf(" %d", p++);
    }
    printf("\n");
  }
  assert(p-1 == n-k);

  printf("%d\n", k);
  int q = a+1;
  REP(ik, k) {
    if (q > n-k)
      q = 1;
    printf("%d %d\n", q++, p++);
  }

  assert(p-1 == n);

  return 0;
}
