#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "idempotent"

#define MOD 1000000007

#define N 200000

int v[N];
int res = 1;

inline void mul(int k) {
  res = (int)((long long)res * k % MOD);
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n;
  scanf("%d", &n);
  REP(i, n) {
    int x;
    scanf("%d", &x);
    x--;
    v[x]++;
  }

  int m = n;
  REP(i, n) {
    if (v[i] > 0) {
      m--;
      mul(v[i]);
    }
  }
  for(int i = m; i >= 1; i--)
    mul(i);

  printf("%d\n", res);

  return 0;
}
