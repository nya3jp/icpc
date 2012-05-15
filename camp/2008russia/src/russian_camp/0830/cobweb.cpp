#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "cobweb"

struct Edge {
  int a, b;
};

int find_root(int* uf, int a) {
  return (uf[a] < 0 ? a : uf[a] = find_root(uf, uf[a]));
}
bool unite(int* uf, int a, int b) {
  int ra = find_root(uf, a);
  int rb = find_root(uf, b);
  if (ra != rb) {
    if (uf[ra] > uf[rb])
      swap(ra, rb);
    uf[ra] += uf[rb];
    uf[rb] = ra;
  }
  return (ra != rb);
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  scanf("%d%d", &n, &m);

  Edge edges[m];
  REP(i, m) {
    Edge& e = edges[i];
    scanf("%d%d", &e.a, &e.b);
    e.a--;
    e.b--;
  }

  int k;
  scanf("%d", &k);

  bool alive[m];
  REP(i, m)
    alive[i] = true;

  int breaks[k];
  REP(i, k) {
    scanf("%d", &breaks[i]);
    breaks[i]--;
    alive[breaks[i]] = false;
  }

  int uf[n];
  REP(i, n)
    uf[i] = -1;

  int c = n;
  REP(i, m)
    if (alive[i])
      if (unite(uf, edges[i].a, edges[i].b))
	c--;

  int res[k];
  for(int q = k-1; q >= 0; q--) {
    res[q] = c;
    if (unite(uf, edges[breaks[q]].a, edges[breaks[q]].b))
      c--;
  }

  REP(i, k)
    printf("%d%c", res[i], (i == k-1 ? '\n' : ' '));

  return 0;
}

