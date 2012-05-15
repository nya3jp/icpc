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

bool arg_less(const P& a, const P& b) { return (arg(a) < arg(b)); }
// 一直線に並んでいる場合に注意
vector<P> convex_hull(vector<P> v) {
    int n = v.size(), m = 2;
    P g(EPS, 0);
    REP(i, n) g += v[i] / (double)n;
    REP(i, n) v[i] -= g;
    sort(ALLOF(v), arg_less);
    P first = v[0];
    REP(i, n) if (v[i].real() < first.real()) first = v[i];
    rotate(v.begin(), find(ALLOF(v), first), v.end());
    v.push_back(first);
    for(int i = 2; i <= n; v[m++] = v[i++])
        while(m >= 2 && (conj(v[m-1]-v[m-2])*(v[i]-v[m-2])).imag() < EPS)
            m--;
    v.resize(--m);
    REP(i, m) v[i] += g;
    return v;
}


int main() {

    string line;
    while(getline(cin, line)) {
        const char* str = line.c_str();

        vector<P> v;
        double x, y;
        int p;
        while(sscanf(str, " ( %lf , %lf )%n", &x, &y, &p) > 0) {
            str += p;
            v.push_back(P(x, y));
        }

        vector<P> res = convex_hull(v);

        REP(i, res.size()) {
            P p = res[i];
            printf("(%f,%f) ", p.real(), p.imag());
        }
        {
            P p = res[0];
            printf("(%f,%f)\n", p.real(), p.imag());
        }
    }

    return 0;
}

