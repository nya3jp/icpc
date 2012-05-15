#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "tea"

#define C 5
#define N 1010
#define MUL 10000

int tea[2][N];
int mm[2];
unsigned long long memo[5][N][N];
int trace[5][N][N];

const unsigned long long INF = (unsigned long long)(long long)-1;

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  scanf("%d%d", &n, &m);

  REP(i, m) {
    int c, t;
    scanf("%d%d", &c, &t);
    tea[t][mm[t]++] = c * MUL + i+1;
  }
  REP(t, 2)
    sort(tea[t], tea[t]+mm[t]);

  //cerr << "piyo" << endl;

  memset(memo, -1, sizeof(memo));

  //cerr << "piyo" << endl;

  const int TRANS[5][2] = {
    {1, 2},
    {3, 2},
    {1, 4},
    {-1, 2},
    {1, -1},
  };
  memo[0][0][0] = 0;
  REP(k, n) {
    REP(a, k+1) {
      int b = k-a;
      REP(c, 5) {
	unsigned long long co = memo[c][a][b];
	if (co == INF)
	  continue;
	REP(t, 2) {
	  int cc = TRANS[c][t];
	  if (cc < 0)
	    continue;
	  if ((t?b:a) >= mm[t])
	    continue;
	  unsigned long long lo = (unsigned long long)(n-k)*(tea[t][t?b:a]/MUL);
	  //int id = tea[t][t?b:a]%MUL;
	  unsigned long long& d = memo[cc][a+(t^1)][b+t];
	  /*
	  fprintf(stderr,
		  "(c=%d, a=%d, b=%d)=%I64d -> cost=%dx%d=%I64d -> (c=%d, a=%d, b=%d)<?=%I64d\n",
		  c, a, b, co, n-k, (tea[t][t?b:a]/MUL), lo, cc, a+(t^1), b+t, co+lo);
	  */
	  if (co+lo < d) {
	    d = co+lo;
	    int& tr = trace[cc][a+(t^1)][b+t];
	    tr = (c<<1)|t;
	  }
	}
      }
    }
  }

  int best_c = -1, best_a = -1, best_b = -1;
  REP(c, 5) REP(a, n+1) {
    int b = n-a;
    if (memo[c][a][b] < INF) {
      if (best_c < 0 || memo[c][a][b] < memo[best_c][best_a][best_b]) {
	best_c = c;
	best_a = a;
	best_b = b;
      }
    }
  }

  if (best_c < 0) {
    cout << "Impossible" << endl;
  }
  else {
    //cout << memo[best_c][best_a][best_b] << endl;

    int c = best_c, a = best_a, b = best_b;
    //cerr << c << " " << a << " " << b << endl;
    vector<int> route;
    while(a+b > 0) {
      //route.push_back(trace[c][a][b][3]);
      int tr = trace[c][a][b];
      int cc = tr >> 1;
      int t = tr & 1;
      //cerr << tr << endl;
      route.push_back(tea[t][(t?b:a)-1]%MUL);
      if (t)
	b--;
      else
	a--;
      c = cc;
    }
    reverse(ALLOF(route));
    REP(i, route.size()) {
      if (i > 0)
	cout << " ";
      cout << route[i];
    }
    cout << endl;

  }

  return 0;
}
