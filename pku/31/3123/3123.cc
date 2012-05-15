#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 30

inline int lsb(int x) {
    return x&-x;
}
inline int masked_inc(int x, int s) {
    return (((x|~s)+1)&s);
}

map<string,int> ids;

int id(const string& s) {
    if (ids.count(s) == 0)
        ids.insert(make_pair(s, ids.size()));
    return ids[s];
}

int adj[N][N];
const int INF = numeric_limits<int>::max()/4;

int main() {

    for(;;) {
        int n, m;
        cin >> n >> m;

        if (n == 0 && m == 0)
            break;

        ids.clear();

        REP(i, n) {
            string s;
            cin >> s;
            id(s);
        }

        REP(i, n) REP(j, n)
            adj[i][j] = INF;
        REP(i, n)
            adj[i][i] = 0;

        REP(i, m) {
            string s1, s2;
            int c;
            cin >> s1 >> s2 >> c;
            int k1 = id(s1), k2 = id(s2);
            adj[k1][k2] <?= c;
            adj[k2][k1] <?= c;
        }

        vector<int> targets;
        REP(i, 8) {
            string s;
            cin >> s;
            targets.push_back(id(s));
        }

        REP(j, n) REP(i, n) REP(k, n)
            adj[i][k] <?= adj[i][j] + adj[j][k];

        int dp[1<<8][N];
        REP(i, 1<<8) REP(j, n)
            dp[i][j] = INF;
        REP(j, n)
            dp[0][j] = 0;
        REP(i, 8) REP(j, n)
            dp[1<<i][j] = adj[targets[i]][j];
        for(int p = 1; p < (1<<8); p++)
            REP(l, n)
                for(int q = lsb(p); q != 0; q = masked_inc(q, p))
                    REP(k, n)
                        dp[p][l] <?= dp[q][k] + dp[p^q][k] + adj[l][k];

        int tree[1<<8];
        REP(i, 1<<8)
            tree[i] = INF;
        REP(i, 1<<8) REP(j, n)
            tree[i] <?= dp[i][j];

        int res = INF;
        res <?= tree[(3<<0)] + tree[(3<<2)] + tree[(3<<4)] + tree[(3<<6)];
        res <?= tree[(3<<0)|(3<<2)] + tree[(3<<4)] + tree[(3<<6)];
        res <?= tree[(3<<0)|(3<<4)] + tree[(3<<2)] + tree[(3<<6)];
        res <?= tree[(3<<0)|(3<<6)] + tree[(3<<2)] + tree[(3<<4)];
        res <?= tree[(3<<2)|(3<<4)] + tree[(3<<0)] + tree[(3<<6)];
        res <?= tree[(3<<2)|(3<<6)] + tree[(3<<0)] + tree[(3<<4)];
        res <?= tree[(3<<4)|(3<<6)] + tree[(3<<0)] + tree[(3<<2)];
        res <?= tree[(3<<0)|(3<<2)] + tree[(3<<4)|(3<<6)];
        res <?= tree[(3<<0)|(3<<4)] + tree[(3<<2)|(3<<6)];
        res <?= tree[(3<<0)|(3<<6)] + tree[(3<<2)|(3<<4)];
        res <?= tree[(3<<2)|(3<<4)] + tree[(3<<0)|(3<<6)];
        res <?= tree[(3<<2)|(3<<6)] + tree[(3<<0)|(3<<4)];
        res <?= tree[(3<<4)|(3<<6)] + tree[(3<<0)|(3<<2)];
        res <?= tree[(3<<0)|(3<<2)|(3<<4)] + tree[(3<<6)];
        res <?= tree[(3<<0)|(3<<2)|(3<<6)] + tree[(3<<4)];
        res <?= tree[(3<<0)|(3<<4)|(3<<6)] + tree[(3<<2)];
        res <?= tree[(3<<2)|(3<<4)|(3<<6)] + tree[(3<<0)];
        res <?= tree[(1<<8)-1];

        cout << res << endl;

    }

    return 0;
}

