#include <iostream>
#include <cstdio>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "jedi"

int inv(int a, int p) {
  return (a == 1 ? 1 : (1-p*inv(p%a, a))/a+p);
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, r;
  cin >> n >> r;

  int** v = new int*[n];
  REP(i, n)
    v[i] = new int[n];

  REP(i, n) REP(j, n)
    cin >> v[i][j];

  int res = 1;
  REP(p, n) {
    for(int i = p; i < n; i++)
      if (v[i][p] > v[p][p])
	swap(v[i], v[p]);
    if (v[p][p] == 0) {
      res = 0;
      break;
    }
    res = res * v[p][p] % r;
    {
      int w = inv(v[p][p], r);
      REP(j, n)
	v[p][j] = v[p][j] * w % r;
    }
    for(int i = p+1; i < n; i++) {
      int w = v[i][p];
      REP(j, n)
	v[i][j] = (v[i][j] + (r - w * v[p][j] % r)) % r;
    }
  }
  REP(i, n)
    res = (res * 2) % r;

  cout << res << endl;

  return 0;
}

