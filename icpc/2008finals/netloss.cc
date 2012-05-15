#include <iostream>
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

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

struct Poly {
    int n;
    double coef[12];
};

double integrate(Poly p, double a, double b) {
    double res = 0;
    double ap = 1, bp = 1;
    REP(i, p.n+1) {
        ap *= a;
        bp *= b;
        res += p.coef[i] / (i+1) * (bp - ap);
    }
    return res;
}
Poly multx(Poly p) {
    for(int i = p.n; i >= 0; i--)
        p.coef[i+1] = p.coef[i];
    p.coef[0] = 0;
    p.n++;
    return p;
}

//Sxp(x) - a/3(1-c^3) - b/2(1-c^2) = 0
//Sp(x) - a/2(1-c^2) - b(1-c) = 0

pair<double,double> solve(Poly p, double c) {
    double a1 = (1-c*c*c)/3;
    double b1 = (1-c*c)/2;
    double c1 = integrate(multx(p), c, 1);
    double a2 = (1-c*c)/2;
    double b2 = (1-c);
    double c2 = integrate(p, c, 1);
    b1 /= a1;
    c1 /= a1;
    a1 = 1;
    b2 -= b1 * a2;
    c2 -= c1 * a2;
    a2 = 0;
    c2 /= b2;
    b2 = 1;
    c1 -= c2 * b1;
    b1 = 0;
    return make_pair(c1, c2);
}

int main() {

    FILE* fp = freopen("netloss.in", "r", stdin);
    assert(fp);
    
    int iCase = 0;
    for(;;) {
        Poly p;
        cin >> p.n;
        if (p.n == 0)
            break;
        REP(i, p.n+1)
            cin >> p.coef[p.n-i];
        double c;
        cin >> c;
        pair<double, double> res_right = solve(p, c);
        REP(i, p.n+1)
            p.coef[i] *= (i % 2 == 0 ? 1 : -1);
        c *= -1;
        pair<double, double> res_left = solve(p, c);
        res_left.first *= -1;
        printf("Case %d: %.3f %.3f %.3f %.3f\n",
               ++iCase,
               res_left.first, res_left.second,
               res_right.first, res_right.second);
    }

    return 0;
}
