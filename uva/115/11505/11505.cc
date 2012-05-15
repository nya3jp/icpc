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

typedef complex<double> P;

const double PI = acos(-1.0);

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        int n;
        scanf("%d", &n);

        P pos(0, 0);
        double angle = 0;

        REP(i, n) {
            string cmd;
            double len;
            cin >> cmd >> len;
            if (cmd == "fd") {
                pos += polar(len, angle);
            }
            else if (cmd == "bk") {
                pos -= polar(len, angle);
            }
            else if (cmd == "lt") {
                angle += len / 180 * PI;
            }
            else if (cmd == "rt") {
                angle -= len / 180 * PI;
            }
        }

        printf("%.0f\n", abs(pos));

    }

    return 0;
}
