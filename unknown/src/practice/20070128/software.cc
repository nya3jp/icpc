#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 100
#define M 100

#define INF 100000000

int n, m;

int times[M][2];

int solve(int limit) {
    int dp[M+1];
    REP(i, m)
        dp[i+1] = -INF;
    dp[0] = 0;

    REP(i, n) {
        int dp2[M+1];
        REP(j, m+1)
            dp2[j] = -INF;
        REP(left, m+1) {
            for(int doleft = 0; doleft <= left && doleft*times[i][0] <= limit; doleft++) {
                int remain = (limit-doleft*times[i][0])/times[i][1];
                if (dp[left-doleft] != -INF)
                    dp2[left] >?= dp[left-doleft]+remain;
            }
        }
        REP(j, m+1)
            dp[j] = dp2[j];
    }

    return dp[m];
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        cin >> n >> m;

        REP(i, n) REP(j, 2)
            cin >> times[i][j];

        int lower = 0;
        int upper = 1;
        while(solve(upper) < m)
            upper *= 2;

        while(upper-lower > 0) {
            int middle = (lower+upper)/2;
            if (solve(middle) < m)
                lower = middle+1;
            else
                upper = middle;
        }

        cout << lower << endl;


    }

    return 0;
}
