#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

#define N 1000
#define C 30

void solve() {
    int n;
    scanf("%d", &n);
    int values[N], costs[N];
    REP(i, n)
        scanf("%d%d", &values[i], &costs[i]);
    int res = 0;
    int m;
    scanf("%d", &m);
    while(m-- > 0) {
        int c;
        scanf("%d", &c);
        int v[C+1];
        REP(i, c+1) v[i] = 0;
        int mx = 0;
        REP(k, n) for(int i = c; i >= costs[k]; i--)
            mx >?= v[i] >?= v[i - costs[k]] + values[k];
        res += mx;
    }
    printf("%d\n", res);
}

int main() {
    int n;
    scanf("%d", &n);
    while(n-- > 0)
        solve();
    return 0;
}
