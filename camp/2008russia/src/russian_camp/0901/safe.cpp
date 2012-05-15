#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


#define PROBLEM_NAME "safe"

int n, m;
char str[1000000+100];
int v[1000000+100];
int kmp[1000000+100];
int table[1000000+100];

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  scanf("%d%d%s", &m, &n, str);
  REP(i, m)
    scanf("%d", &v[i]);

  {
    int q = kmp[0] = -1;
    for(int p = 1; p <= n; p++) {
      while(q >= 0 && str[q] != str[p-1])
	q = kmp[q];
      kmp[p] = ++q;
    }
  }

  int period = n - kmp[n];
  if (n % period != 0)
    period = n;

  REP(i, m)
    table[v[i]%period]++;

  /*
  REP(i, period) {
    fprintf(stderr, "%d ", v[i]);
  }
  fprintf(stderr, "\n");
  */

  long long res = numeric_limits<long long>::max();
  int half = (period-1)/2;
  long long left = 0, right = 0;
  REP(i, half) {
    left += table[period-1-i];
    right += table[i+1];
  }
  long long lo = 0;
  REP(i, period)
    lo += (long long)min(i, period-i) * table[i];
  REP(i, period*3) {
    /*
    if (i == 0)
      fprintf(stderr, "\n");
    fprintf(stderr, "%I64d(%I64d,%I64d) ", lo, left, right);
    */
    res <?= lo;
    if (period % 2 == 0)
      lo -= (long long)(half+1) * table[(i+half+1)%period];
    lo -= right;
    lo += (long long)half*table[(i+half+1+period)%period];
    left -= table[(i-half+period)%period];
    left += table[(i+period)%period];
    right += table[(i+half+1+period)%period];
    right -= table[(i+1+period)%period];
    lo -= (long long)half*table[(i-half+period)%period];
    lo += left;
    /*
    lo -= (long long)half * table[(i-half+period) % period];
    lo += (long long)(half-1) * table[(i+half+1+period) % period];
    left += table[i];
    left -= table[(i-half+period) % period];
    right += table[(i+half+1+period) % period];
    right -= table[(i+1) % period];
    lo += left + right;
    */
    /*
    left += table[i];
    lo += left;
    lo -= right;
    right -= table[i];
    lo -= (long long)(half+1) * table[(i-half+period) % period];
    lo += (long long)half * table[(i+half+period) % period];
    */
    if (period % 2 == 0)
      lo += (long long)(half+1) * table[(i+half+2)%period];
  }

  cout << res << endl;

  return 0;
}
