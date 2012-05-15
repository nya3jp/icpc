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

const double EPS = 1.0e-8;

typedef complex<double> P;
typedef vector<P> G;

struct L {
    P pos, dir;
};

G cut_polygon(const G& g, L cut) {
    int n = g.size();

    G res;

    REP(i, n) {
        int j = (i+1)%n;
        P from(g[i]), to(g[j]);
        double p1 = (conj(cut.dir)*(from-cut.pos)).imag();
        double p2 = (conj(cut.dir)*(to-cut.pos)).imag();
        //cout << "cutting: p1=" << p1 << ", p2=" << p2 << endl;
        if (p1 > -EPS) {
            res.push_back(from);
            if (p2 < -EPS && p1 > EPS)
                res.push_back(from - (to-from)*p1/(conj(cut.dir)*(to-from)).imag());
        }
        else {
            if (p2 > EPS)
                res.push_back(from - (to-from)*p1/(conj(cut.dir)*(to-from)).imag());
        }
        /*
        if (p1 > EPS)
            res.push_back(from);
        if ((p1 > EPS) != (p2 > EPS))
            res.push_back(from - (to-from)*p1/(conj(cut.dir)*(to-from)).imag());
        */
    }

    return res;
}

double area(const G& g) {
    int n = g.size();
    double res = 0;
    REP(i, n) {
        int j = (i+1)%n;
        res += (conj(g[i])*g[j]).imag();
        //cout << g[i] << " ... ";
    }
    //cout << g.front() << endl;
    return abs(res) / 2;
}

double do_cut(G g, const vector<L>& cuts, int next, int nCovers) {
    if (nCovers == 0)
        return area(g);
    double res = 1.0e100;
    for(int cur = next; cur+nCovers <= (int)cuts.size(); cur++)
        res <?= do_cut(cut_polygon(g, cuts[cur]), cuts, cur+1, nCovers-1);
    return res;
}

int main() {

    for(;;) {

        int n, nCovers;
        double height;
        cin >> n >> nCovers >> height;

        if (n == 0 && nCovers == 0 && height == 0)
            break;

        nCovers <?= n;

        G g;
        REP(i, n) {
            double x, y;
            cin >> x >> y;
            g.push_back(P(x, y));
        }

        vector<L> cuts;
        REP(i, n) {
            int j = (i+1)%n;
            L cut = {g[i], g[j]-g[i]};
            cut.pos += cut.dir / abs(cut.dir) * height * P(0, 1);
            //cout << "cut: " << cut.pos << " ... " << (cut.pos+cut.dir) << endl;
            cuts.push_back(cut);
        }

        double res = area(g) - do_cut(g, cuts, 0, nCovers);

        printf("%.2f\n", res+EPS);

    }


    return 0;
}
