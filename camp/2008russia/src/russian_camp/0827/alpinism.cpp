#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define NAME "alpinism"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

int v[100009];
int n;
int u0[2][100009];

int go(int* u) {
  int m = 0;
  int lo = 0, hi = 0;
  int dir = 0;
  REP(i, n) {
    int y = v[i];
    if (y > hi) {
      if (dir == -1)
	m++;
      u[m] = y;
      dir = 1;
    }
    if (y < lo) {
      if (dir == 1)
	m++;
      u[m] = y;
      dir = -1;
    }
    hi >?= y;
    lo <?= y;
  }
  m++;
  return m;
}

int main() {

  if (!freopen(NAME ".in", "r", stdin))
    abort();
  if (!freopen(NAME ".out", "w", stdout))
    abort();

  scanf("%d", &n);
  REP(i, n)
    scanf("%d", &v[i]);

  int m0 = go(u0[0]);
  reverse(v, v+n);
  int m1 = go(u0[1]);
  /*
  REP(i, m0)
    cerr << u0[0][i] << " ";
  cerr << endl;
  REP(i, m1)
    cerr << u0[1][i] << " ";
  cerr << endl;
  */
  puts(m0 == m1 && equal(u0[0], u0[0]+m0, u0[1]) ? "YES" : "NO");

  return 0;
}
