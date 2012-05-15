#include <iostream>
#include <cstdio>
#include <complex>
#include <cstring>
#include <iomanip>
#include <sstream>

using namespace std;

#define for if(0);else for
#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "monkey"

typedef long double decimal;
const decimal INF = 1e100;
const decimal BIG = 1e30;

int n, m;
char str[32000];
int seq[32000];
int kmp[32000];
int am[32000][26];
decimal x[32000];

bool go(decimal x0) {
  x[0] = x0;
  //cerr << setprecision(30) << x0 << " -> ";
  for(int i = 0; i < n; i++) {
    decimal t = m*(x[i]-1.0);
    REP(c, m)
      if (c != seq[i])
	t -= x[am[i][c]];
    x[i+1] = t;
    if (t > INF)
      return true;
    if (t < 0) {
      //cerr << "no" << endl;
      return false;
    }
  }
  //cerr << x[n] << endl;
  return true;
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  cin >> m;
  cin >> str;
  n = strlen(str);

  REP(i, n)
    seq[i] = (int)(str[i] - 'a');

  {
    int q = kmp[0] = -1;
    for(int p = 1; p <= n; p++) {
      while(q >= 0 && seq[q] != seq[p-1])
	q = kmp[q];
      kmp[p] = ++q;
    }
  }
  {
    REP(c, m)
      am[0][c] = 0;
    am[0][seq[0]] = 1;
    for(int p = 1; p < n; p++) {
      REP(c, m) {
	if (seq[p] == c)
	  am[p][c] = p+1;
	else
	  am[p][c] = am[kmp[p]][c];
      }
    }
  }

  decimal lo = 0, hi = BIG;
  //while(abs(round(lo)-round(hi)) > 0.1) {
  while(hi-lo > 1e-7) {
    decimal mid = (lo+hi)/2;
    if (go(mid))
      hi = mid;
    else
      lo = mid;
  }

  printf("%.10f\n", (double)lo);
  /*
  {
    ostringstream os;
    os << setprecision(100) << round(lo);
    string s = os.str();
    string::size_type pos = s.find('.');
    if (pos != string::npos) {
      s = s.substr(0, pos);
    }
    cout << s << endl;
  }
  */

  return 0;
}

