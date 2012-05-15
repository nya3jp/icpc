#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

#define REP(i,n) for(int i = 0 ; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

typedef long long int integer;

integer gcd(integer a, integer b) {
    while(b != 0) {
        integer r = a%b;
        a = b;
        b = r;
    }
    return a;
}

inline integer myabs(integer x) {
    return (x < 0 ? -x : x);
}

struct Frac {
    integer num, denom;
};
void reduce(Frac& a) {
    integer g = gcd(myabs(a.num), myabs(a.denom));
    a.num /= g;
    a.denom /= g;
}
void minusss(const Frac& a, const Frac& b, Frac& c) {
    c.num = a.num*b.denom - b.num*a.denom;
    c.denom = a.denom*b.denom;
    reduce(c);
}
bool operator<(const Frac& a, const Frac& b) {
    Frac c;
    minusss(a, b, c);
    return (c.num < 0);
}

namespace hoge {
integer N, D;
integer diffN, diffD;
integer bestN, bestD;

void test(integer n, integer d) {
    if (!IN(n, 1, 32768) || !IN(d, 1, 32768))
        return;
    integer dN = myabs(N*d - D*n);
    integer dD = D*d;
    if (dN*diffD - dD*diffN < 0 && dN != 0) {
        integer g = gcd(myabs(n), myabs(d));
        bestN = n / g;
        bestD = d / g;
        diffN = dN;
        diffD = dD;
    }
}

void main(integer NN, integer DD) {
    N = NN;
    D = DD;

    diffN = 65536;
    diffD = 1;

    for(integer d = 1; d < 32768; d++) {

        // N/D - n/d = (Nd - Dn)/Dd

        integer n = N*d/D;

        test(n, d);
        test(n+1, d);
        test(n-1, d);

    }

    cout << bestN << ' ' << bestD << endl;
}
}

int main() {

    Frac original;
    cin >> original.num >> original.denom;

    Frac best = {65536, 1};
    Frac ans = {0, 1};

    for(integer denom = 1; denom <= 32767; denom++) {
        // N/D - n/d = Nd - Dn
        int num = original.num * denom / original.denom;
        Frac f1 = {num, denom}, f2 = {num+1, denom}, f3 = {num-1, denom};
        reduce(f1);
        reduce(f2);
        reduce(f3);

        /*
        {
            Frac f = f3;
            Frac d;
            minusss(f, original, d);
            d.num = myabs(d.num);
            if (d < best && d.num != 0 && IN(f.num, 1, 32768)) {
                best = d;
                ans = f;
            }
        }
        {
            Frac f = f1;
            Frac d;
            minusss(f, original, d);
            d.num = myabs(d.num);
            if (d < best && d.num != 0 && IN(f.num, 1, 32768)) {
                best = d;
                ans = f;
            }
        }
        {
            Frac f = f2;
            Frac d;
            minusss(f, original, d);
            d.num = myabs(d.num);
            if (d < best && d.num != 0 && IN(f.num, 1, 32768)) {
                best = d;
                ans = f;
            }
        }
        */
    }

    //cout << ans.num << ' ' << ans.denom << endl;
    hoge::main(original.num, original.denom);

    return 0;
}

// Powered by Fate Testarossa
