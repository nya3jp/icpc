#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "studies"

#define MOD 1000000007

#define N 310

int n;
long long g[N][N];
long long v[N];
bool res[N];
int colors[N];
int comp[N];
int nColors = 0;
int order[N];

const long long INF = 1234567890;

void dfs(int a, int c, int*& p) {
  if (colors[a] == 0) {
    colors[a] = c;
    REP(b, n) if (g[a][b] < INF) {
      dfs(b, c, p);
    }
    *p++ = a;
  }
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int m;
  scanf("%d%d", &n, &m);

  REP(i, n) REP(j, n)
    g[i][j] = (i == j ? 0 : INF);

  REP(i, m) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    a--; b--;
    g[a][b] = -c;
  }

  {
    int* p = order;
    REP(i, n)
      dfs(i, 1, p);
    reverse(order, order+n);
    memset(colors, 0, sizeof(colors));
    REP(i, n) REP(j, i)
      swap(g[i][j], g[j][i]);
    REP(i, n) if (colors[order[i]] == 0) {
      p = comp;
      dfs(order[i], ++nColors, p);
    }
    REP(i, n) REP(j, i)
      swap(g[i][j], g[j][i]);
  }

  /*
  REP(i, n)
    fprintf(stderr, "%d ", colors[i]);
  fprintf(stderr, "\n");
  */

  REP(t, n) {
    /*
    REP(i, n)
      fprintf(stderr, "%d ", v[i]);
    fprintf(stderr, "\n");
    */
    REP(i, n) REP(j, n)
      if (g[i][j] < INF && colors[i] == colors[j])
	v[j] <?= v[i] + g[i][j];
  }
  REP(t, n) {
    REP(i, n) REP(j, n) {
      if (g[i][j] < INF && colors[i] == colors[j] && v[j] > v[i]+g[i][j]) {
	res[colors[i]] = true;
	v[j] = v[i]+g[i][j];
      }
    }
  }

  int k = 0;
  REP(i, n)
    if (res[colors[i]])
      k++;

  printf("%d\n", k);
  bool first = true;
  REP(i, n) {
    if (res[colors[i]]) {
      if (!first)
	printf(" ");
      printf("%d", i+1);
      first = false;
    }
  }
  puts("");

  return 0;
}
