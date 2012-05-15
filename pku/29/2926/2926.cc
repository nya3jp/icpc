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

#define N 100000

double v[N][5];

const double INF = numeric_limits<double>::infinity();

int main() {

    int n;
    scanf("%d", &n);

    REP(i, n) REP(j, 5)
        scanf("%lf", &v[i][j]);

    double res = 0;
    REP(p, 1<<4) {
        double sup = -INF, inf = INF;
        REP(i, n) {
            double s = 0;
            REP(j, 5)
                s += v[i][j] * ((p&(1<<j)) == 0 ? 1 : -1);
            sup >?= s;
            inf <?= s;
        }
        res >?= sup-inf;
    }

    printf("%.2f\n", res);

    return 0;
}



// Powered by fate testarossa
