// 何が大変かって凸包ですよおにーさん

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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

typedef complex<double> P;
typedef vector<P> G;
const double PI = 2*acos(0.0);
const double EPS = 1.0e-8;

int n;
vector<P> points;

bool pair_less(const P& a, const P& b) {
    return (make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag()));
}
bool arg_less(const P& a, const P& b) {
    return (arg(a) < arg(b));
}

// 線形だめ！
vector<P> convex_hull(vector<P> v) {
    int n = v.size();
    P g(EPS, 0);
    REP(i, n)
        g += v[i] / (double)n;
    REP(i, n)
        v[i] -= g;
    sort(ALLOF(v), arg_less);
    P first = v[0];
    REP(i, n)
        if (v[i].real() < first.real())
            first = v[i];
    rotate(v.begin(), find(ALLOF(v), first), v.end());
    v.push_back(first);
    int m = 2;
    for(int i = 2; i <= n; i++) {
        P p = v[i];
        while(m >= 2 && (conj(v[m-1]-v[m-2])*(p-v[m-2])).imag() < EPS)
            m--;
        v[m++] = p;
    }
    v.resize(--m);
    REP(i, m)
        v[i] += g;
    return v;
}



double imag_min(P p, double inf, double sup) {
    return min((p*polar(1.0, inf)).imag(), (p*polar(1.0, sup)).imag());
}

double solve() {

    vector<P> v(points);
    sort(ALLOF(v), pair_less);
    v.erase(unique(ALLOF(v)), v.end());

    bool linear = true;
    for(int i = 2; i < (int)v.size(); i++)
        if (abs(arg(v[i]-v[0])-arg(v[1]-v[0])) > EPS)
            linear = false;
    if (linear)
        return 0;

    vector<P> convex = convex_hull(v);

    /*
    REP(i, convex.size()) {
        printf("convex %d: (%.0f, %.0f)\n", i, convex[i].real(), convex[i].imag());
    }
    */

    int nAngles = convex.size();
    if (nAngles == 1)
        return 0;

    vector<double> angles(nAngles+1);
    REP(i, nAngles) {
        int j = (i+1) % nAngles;
        angles[i] = arg(convex[j]-convex[i]);
    }
    angles[nAngles] = angles[0];
    REP(i, nAngles)
        if (angles[i+1] < angles[i])
            angles[i+1] += 2*PI;

    P sum = 0;
    REP(i, n)
        sum += points[i];

    double res = 1e100;
    REP(iAngle, nAngles) {
        double inf = -angles[iAngle+1];
        double sup = -angles[iAngle];
        P bottom = convex[(iAngle+1)%nAngles];
        P f = sum - (double)n * bottom;

        //printf("%.0f to %.0f: bottom = (%.0f, %.0f), f = %.0f + %.0fi, imag_min = %.2f\n", angles[iAngle]*180/PI, angles[iAngle+1]*180/PI, bottom.real(), bottom.imag(), f.real(), f.imag(), imag_min(f, inf, sup));

        res <?= imag_min(f, inf, sup);
    }

    return res;
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        cin >> n;
        points.clear();
        REP(i, n) {
            double x, y;
            cin >> x >> y;
            points.push_back(P(x, y));
        }

        printf("Case #%d: %.3f\n", iCase+1, solve()/n+EPS);

    }

    return 0;
}

