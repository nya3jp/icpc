#include <iostream>
#include <cstdio>

using namespace std;

#define NAME "country"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main() {

  if (!freopen(NAME ".in", "r", stdin))
    abort();
  if (!freopen(NAME ".out", "w", stdout))
    abort();

  int n, m;
  scanf("%d%d", &n, &m);

  int degs[n];
  int edges[m][2];
  memset(degs, 0, sizeof(int)*n);

  REP(i, m) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    edges[i][0] = a;
    edges[i][1] = b;
    degs[a]++;
    degs[b]++;
  }

  int junction = max_element(degs, degs+n)-degs;

  bool alive[m];
  REP(i, m)
    alive[i] = true;

  int junction_edges[n], outer_edges[n], neighbor[n];
  junction_edges[junction] = outer_edges[junction] = neighbor[junction] = -123;

  REP(i, m) {
    int a = edges[i][0], b = edges[i][1];
    if (a != junction)
      swap(a, b);
    if (a == junction) {
      // junction edge
      junction_edges[b] = i;
    }
    else {
      // outer edge
      outer_edges[a] = i;
      outer_edges[b] = i;
      neighbor[a] = b;
      neighbor[b] = a;
    }
  }

  for(;;) {
    char cmd[64];
    if (scanf("%s", cmd) != 1)
      break;
    if (strcmp(cmd, "LENGTH") == 0) {
      int a, b;
      scanf("%d%d", &a, &b);
      a--; b--;
      if (a == b) {
	printf("0\n");
      }
      else if (neighbor[a] == b && alive[outer_edges[a]]) {
	printf("1\n");
      }
      else {
	if (a != junction)
	  swap(a, b);
	int da = (a == junction ? 0 :
		  (alive[junction_edges[a]] ? 1 :
		   (alive[outer_edges[a]] && alive[junction_edges[neighbor[a]]] ? 2 : -123)));
	int db = (alive[junction_edges[b]] ? 1 :
		  (alive[outer_edges[b]] && alive[junction_edges[neighbor[b]]] ? 2 : -123));
	int d = da + db;
	if (d < 0)
	  printf("-1\n");
	else
	  printf("%d\n", d);
      }
    }
    else if (strcmp(cmd, "DELETE") == 0) {
      int i;
      scanf("%d", &i);
      i--;
      alive[i] = false;
    }
    else {
      abort();
    }
  }

  return 0;
}
