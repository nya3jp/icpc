#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "game"

struct len_greater {
  bool operator()(const string& a, const string& b) const {
    if (a.size() != b.size())
      return (a.size() > b.size());
    return a < b;
  }
};

map<string, bool, len_greater> memo;


int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n;
  cin >> n;

  vector<string> starts(n);
  REP(i, n) {
    string s;
    cin >> s;
    starts[i] = s;
    int m = s.size();
    REP(i, m) for(int len = 1; i+len <= m; len++) {
      string t = s.substr(i, len);
      memo[t] = false;
    }
  }
  REP(i, n)
    memo[starts[i]] = true;

  string res;
  for(map<string, bool, len_greater>::iterator it = memo.begin(); it != memo.end(); ++it) {
    if (!it->second) {
      int len = it->first.size();
      if (len == 1) {
	res += it->first;
      }
      else {
	memo[it->first.substr(0, len-1)] = true;
	memo[it->first.substr(1, len-1)] = true;
      }
    }
  }

  if (res.empty()) {
    cout << "Second" << endl;
  }
  else {
    cout << "First" << endl << res << endl;
  }

  return 0;
}

