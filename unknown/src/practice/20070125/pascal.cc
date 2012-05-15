#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


#define N 34


typedef long long int integer;
int board[N][N];
integer dp[N][N];

int main() {
    int n;

    while(cin >> n && n > 0) {

        REP(i, n) REP(j, n) {
            char c;
            cin >> c;
            board[i][j] = (int)(c - '0');
        }

        REP(i, n) REP(j, n)
            dp[i][j] = 0;
        dp[0][0] = 1;

        REP(i, n) REP(j, n) {
            int s = board[i][j];
            if (s > 0) {
                if (i+s < n)
                    dp[i+s][j] += dp[i][j];
                if (j+s < n)
                    dp[i][j+s] += dp[i][j];
            }
        }

        cout << dp[n-1][n-1] << endl;

    }

    return 0;
}
