#include <cstdio>
#include <iostream>
#include <climits>
#include <algorithm>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

#define PROBLEM_NAME "xor"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 200

int n, s, t;
int cap[N][N];
int flow[N][N];
int levels[N];
bool finished[N];
#define residue(i,j) (cap[i][j]-flow[i][j])

void levelize() {
  memset(levels, -1, sizeof(levels));
  queue<int> q;
  levels[s] = 0; q.push(s);
  while(!q.empty()) {
    int here = q.front(); q.pop();
    REP(there, n) if (levels[there] < 0 && residue(here, there) > 0) {
      levels[there] = levels[here] + 1;
      q.push(there);
    }
  }
}
int augment(int here, int cur) {
  if (here == t || cur == 0)
    return cur;
  if (finished[here])
    return 0;
  finished[here] = true;
  REP(there, n) if (levels[there] > levels[here]) {
    int f = augment(there, min(cur, residue(here, there)));
    if (f > 0) {
      flow[here][there] += f;
      flow[there][here] -= f;
      finished[here] = false;
      return f;
    }
  }
  return 0;
}
int max_flow() {
  memset(flow, 0, sizeof(flow));
  int total = 0;
  for(bool cont = true; cont; ) {
    cont = false;
    levelize();
    memset(finished, 0, sizeof(finished));
    for(int f; (f = augment(s, INT_MAX)) > 0; cont = true)
      total += f;
  }
  return total;
}


int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int m;
  cin >> m;

  vector<long long> v(m);
  REP(i, m)
    cin >> v[i];

  int sum = 0;
  int width = 0;
  REP(i, m) {
    long long a = v[i];
    sum += __builtin_popcountll(a);
    while(a) {
      int l = __builtin_ctzll(a);
      a &= ~(1ll<<l);
      width >?= l+1;
    }
  }

  n = m + width + 2;
  s = n-2;
  t = n-1;

  REP(i, m) REP(j, width) {
    cap[i][m+j] = 1;
  }
  REP(i, m) {
    cap[s][i] = __builtin_popcountll(v[i]);
  }

  int sumsum = sum;
  REP(j, width) {
    int lo = (sumsum/2) / (width-j) * 2;
    cap[m+j][t] = lo;
    //fprintf(stderr, "> %d, %d\n", lo, width);
    sumsum -= lo;
  }

  if (sumsum > 0 || max_flow() != sum) {
    //fprintf(stderr, "sum=%d, sumsum=%d, max_flow=%d\n", sum, sumsum, max_flow());
    puts("impossible");
  }
  else {
    vector<long long> res(m, 0);
    REP(i, m) REP(j, width) {
      int f = flow[i][m+j];
      if (f > 0)
	res[i] |= 1ll << j;
    }
    REP(i, m) {
      if (i > 0)
	cout << " ";
      cout << res[i];
    }
    cout << endl;
  }

  return 0;
}

