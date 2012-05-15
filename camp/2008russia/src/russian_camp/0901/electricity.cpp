#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int rig[1000000+10];
int stock[200000+10];
int children[200000+10];

#define PROBLEM_NAME "electricity"

int mod;

int bitquery(const int* bit, int n, int to) {
  int res = 0;
  for(int k = to-1; k >= 0; k = (k & (k+1)) - 1)
    res = (res + bit[k]) % mod;
  return res;
}

void bitupdate(int* bit, int n, int pos, int delta) {
  while(pos < n) {
    bit[pos] = (bit[pos] + delta) % mod;
    pos |= pos+1;
  }
}

struct Edge {
  int i, j;
};
bool operator<(const Edge& a, const Edge& b) {
  if (a.i != b.i)
    return (a.i < b.i);
  return (a.j > b.j);
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int ni, nj, n;
  scanf("%d%d%d%d", &ni, &nj, &n, &mod);

  Edge v[n];
  REP(i, n) {
    Edge& e = v[i];
    scanf("%d%d", &e.i, &e.j);
    e.i--;
    e.j--;
  }

  sort(v, v+n);

  int from = 0;
  int res = 1;
  int bit[nj];
  memset(bit, 0, sizeof(bit));

  while(from < n) {
    int to = from+1;
    while(to < n && v[from].i == v[to].i)
      to++;
    for(int i = from; i < to; i++) {
      Edge& e = v[i];
      int lo = (bitquery(bit, nj, e.j) + 1) % mod;
      //fprintf(stderr, "(%d,%d) = %d\n", e.i, e.j, lo);
      res = (res + lo) % mod;
      bitupdate(bit, nj, e.j, lo);
    }
    from = to;
  }

  printf("%d\n", res);

  return 0;
}
