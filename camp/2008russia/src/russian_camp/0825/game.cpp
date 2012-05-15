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

#define PROBLEM_NAME "game"

typedef complex<int> P;

namespace std {
  inline bool operator<(const P& a, const P& b) {
    if (a.real() != b.real())
      return (a.real() < b.real());
    return (a.imag() < b.imag());
  }
}

inline bool by_x(const P& a, const P& b) {
  if (a.real() != b.real())
    return (a.real() < b.real());
  return (a.imag() < b.imag());
}
inline bool by_y(const P& a, const P& b) {
  if (a.imag() != b.imag())
    return (a.imag() < b.imag());
  return (a.real() < b.real());
}

inline P readPoint() {
  int x, y;
  scanf("%d%d", &x, &y);
  return P(x, y);
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n;
  scanf("%d", &n);

  P ps[n];
  REP(i, n)
    ps[i] = readPoint();

  map<P, int> ids;
  REP(i, n)
    ids[ps[i]] = i;

  int adj[4][n];
  REP(i, 4) REP(j, n)
    adj[i][j] = -1;

  sort(ps, ps+n, by_x);
  REP(i, n-1) {
    if ((ps[i]-ps[i+1]).real() == 0) {
      adj[0][ids[ps[i]]] = ids[ps[i+1]];
      adj[1][ids[ps[i+1]]] = ids[ps[i]];
    }
  }
  sort(ps, ps+n, by_y);
  REP(i, n-1) {
    if ((ps[i]-ps[i+1]).imag() == 0) {
      adj[2][ids[ps[i]]] = ids[ps[i+1]];
      adj[3][ids[ps[i+1]]] = ids[ps[i]];
    }
  }

  for(map<P, int>::iterator it = ids.begin(); it != ids.end(); ++it)
    ps[it->second] = it->first;

  long long int res = 0;
  bool visited[n];
  REP(i, n)
    visited[i] = false;

  REP(s, n) {
    if (!visited[s]) {
      visited[s] = true;
      set<int> xs, ys;
      xs.insert(ps[s].real());
      ys.insert(ps[s].imag());
      queue<int> q;
      q.push(s);
      while(!q.empty()) {
	int cur = q.front();
	q.pop();
	REP(dir, 4) {
	  int next = adj[dir][cur];
	  if (next >= 0 && !visited[next]) {
	    visited[next] = true;
	    q.push(next);
	    xs.insert(ps[next].real());
	    ys.insert(ps[next].imag());
	  }
	}
      }
      res += (long long)xs.size() * ys.size();
    }
  }

  cout << res << endl;

  return 0;
}
