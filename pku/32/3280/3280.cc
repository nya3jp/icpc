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

int n;
int m;

char str[2048];
int costs[26][2];
bool avail[26];

int dp[2048][2048];

int main() {

    scanf("%d%d ", &m, &n);

    gets(str);

    REP(i, 26)
        avail[i] = false;

    REP(i, m) {
        char c;
        int a, r;
        scanf(" %c%d%d", &c, &a, &r);
        int k = (int)(c - 'a');
        avail[k] = true;
        costs[k][0] = a;
        costs[k][1] = r;
    }

    REP(i, n+1)
        dp[i][0] = 0;
    REP(i, n)
        dp[i][1] = 0;
    for(int len = 2; len <= n; len++) {
        for(int pos = 0; pos+len <= n; pos++) {
            int first = pos, last = pos+len-1;
            int kfirst = (int)(str[first] - 'a');
            int klast = (int)(str[last] - 'a');
            if (str[first] == str[last])
                dp[pos][len] = dp[pos+1][len-2];
            else
                dp[pos][len] = min(dp[pos+1][len-1] + min(costs[kfirst][1], costs[kfirst][0]),
                                   dp[pos][len-1] + min(costs[klast][1], costs[klast][0]));
        }
    }

    printf("%d\n", dp[0][n]);

    return 0;
}
