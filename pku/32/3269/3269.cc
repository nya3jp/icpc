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

#define N 10000

int cows[N][2];
int xs[N], ys[N];

int main() {

    int n;
    scanf("%d", &n);
    REP(i, n) {
        int x, y;
        scanf("%d%d", &x, &y);
        cows[i][0] = x;
        cows[i][1] = y;
        xs[i] = x;
        ys[i] = y;
    }
    sort(xs, xs+n);
    sort(ys, ys+n);

    int xl, xh, yl, yh;
    if (n%2 == 0) {
        xl = xs[n/2-1];
        xh = xs[n/2];
        yl = ys[n/2-1];
        yh = ys[n/2];
    }
    else {
        xl = xh = xs[n/2];
        yl = yh = ys[n/2];
    }

    int res_count = (xh-xl+1)*(yh-yl+1);
    int res_dist = 0;
    REP(i, n) {
        int x = cows[i][0], y = cows[i][1];
        res_dist += abs(xl-x) + abs(yl-y);
        if (xl <= x && x <= xh && yl <= y && y <= yh)
            res_count--;
    }

    if (res_count == 0) {
        assert(n % 2 == 1);
        int cands[4] = {0,0,0,0};
        REP(i, n) {
            int x = cows[i][0], y = cows[i][1];
            cands[0] += abs(xl-1-x) + abs(yl-y);
            cands[1] += abs(xl+1-x) + abs(yl-y);
            cands[2] += abs(xl-x) + abs(yl-1-y);
            cands[3] += abs(xl-x) + abs(yl+1-y);
        }
        res_dist = *min_element(cands, cands+4);
        res_count = count(cands, cands+4, res_dist);
    }

    printf("%d %d\n", res_dist, res_count);

    return 0;
}
