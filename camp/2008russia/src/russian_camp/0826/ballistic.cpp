#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()


#define DIGIT 100
#define ONE_LENGTH 9
#define MAX_LENGTH (DIGIT/ONE_LENGTH+2)
#define ONE_MAX 1000000000
#define BUFSIZE 256

inline int signum(int n) {
  return (n == 0 ? 0 : n < 0 ? -1 : 1);
}

class lint_t {
  int body[MAX_LENGTH];
  int sgn;

  inline int& operator[](const int index) { return body[index]; }
  inline const int& operator[](const int index) const { return body[index]; }
  inline int last() const {
    int i;
    for(i = MAX_LENGTH-1; i >= 0; i--)
      if (body[i])
	break;
    return i+1;
  }
public:
  lint_t(int n = 0) {
    fill(body, body+MAX_LENGTH, 0);
    body[0] = n;
    sgn = signum(n);
  }
  lint_t(const lint_t& a) {
    copy(a.body, a.body+MAX_LENGTH, body);
    sgn = a.sgn;
  }
  void operator=(const lint_t& a) {
    copy(a.body, a.body+MAX_LENGTH, body);
    sgn = a.sgn;
  }
  int compare(const lint_t& a) const {
    if (sgn != a.sgn)
      return signum(sgn-a.sgn);
    for(int i = MAX_LENGTH-1; i >= 0; i--)
      if (body[i] > a[i])
	return sgn*1;
      else if (body[i] < a[i])
	return sgn*-1;
    return 0;
  }
  friend bool operator==(const lint_t& a, const lint_t& b) { return !a.compare(b); }
  friend bool operator!=(const lint_t& a, const lint_t& b) { return a.compare(b); }
  friend bool operator<(const lint_t& a, const lint_t& b) { return a.compare(b) < 0; }
  friend bool operator<=(const lint_t& a, const lint_t& b) { return a.compare(b) <= 0; }
  friend bool operator>(const lint_t& a, const lint_t& b) { return a.compare(b) > 0; }
  friend bool operator>=(const lint_t& a, const lint_t& b) { return a.compare(b) >= 0; }

  string toString() const {
    string str;
    char buf[BUFSIZE];
    int i = last()-1;
    if (i == -1)
      return string("0");
    if (sgn < 0)
      str += "-";
    sprintf(buf, "%d", body[i]);
    str += buf;
    while(--i >= 0) {
      sprintf(buf, "%0*d", ONE_LENGTH, body[i]);
      str += buf;
    }
    return str;
  }

  friend lint_t operator*(lint_t a, int b) {
    long long carry = 0;
    for(int i = 0; i < MAX_LENGTH; i++) {
      long long tmp = a[i]*b + carry;
      a[i] = tmp%ONE_MAX;
      carry = tmp/ONE_MAX;
    }
    if (b < 0)
      a.sgn *= -1;
    if (b == 0)
      a.sgn = 0;
    return a;
  }

  friend lint_t operator+(lint_t a, const lint_t& b) {
    if (b.sgn < 0)
      return a-b.negate();
    if (a.sgn < 0)
      return b-a.negate();
    int carry = 0;
    for(int i = 0; i < MAX_LENGTH; i++) {
      int tmp = a[i] + b[i] + carry;
      a[i] = tmp % ONE_MAX;
      carry = tmp / ONE_MAX;
    }
    a.sgn = (a.last() == 0 ? 0 : 1);
    return a;
  }
  friend lint_t operator-(lint_t a, const lint_t& b) {
    if (b.sgn < 0)
      return a+b.negate();
    if (a.sgn < 0)
      return (a.negate()+b).negate();
    if (a.compare(b) < 0)
      return (b-a).negate();
    int carry = 0;
    for(int i = 0; i < MAX_LENGTH; i++) {
      int tmp = a[i] - b[i] - carry;
      carry = (tmp < 0 ? 1 : 0);
      if (carry > 0)
	tmp += ONE_MAX;
      a[i] = tmp;
    }
    a.sgn = (a.last() == 0 ? 0 : 1);
    return a;
  }
  lint_t negate() const {
    lint_t o(*this);
    o.sgn *= -1;
    return o;
  }

};

int mat[20][20];
lint_t* memo[20][1<<20];
int n;
lint_t poly_one[21];


lint_t* solve(int j, int p) {
  if (j == n)
    return poly_one;
  if (memo[j][p])
    return memo[j][p];

  int m = n-j;
  int sgn = 1;

  lint_t* res = new lint_t[m+1];

  for(int i = 0; i < n; i++) {
    if (p & (1<<i))
	continue;

    lint_t* suborg = solve(j+1, p|(1<<i));
    lint_t sub[m];
    for(int k = 0; k < m; k++) {
      sub[k] = suborg[k];
      if (sgn < 0)
	sub[k] = sub[k].negate();
    }
    if (i == j) {
      for(int k = 0; k < m; k++)
	res[k+1] = res[k+1] - sub[k];
    }
    for(int k = 0; k < m; k++)
      res[k] = res[k] + sub[k] * mat[i][j];
    sgn *= -1;
  }

  memo[j][p] = res;
  return res;
}

void print(const lint_t& a) {
  cout << a.toString() << endl;
}

int main() {

  if (!freopen("ballistic.in", "r", stdin))
    abort();
  if (!freopen("ballistic.out", "w", stdout))
    abort();

  poly_one[0] = lint_t(1);

  cin >> n;

  REP(i, n) REP(j, n)
    cin >> mat[i][j];

  lint_t* res = solve(0, 0);
  for(int k = n; k >= 0; k--)
    print(res[k]);

  return 0;
}

