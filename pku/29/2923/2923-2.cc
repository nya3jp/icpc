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

//#define min(a,b) (a < b ? a : b)
//#define max(a,b) (a > b ? a : b)
//#define for if(0);else for

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

int n;
int v[10];
int dp[1<<10];
int pos1[1<<10];
int pos2[1<<10];

int pack(int p0, int* pos) {
    memset(dp, 0x12, sizeof(dp));
    dp[p0] = 0;
    for(int p = p0; p; p = ((p-1)&p0)) {
        for(int q = p; q; q = ((q-1)%p)) {
            if (pos[q]) {
                dp[p-q] = min(dp[p-q], dp[p] + 1);
            }
        }
    }
    return dp[0];
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {
        int c1, c2;
        scanf("%d%d%d", &n, &c1, &c2);
        REP(i, n)
            scanf("%d", &v[i]);
        REP(p, 1<<n) {
            int s = 0;
            REP(i, n)
                if (p & (1<<i))
                    s += v[i];
            pos1[p] = (s <= c1);
            pos2[p] = (s <= c2);
        }
        int res = INT_MAX;
        REP(p, 1<<n) {
            int a = pack(p, pos1);
            if (a >= res)
                continue;
            int b = pack((1<<n)-1-p, pos2);
            res = min(res, max(a, b));
        }
        printf("Scenario #%d:\n%d\n\n", iCase+1, res);
    }

    return 0;
}
