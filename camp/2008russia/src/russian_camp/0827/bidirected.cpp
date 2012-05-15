#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define NAME "bidirected"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

struct Edge {
  int dest;
  int color;
};

int main() {

  if (!freopen(NAME ".in", "r", stdin))
    abort();
  if (!freopen(NAME ".out", "w", stdout))
    abort();

  int n, m;
  scanf("%d%d", &n, &m);

  vector<Edge> g[n];

  REP(k, m) {
    int a, b, p, q;
    scanf("%d%d%d%d", &a, &b, &p, &q);
    a--; b--;
    int rev = (p == q ? 1 : 0);
    g[a].push_back((Edge){b, rev});
    g[b].push_back((Edge){a, rev});
  }

  int colors[n];
  memset(colors, -1, sizeof(int)*n);

  vector<int> res;
  REP(s, n) {
    if (colors[s] < 0) {
      vector<int> comps[2];
      colors[s] = 0;
      queue<Edge> q;
      q.push((Edge){s, 0});
      comps[0].push_back(s);
      while(!q.empty()) {
	Edge cur = q.front();
	q.pop();
	assert(colors[cur.dest] == cur.color);
	vector<Edge>& adj = g[cur.dest];
	REP(i, adj.size()) {
	  Edge& e = adj[i];
	  int nextcolor = cur.color ^ e.color;
	  if (colors[e.dest] < 0) {
	    colors[e.dest] = nextcolor;
	    q.push((Edge){e.dest, nextcolor});
	    comps[nextcolor].push_back(e.dest);
	  }
	  else if (colors[e.dest] != nextcolor) {
	    goto FAILED;
	  }
	}
      }
      if (comps[0].size() < comps[1].size())
	copy(ALLOF(comps[0]), back_inserter(res));
      else
	copy(ALLOF(comps[1]), back_inserter(res));
    }
  }

  puts("YES");
  printf("%d\n", res.size());
  REP(i, res.size())
    printf("%d%c", res[i]+1, (i+1 == res.size() ? '\n' : ' '));
  return 0;

 FAILED:
  puts("NO");

  return 0;
}
