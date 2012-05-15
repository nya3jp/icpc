#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "merge"

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  cin >> n >> m;

  for(int i = 0; i < n+m; i++) {
    for(int j = 0; j <= i; j++) {
      if (j > 0)
	printf("|");
      if (j < n && i-j < m)
	printf("(x%d&y%d)", j+1, i-j+1);
      else if (j < n)
	printf("x%d", j+1);
      else if (i-j < m)
	printf("y%d", i-j+1);
      else
	abort();
    }
    printf("\n");
  }

  return 0;
}

