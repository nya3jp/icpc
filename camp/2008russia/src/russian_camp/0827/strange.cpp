#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

#define NAME "strange"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define MOD (1000000000+7)
#define MEMOSIZE 1000000
char bits[3][100000+10];
int n;
int invmemo[MEMOSIZE];

typedef long long integer;

integer gcd(integer a, integer b) {
  return (b == 0 ? a : gcd(b, a%b));
}

void xgcd(integer a, integer b, integer& x, integer& y) {
  if (b == 0) {
    x = 1;
    y = 0;
  }
  else {
    xgcd(b, a%b, y, x);
    y -= a/b*x;
  }
}

integer divide(integer a, integer b, integer m) {
  integer g = gcd(a, m);
  integer x, y;
  xgcd(a, m, x, y);
  integer n = x*b/g;
  integer dn = m/g;
  n -= n/dn*dn;
  if (n < 0)
    n += dn;
  return n;
}

inline int add(int a, int b) {
  return (a+b)%MOD;
}
inline int mul(int a, int b) {
  return (int)(((long long)a*b)%MOD);
}
inline int inv(int a) {
  assert(a < MEMOSIZE);
  if (invmemo[a] == 0) {
    invmemo[a] = divide(a, 1, MOD);
  }
  return invmemo[a];
}
inline int divi(int a, int b) {
  return mul(a, inv(b));
}

map<int, int*> choosememo;

int choose(int n, int m) {
  if (n == 0)
    return (m == 0 ? 1 : 0);
  if (m == 0)
    return 1;
  if (choosememo.count(n) == 0) {
    int* p = new int[1000000];
    memset(p, 0, sizeof(int)*1000000);
    choosememo[n] = p;
  }
  int* p = choosememo[n];
  if (p[m] == 0) {
    p[m] = divi(mul(choose(n, m-1), n-m+1), m);
  }
  return p[m];
}

int go(int* cnt) {
  sort(cnt, cnt+3);
  int a = cnt[0], b = cnt[1], c = cnt[2];
  int res = 0;
  int ca = 1, cb = 1, cc = 1;
  for(int i = 0; i <= a; i++) {
    res = add(res, mul(choose(a, i), mul(choose(b, (b-a)/2+i), choose(c, (c-a)/2+i))));
  }
  REP(i, n-(a+b+c))
    res = mul(res, 2);
  return res;
}

  /*
  //printf("z%d,%d,%d\n", a, b, c);
  for(int i = 0; i < (b-a)/2; i++)
    cb = divi(mul(cb, b-i), (b-a)/2-i);
  for(int i = 0; i < (c-a)/2; i++)
    cc = divi(mul(cc, c-i), (c-a)/2-i);
  if (b == 0 && (b-a)/2 == 0)
    cb = 1;
  if (c == 0 && (c-a)/2 == 0)
    cc = 1;
  for(int i = 0; i <= a/2; i++) {
    res = add(res, mul(ca, mul(cb, cc)));
    //printf("%d,%d,%d\n", ca, cb, cc);
    if (i == a/2)
      break;
    ca = divi(mul(ca, a-i), i+1);
    cb = divi(mul(cb, b-(b-a)/2-i), (b-a)/2+i+1);
    cc = divi(mul(cc, c-(c-a)/2-i), (c-a)/2+i+1);
//     ca = divi(mul(ca, a-i-1), i+1);
//     cb = divi(mul(cb, b-(b-a)/2-i-1), (b-a)/2+i+1);
//     cc = divi(mul(cc, c-(c-a)/2-i-1), (c-a)/2+i+1);
  }
  */
int main() {

  if (!freopen(NAME ".in", "r", stdin))
    abort();
  if (!freopen(NAME ".out", "w", stdout))
    abort();

  REP(i, 3)
    scanf("%s", bits[i]);

  n = strlen(bits[0]);

  int cnt[3] = {0};
  REP(i, n) {
    REP(j, 3) {
      if (bits[j][i] != bits[(j+1)%3][i] &&
	  bits[j][i] != bits[(j+2)%3][i])
	cnt[j]++;
    }
  }

  if (cnt[0]%2 != cnt[1]%2 ||
      cnt[1]%2 != cnt[2]%2 ||
      cnt[2]%2 != cnt[0]%2)
    puts("0");
  else
    printf("%d\n", go(cnt));

  return 0;
}
