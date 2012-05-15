#include <iostream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 100

void solve() {
    int n;
    cin >> n;
    int preferences[N][8];
    REP(i, n) REP(j, 8)
        cin >> preferences[i][j];
    int outcomes[N+1][8];
    REP(j, 8)
        outcomes[n][j] = j;
    for(int i = n-1; i >= 0; i--) {
        REP(j, 8) {
            int flip;
            int preference = 10;
            int oc;
            REP(k, 3) {
                int o = outcomes[i+1][j^(1<<k)];
                int p = preferences[i][o];
                if (p < preference) {
                    preference = p;
                    flip = k;
                    oc = o;
                }
            }
            outcomes[i][j] = oc;
        }
    }
    const char RES[2] = {'N', 'Y'};
    REP(k, 3)
        printf("%c", RES[(outcomes[0][0]>>(2-k))&1]);
    printf("\n");
}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}
