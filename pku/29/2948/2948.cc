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
#include <bitset>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define N 500

int gold[N+1][N+1];
int silver[N+1][N+1];
int dp[N+1][N+1];

int main() {

    for(;;) {
        int h, w;
        scanf("%d%d", &h, &w);
        if (h == 0)
            break;

        REP(i, h) {
            int s = 0;
            gold[i][0] = 0;
            REP(j, w) {
                int x;
                scanf("%d", &x);
                s += x;
                gold[i][j+1] = s;
            }
        }
        REP(i, h) {
            int s = 0;
            gold[i][0] = 0;
            REP(j, w) {
                int x;
                scanf("%d", &x);
                s += x;
                silver[i][j+1] = s;
            }
        }

        REP(j, w+1)
            dp[0][j] = (j == 0 ? 0 : INT_MIN);

        REP(i, h) {
            int maxi = INT_MIN;
            REP(j, w+1) {
                maxi >?= dp[i][j];
                dp[i+1][j] = maxi + gold[i][j] + silver[i][w] - silver[i][j];
            }
        }

        int res = INT_MIN;
        REP(j, w+1)
            res >?= dp[h][j];
        printf("%d\n", res);
    }

    return 0;
}
