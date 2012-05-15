#include <iostream>
#include <cstdio>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "mk"

int n, m;
bool g[300][1500];
bool possible[300][1500];
int toright[300], toleft[1500];
int visited[300];

bool augment(int left) {
  if (left < 0)
    return true;
  if (visited[left])
    return false;
  visited[left] = 1;
  REP(right, m) if (g[left][right] && augment(toleft[right])) {
    toleft[right] = left;
    return true;
  }
  return false;
}

bool match() {
  memset(toleft, -1, sizeof(toleft));
  memset(toright, -1, sizeof(toright));
  REP(left, n) {
    memset(visited, 0, sizeof(visited));
    if (!augment(left))
      return false;
  }
  REP(right, m)
    if (toleft[right] >= 0)
      toright[toleft[right]] = right;
  return true;
}

bool alternate(int left, int start) {
  if (left < 0)
    return true;
  int& res = visited[left];
  if (res < 0) {
    res = 0;
    REP(right, m) if (g[left][right] && (right == start || alternate(toleft[right], start))) {
      possible[left][right] = true;
      res = 1;
    }
  }
  return res;
}

void check() {
  REP(left, n) {
    memset(visited, -1, sizeof(visited));
    alternate(left, toright[left]);
  }
}


int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  scanf("%d%d", &n, &m);
  REP(i, n) REP(j, m) {
    char c ;
    scanf(" %c", &c);
    g[i][j] = (c == '1');
  }

  if (match())
    check();

  REP(i, n) {
    REP(j, m)
      printf("%d", (possible[i][j] ? 0 : 1));
    puts("");
  }

  return 0;
}

