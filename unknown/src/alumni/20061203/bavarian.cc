#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 1000

int dp[N+1][N];

int solve(const vector<int>& v) {
    int u[N];
    int n = v.size();
    REP(i, n)
        u[i] = v[i];

    REP(i, n)
        dp[0][i] = 0;

    for(int len = 2; len <= n; len+=2) {
        for(int start = 0; start+len <= n; start++) {
            int res = -1;
            for(int segment = 2; segment <= len; segment+=2) {
                res >?= (u[start] == u[start+segment-1] ? 1 : 0) +
                    dp[segment-2][start+1] + dp[len-segment][start+segment];
            }
            assert(res >= 0);
            dp[len][start] = res;
            //cout << start << "-" << start+len-1 << " = " << dp[len][start] << endl;
        }
    }

    return dp[n][0];
}



int main() {

    ifstream cin("e.in");

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n;
        cin >> n;
        vector<int> v(n);
        REP(i, n)
            cin >> v[i];

        cout << solve(v) << endl;

    }

    return 0;
}
