#include <iostream>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 30
#define V 50
#define M ((2*N-1)*V)

int n;
int field[2*N-1][N];
bool dp[2*N-1][N][M+V+1];

void solve() {
    REP(i, 2*N-1) REP(j, N) REP(v, M+V+1)
        dp[i][j][v] = false;
    dp[0][0][abs(field[0][0])] = true;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            int left = j-1, right = j;
            if (j == 0)
                left = right;
            if (j == i)
                right = left;
            REP(v, M+1)
                dp[i][j][v] = dp[i-1][left][abs(v-field[i][j])] || dp[i-1][left][abs(v+field[i][j])] ||
                              dp[i-1][right][abs(v-field[i][j])] || dp[i-1][right][abs(v+field[i][j])];
        }
    }
    for(int i = n; i < 2*n-1; i++) {
        for(int j = 0; j <= 2*n-i-2; j++) {
            int left = j, right = j+1;
            REP(v, M+1)
                dp[i][j][v] = dp[i-1][left][abs(v-field[i][j])] || dp[i-1][left][abs(v+field[i][j])] ||
                              dp[i-1][right][abs(v-field[i][j])] || dp[i-1][right][abs(v+field[i][j])];
        }
    }
    REP(v, M+1) {
        if (dp[2*n-2][0][v]) {
            cout << v << endl;
            break;
        }
    }
}

int main() {
    cin >> n;
    if (n == 0)
        return 0;
    REP(k, n) {
        int i = k;
        REP(j, k+1)
            cin >> field[i][j];
    }
    REP(k, n-1) {
        int i = n+k;
        REP(j, n-1-k)
            cin >> field[i][j];
    }
    solve();
    return main();
}
