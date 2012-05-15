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

struct Stage {
    long long s, l, t, c;
};
Stage stages[1000+10];
int n;
double memo[1000+10][10000+10];

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        cin >> n;

        REP(i, n) {
            Stage& s = stages[i];
            scanf("%lld%lld%lld%lld", &s.s, &s.l, &s.t, &s.c);
        }
        reverse(stages, stages+n);

        REP(i, n)
            memo[i][0] = 0;
        for(int l = 0; l <= 10000; l++)
            memo[n][l] = 0;
        double res = 0;
        for(int l = 1; l <= 10000; l++) {
            for(int i = n-1; i >= 0; i--) {
                memo[i][l] = memo[i+1][l];
                Stage& stage = stages[i];
                if (l >= stage.s + stage.l && 10*stage.t >= 98*l) {
                    memo[i][l] = max(memo[i][l],
                                     (stage.t*log((double)l/(l-stage.l)) - 9.8*stage.l) / stage.c +
                                     memo[i+1][l-(stage.s+stage.l)]);
                }
            }
            res = max(res, memo[0][l]);
        }

        printf("%.0f\n", res);

    }

    return 0;
}
