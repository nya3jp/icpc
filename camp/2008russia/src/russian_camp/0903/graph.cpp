#include <cstdio>
#include <iostream>
#include <climits>
#include <algorithm>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

#define PROBLEM_NAME "graph"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()



int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int d, r;
  cin >> d >> r;

  cout << "YES" << endl;
  if (d == 1) {
    printf("2 1\n1 2\n");
  }
  else if (d == 2 && r == 1) {
    printf("3 2\n1 2\n2 3\n");
  }
  else {
    printf("%d %d\n", 2*d, 2*d);
    for(int i = 1; i <= d; i++)
      printf("%d %d\n", i, i+1);
    for(int i = d+2; i < 2*d; i++)
      printf("%d %d\n", i, i+1);
    printf("%d %d\n", (d-r+1), d+2);
    printf("%d %d\n", d+2-(d-r+1), 2*d);
  }

  return 0;
}

