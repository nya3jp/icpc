#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "amplifiers"

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n;
  cin >> n;

  if (n%2 == 0) {
    cout << "No solution" << endl;
  }
  else {
    vector<int> res;
    while(n > 1) {
      int p = n & 3;
      if (p == 1) {
	res.push_back(1);
      }
      else {
	res.push_back(2);
      }
      n = (n >> 1) | 1;
    }
    reverse(ALLOF(res));
    cout << res.size() << endl;
    REP(i, res.size()) {
      if (i > 0)
	cout << " ";
      cout << res[i];
    }
    cout << endl;
  }

  return 0;
}
