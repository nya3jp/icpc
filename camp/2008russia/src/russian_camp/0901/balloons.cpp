#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int rig[1000000+10];
int stock[200000+10];
int children[200000+10];

#define PROBLEM_NAME "balloons"

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  scanf("%d%d", &n, &m);

  REP(i, n)
    scanf("%d", &stock[i]);
  REP(j, m)
    scanf("%d", &children[j]);

  sort(stock, stock+n, greater<int>());
  sort(children, children+m, greater<int>());

  int maxi = stock[0];

  REP(i, n)
    rig[stock[i]-1] = i+1;

  for(int i = maxi; i > 0; i--)
    rig[i-1] >?= rig[i];

  /*
  REP(i, maxi+1) {
    printf("right[%d] = %d\n", i, rig[i]);
  }
  */

  int s = 0, p = 0;
  REP(c, m) {
    int w = children[c];
    int lim = min(rig[s], rig[s]-p+rig[s+1]);
    //fprintf(stderr, "(s,p)=(%d,%d), w/lim=%d/%d\n", s, p, w, lim);
    if (w > lim) {
      puts("NO");
      return 0;
    }
    p += w;
    if(p >= rig[s]) {
      p -= rig[s];
      s++;
    }
  }
  puts("YES");

  return 0;
}
