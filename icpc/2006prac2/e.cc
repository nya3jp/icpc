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
#define ALLOF(c) ((c).begin()), ((c).end())

#define EPS 1.0e-8

vector<double> xs, ys, xt;
int n;

double f(double x) {
    if (x < xs[0] || x > xs[n-1])
        return 0;
    int idx = n-2;
    REP(i, n-1) {
        if (x < xs[i+1]) {
            idx = i;
            break;
        }
    }
    return (ys[idx+1]-ys[idx])*(x-xs[idx])/(xs[idx+1]-xs[idx])+ys[idx];
}
double df(double x) {
    if (x < xs[0] || x > xs[n-1])
        return 0;
    int idx = n-2;
    REP(i, n-1) {
        if (x < xs[i+1]) {
            idx = i;
            break;
        }
    }
    return (ys[idx+1]-ys[idx])/(xs[idx+1]-xs[idx]);
}

int main() {
    ifstream cin("E.txt");

    double r;
    while(cin >> n >> r && n > 0) {

        xs.resize(n);
        ys.resize(n);
        REP(i, n)
            cin >> xs[i] >> ys[i];

        xt.resize(2*n);
        copy(ALLOF(xs), xt.begin());
        copy(ALLOF(xs), xt.begin()+n);
        REP(i,n)
            xt[i+n] -= r;

        sort(ALLOF(xt));

        double res = 0;

        REP(i, 2*n-1) {

            double w = xt[i+1]-xt[i];

            double y1 = f(xt[i]+EPS);
            double d1 = df(xt[i]+EPS);
            double y2 = f(xt[i]+r+EPS);
            double d2 = df(xt[i]+r+EPS);

            /*
            printf("x = %.2f\nw = %.2f\ny1 = (%.2f,%.2f)\ny2 = (%.2f,%.2f)\n",
                   xt[i], w, y1, d1, y2, d2);
            */

            double s =  d1*d2*w*w*w/3 + (d1*y2+d2*y1)*w*w/2 + y1*y2*w;

            /*
            printf("s = %.2f\n", s);
            */
            res += s;

        }

        printf("%.10f\n", res);

    }

    return 0;
}

// Powered by Fate Testarossa
