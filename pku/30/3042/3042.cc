#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

typedef long long int integer ;

const integer INF = 1ll << 60;
integer dp[1001][1001+1][2];

int main() {
    int n;
    cin >> n;
    n++;

    vector<int> v(n);
    REP(i, n)
        cin >> v[i];

    int spos = v[0];
    sort(ALLOF(v));

    int s = lower_bound(ALLOF(v), spos) - v.begin();

    REP(i, n)
        dp[i][1][0] = dp[i][1][1] = (i == s ? 0 : INF);

    for(int len = 2; len <= n; len++) {
        for(int pos = 0; pos+len <= n; pos++) {
            dp[pos][len][0] = min(dp[pos+1][len-1][0] + (v[pos+1] - v[pos]),
                                  dp[pos+1][len-1][1] + (v[pos+len-1] - v[pos]));
            dp[pos][len][1] = min(dp[pos][len-1][0] + (v[pos+len-1] - v[pos]),
                                  dp[pos][len-1][1] + (v[pos+len-1] - v[pos+len-2]));
            printf("[%d-%d] %lld %lld\n", pos, pos+len-1, dp[pos][len][0], dp[pos][len][1]);
        }
    }

    cout << min(dp[0][n][0], dp[0][n][1]) << endl;


    return 0;
}
