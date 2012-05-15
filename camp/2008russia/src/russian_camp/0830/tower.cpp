#include <iostream>
#include <cstdio>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "tower"


typedef long double decimal;
typedef complex<decimal> P;

const decimal PI = acos((decimal)0.0)*2;
const decimal EPS = 1.0e-14;

P readPoint() {
  decimal x, y;
  cin >> x >> y;
  return P(x, y);
}

decimal f(decimal r, decimal R) {
  const decimal sqrt2 = sqrt(2.0);
  if (abs(r-R) < EPS)
    return PI/4;
  if (abs(R-sqrt2*r) < EPS)
    return 0;
  return acos(R/(sqrt2*r));
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int nCases;
  cin >> nCases;

  REP(iCase, nCases) {

    decimal R;
    cin >> R;

    P a = readPoint();
    P b = readPoint();

    decimal ra = abs(a), rb = abs(b);
    decimal tha = f(ra, R);
    decimal thb = f(rb, R);

    //cerr << "Case " << iCase+1 << endl;
    if (!(0 <= tha && tha <= 1 && 0 <= thb && thb <= 1)) {
      //cerr << "invalid" << endl;
      puts("NO");
    }
    else {
      bool yes = false;
      for(int sa = -1; sa <= 1; sa+=2) {
	for(int sb = -1; sb <= 1; sb+=2) {
	  decimal th = (arg(a)+sa*tha)-(arg(b)+sb*thb);
	  if (abs(sin(th)) < EPS || abs(cos(th)) < EPS) {
	    yes = true;
	  }
	}
      }
      puts(yes ? "YES" : "NO");
    }

  }

  return 0;
}

