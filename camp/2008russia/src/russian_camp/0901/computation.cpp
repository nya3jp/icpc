#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "computation"

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, d;
  cin >> n >> d;

  if (n == 2 && d == 1) {
    cout << "1 2" << endl;
  }
  else if (n >= 3 && d >= 2) {
    for(int i = 1; i <= d-1; i++)
      printf("%d %d\n", i, i+1);
    for(int i = d+1; i <= n; i++)
      printf("%d %d\n", d, i);
  }
  else {
    puts("NONE");
  }

  return 0;
}
