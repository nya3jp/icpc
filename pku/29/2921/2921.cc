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

#define N 300
#define EPS 1.0e-9
const double PI = acos(0.0)*2;

void solve() {

    int n;
    cin >> n;
    vector<double> v(n);
    REP(i, n) {
        int num, denom;
        scanf("%d%d", &num, &denom);
        v[i] = (double)num/denom * 2;
    }
    v.resize(2*n);
    REP(i, n)
        v[i+n] = v[i] + 2;

    double res = 0;
    {
        int j = 0;
        REP(i, n) {
            while(j+1 < 2*n && v[j+1]-v[i] <= 1+EPS)
                j++;
            res >?= v[j]-v[i];
            if (j+1 < 2*n)
                res >?= 2-(v[j+1]-v[i]);
        }
    }

    printf("%.2f\n", sqrt(2*n*n*(1-cos(res*PI))));
}

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        cout << "Scenario #" << iCase+1 << ":" << endl;
        solve();
        cout << endl;
    }

    return 0;
}
