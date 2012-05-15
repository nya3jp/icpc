#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 1000

bool adj[N][N];
long long int dp[N][N];

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        int n1, n2, m;
        scanf("%d%d%d", &n1, &n2, &m);

        REP(i, n1) REP(j, n2)
            adj[i][j] = false;

        REP(i, m) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--;
            b = n2 - b;
            adj[a][b] = true;
        }

        REP(i, n1) REP(j, n2)
            dp[i][j] = 0;
        long long int res = 0;
        for(int i = n1-2; i >= 0; i--) {
            for(int j = n2-2; j >= 0; j--) {
                dp[i][j] = dp[i+1][j] + dp[i][j+1] - dp[i+1][j+1] + (adj[i+1][j+1] ? 1 : 0);
                if (adj[i][j])
                    res += dp[i][j];
            }
        }

        cout << "Test case " << iCase+1 << ": " << res << endl;

    }


    return 0;
}
