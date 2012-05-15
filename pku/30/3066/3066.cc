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

#define EPS 1.0e-10


int main() {
    int m, p;
    double a, b;

    if (!(cin >> m >> p >> a >> b))
        return 0;

    double xmax = sqrt(a);
    double xmin = -1.0/sqrt(a);
    double sum = b*sqrt(a);

    double x[m];
    REP(i, m)
        x[i] = 0;

    if (b >= 0) {
        double r = sum;
        REP(i, m) {
            x[i] = min(r, xmax);
            r -= x[i];
        }
    }
    else {
        double r = sum;
        for(int i = m-1; i >= 0; i--) {
            x[i] = max(r, xmin);
            r -= x[i];
        }
    }

    bool improve;
    do {
        improve = false;

        for(int i = 0; i < m; i++) {
            for(int j = m-1; j >i ; j--) {
                double dx = min(xmax-x[i], x[j]-xmin);
                if (dx > EPS) {
                    x[i] += dx;
                    x[j] -= dx;
                    improve = true;
                }
            }
        }

    } while(improve);

    double res = 0;
    REP(i, m)
        res += pow(abs(x[i]), p);

    printf("%.0f\n", res);
    return main();
}



// Powered by fate testarossa
