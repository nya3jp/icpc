#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

int dp[10010][1010];
int v[10010];

int main() {

    int n, m;
    cin >> n >> m;

    memset(v, 0, sizeof(v));
    REP(i, n)
        cin >> v[i];

    memset(dp, 0, sizeof(dp));

    dp[0][1] = 1;

    REP(i, n) REP(j, m) {
        if (dp[i][j]) {
            dp[i+1][j] = j;
            dp[i+1][(j*v[i])%m] = j;
        }
    }

    int maximal = m-1;
    while(dp[n][maximal] == 0)
        maximal--;

    cout << maximal << endl;

    vector<int> res;
    for(int here = maximal, i = n; i > 0; here = dp[i][here], i--) {
        if (dp[i][here] != here)
            res.push_back(i);
    }

    reverse(ALLOF(res));

    REP(i, res.size())
        cout << res[i] << ' ';
    cout << endl;

    return 0;
}
