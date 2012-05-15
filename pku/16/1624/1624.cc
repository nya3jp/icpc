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

double area(vector<P> g) {
    int n = g.size();
    double res = 0;
    REP(i, n) {
        int j = (i+1)%n;
        res += (conj(g[i])*g[j]).imag();
    }
    return abs(res)/2;
}

int main() {

    // May fate be with you!

    int iCase = 0;
    for(;;) {
        vector<P> g;

        REP(i, 4) {
            double x, y;
            cin >> x >> y;
            g.push_back(P(x, y));
        }

        bool last = true;
        REP(i, 4)
            if (norm(g[i]) > 0)
                last = false;
        if (last)
            break;

        vector<P> points(8);
        REP(i, 4)
            points[i*2] = g[i];
        REP(i, 4)
            points[i*2+1] = (g[i] + g[(i+1)%4]) / 2.0;

        double total = area(g);

        double res = 0;
        REP(i, 4) REP(j, 3) {
            vector<int> c;
            c.push_back(i*2);
            c.push_back(i*2+2);
            c.push_back(i*2+3+j);
            vector<P> cc;
            REP(i, c.size())
                cc.push_back(points[c[i]%8]);
            double s = area(cc);
            res >?= min(s, total-s);
        }
        REP(i, 4) {
            vector<int> c;
            c.push_back(i*2+1);
            c.push_back(i*2+2);
            c.push_back(i*2+3);
            vector<P> cc;
            REP(i, c.size())
                cc.push_back(points[c[i]%8]);
            double s = area(cc);
            res >?= min(s, total-s);
        }
        REP(i, 4) {
            vector<int> c;
            c.push_back(i*2+1);
            c.push_back(i*2+2);
            c.push_back(i*2+4);
            c.push_back(i*2+5);
            vector<P> cc;
            REP(i, c.size())
                cc.push_back(points[c[i]%8]);
            double s = area(cc);
            res >?= min(s, total-s);
        }

        printf("Cake %d: %.3f %.3f\n",
               ++iCase, res, total-res);

    }

    return 0;
}



// Powered by fate testarossa
