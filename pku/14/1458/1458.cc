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
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define N 2000
char s1[N], s2[N];
int dp[N+1][N+1];

int lcs() {
    int n1 = strlen(s1), n2 = strlen(s2);
    REP(i, n1+1)
        dp[i][0] = 0;
    REP(j, n2+1)
        dp[0][j] = 0;
    REP(i, n1) REP(j, n2) {
        if (s1[i] == s2[j])
            dp[i+1][j+1] = dp[i][j] + 1;
        else
            dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
    }
    return dp[n1][n2];
}

int main() {

    while(scanf("%s%s", s1, s2) == 2)
        printf("%d\n", lcs());

    return 0;
}

