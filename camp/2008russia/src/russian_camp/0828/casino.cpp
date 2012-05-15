#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "casino"

struct option_t {
  double p;
  int gain;
};

int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);

  option_t options[m];
  REP(j, m) {
    option_t& opt = options[j];
    int p, w;
    scanf("%d%d", &p, &w);
    opt.p = (double)p / s;
    opt.gain = w;
  }

  double* p = new double[n+1];
  double* q = new double[n+1];
  REP(i, n+1)
    p[i] = 1;
  p[0] = 0;
  q[0] = 0;

  REP(t, 2000) {
    for(int i = 1; i <= n; i++) {
      q[i] = 0;
      REP(j, m) {
	option_t& opt = options[j];
	//                                                                  v CAREFUL!
	q[i] >?= opt.p * (i+opt.gain > n ? 1 : p[i+opt.gain]) + (1-opt.p) * q[i-1];
      }
    }
    swap(p, q);
  }

  printf("%.20f\n", p[n]);

  return 0;
}

