#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> xs(n), ys(n);
    REP(i, n)
        cin >> xs[i] >> ys[i];

    int table[s+1][s+1];
    const int INF = 1000;
    REP(i, s+1) REP(j, s+1) table[i][j] = INF;
    table[0][0] = 0;
    
    REP(k, n) REP(i, s+1-xs[k]) REP(j, s+1-ys[k])
        table[i+xs[k]][j+ys[k]] <?= table[i][j] + 1;

    int res = INF;
    {
        int j = s;
        for(int i = 0; i <= s; i++) {
            while(i*i+j*j > s*s)
                j--;
            if (i*i+j*j == s*s)
                res <?= table[i][j];
        }
    }

    if (res == INF)
        cout << "not possible" << endl;
    else
        cout << res << endl;
}

int main() {
    int n;
    cin >> n;
    while(n-- > 0)
        solve();
    return 0;
}
