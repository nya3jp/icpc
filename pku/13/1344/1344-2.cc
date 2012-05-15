#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

#define N 100

int adj[N][N];
int n;

int solve(vector<int> v, int low=0) {
    map<int, vector<int> > m;
    const int a = 0, b = v[0];
    for(int i = 1; i < (int)v.size(); i++) {
        int c = v[i];
        int ax = (adj[a][b] + adj[a][c] - adj[b][c]) / 2;
        m[ax].push_back(c);
    }

    int res = adj[a][b] - low;
    FOR(it, m)
        res += solve(it->second, it->first);
    return res;
}

int main() {

    for(;;) {
        cin >> n;

        if (n == 0)
            break;

        REP(i, n)
            adj[i][i] = 0;

        REP(i, n) for(int j = i+1; j < n; j++) {
            int x;
            cin >> x;
            adj[i][j] = adj[j][i] = x;
        }

        vector<int> v;
        for(int i = 1; i < n; i++)
            v.push_back(i);

        cout << solve(v) << endl;

    }

    return 0;
}
