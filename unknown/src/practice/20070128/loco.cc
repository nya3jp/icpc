#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 50000
#define K 3

int dp[N+1][K+1];
int given[N];
int sum[N+1];

const int INF = 10000000;

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n;
        cin >> n;
        REP(i, n)
            cin >> given[i];

        int m;
        cin >> m;

        sum[0] = 0;
        REP(i, m)
            sum[i+1] = sum[i] + given[i];
        for(int i = m; i < n; i++)
            sum[i+1] = sum[i] + given[i] - given[i-m];

        /*
        REP(i, n+1)
            cout << sum[i] << ' ';
        cout << endl;
        */

        REP(k, K+1) REP(i, n+1)
            dp[i][k] = -INF;
        REP(i, n+1)
            dp[i][0] = 0;

        for(int k = 1; k <= K; k++)
            for(int i = m; i <= n; i++)
                dp[i][k] = max(dp[i-m][k-1]+sum[i], dp[i-1][k]);

        cout << dp[n][K] << endl;
    }

    return 0;
}



