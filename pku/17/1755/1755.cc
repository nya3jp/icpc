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

const long double EPS = 1.0e-18;

typedef complex<long double> P;
typedef vector<P> G;

struct L {
    P pos, dir;
};

G cut_polygon(const G& g, L cut) {
    int n = g.size();

    G res;

    REP(i, n) {
        P from(g[i]), to(g[(i+1)%n]);
        long double p1 = (conj(cut.dir)*(from-cut.pos)).imag();
        long double p2 = (conj(cut.dir)*(to-cut.pos)).imag();
        if (p1 > -EPS) {
            res.push_back(from);
            if (p2 < -EPS && p1 > EPS)
                res.push_back(from - (to-from)*p1/(conj(cut.dir)*(to-from)).imag());
        }
        else if (p2 > EPS)
            res.push_back(from - (to-from)*p1/(conj(cut.dir)*(to-from)).imag());
        }
    }

    return res;
}

long double area(const G& g) {
    int n = g.size();
    long double res = 0;
    REP(i, n) {
        int j = (i+1)%n;
        res += (conj(g[i])*g[j]).imag();
        //cout << g[i] << " ... ";
    }
    //cout << g.front() << endl;
    return abs(res) / 2;
}

struct param_t {
    long double p, q, r;
};

int main() {

    int n;
    cin >> n;

    vector<param_t> params(n);
    REP(i, n) {
        param_t& p = params[i];
        cin >> p.p >> p.q >> p.r;
    }

    REP(toWin, n) {
        const P UNIT[] = {P(0, 0), P(1, 0), P(0, 1)};
        G poly(UNIT, UNIT+3);

        const param_t& p0 = params[toWin];
        REP(toLose, n) {
            if (toLose == toWin)
                continue;
            
            const param_t& p1 = params[toLose];
            long double a = (1/p1.p-1/p1.r)-(1/p0.p-1/p0.r);
            long double b = (1/p1.q-1/p1.r)-(1/p0.q-1/p0.r);
            long double c = 1/p1.r-1/p0.r;

            if (hypot(a, b) < EPS) {
                if (c < EPS)
                    poly.clear();
                continue;
            }

            //printf("%.2fx + %.2fy + %.2f > 0\n", a, b, c);
            
            L cut = {polar(-c/abs(P(a, b)), atan2(b, a)), P(b, -a)};

            assert(abs(a*cut.pos.real() + b*cut.pos.imag() + c) < EPS);

            if ((conj(P(a, b))*cut.dir*P(0, 1)).real() < 0) {
                cut.dir = -cut.dir;
            }

            //cout << cut.pos << " " << cut.dir << endl;

            poly = cut_polygon(poly, cut);

        }

        cout << ((area(poly) > EPS) ? "Yes" : "No") << endl;

    }

    return 0;
}
