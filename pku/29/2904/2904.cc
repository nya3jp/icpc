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

// f(s,t,m) = min(s<=i<=t) i+max(f(s,i-1,m-1), f(i+1,t,m))

#define N 100
#define K 10

int dp[N+2][N+1][K+1];

const int INF = numeric_limits<int>::max()/4;

int main() {

    REP(i, N+2) REP(j, N+1) REP(k, K+1)
        dp[i][j][k] = INF;
    REP(i, N+2) REP(k, K+1)
        dp[i][0][k] = 0;

    for(int k = 1; k <= K; k++) {
        for(int w = 1; w <= N; w++) {
            for(int s = 1; s+w-1 <= N; s++) {
                int t = s+w;
                int& res = dp[s][w][k];
                for(int c = s; c < t; c++) {
                    res <?= c + max(dp[s][c-s][k-1], dp[c+1][t-c-1][k]);
                }
            }
        }
    }

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        int k, m;
        cin >> k >> m;
        cout << dp[1][m][k] << endl;
    }
    return 0;
}

// Powered by Fate Testarossa
