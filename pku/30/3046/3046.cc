#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 100000
#define M 1000
#define MOD 1000000

int dp0_[N+1], dp1_[N+1];
int counts[M];




int main() {

    int m, n, from, to;
    scanf("%d%d%d%d", &m, &n, &from, &to);

    REP(i, m)
        counts[i] = 0;

    REP(i, n) {
        int t;
        scanf("%d", &t);
        t--;
        counts[t]++;
    }

    int* dp0 = dp0_;
    int* dp1 = dp1_;

    REP(j, n+1)
        dp0[j] = (j == 0 ? 1 : 0);

    for(int i = 0; i < m; i++) {
        dp1[0] = 1;
        for(int j = 1; j <= counts[i]; j++)
            dp1[j] = (dp1[j-1] + dp0[j]) % MOD;
        for(int j = counts[i]+1; j <= n; j++)
            dp1[j] = (dp1[j-1] + dp0[j] - dp0[j-(counts[i]+1)] + MOD) % MOD;
        swap(dp0, dp1);
    }

    int res = 0;
    for(int j = from; j <= to; j++)
        res += dp0[j], res %= MOD;

    printf("%d\n", res);

    return 0;
}
