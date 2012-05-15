#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

typedef vector< vector<int> > AList;

AList g;

void dfs(int a, vector<int>& route) {
    while(!g[a].empty()) {
        int b = g[a].back();
        g[a].pop_back();
        g[b].erase(find(ALLOF(g[b]), a));
        dfs(b, route);
    }
    route.push_back(a);
}
void solve() {
    int m;
    cin >> m;
    g.clear(); g.resize(50);
    REP(i, m) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int n = g.size();
    vector<int> route;
    int start = 50;
    REP(i, n) {
        if (g[i].size()%2 != 0) {
            cout << "Some beads may be lost" << endl;
            return;
        }
        if (!g[i].empty())
            start <?= i;
    }
    dfs(start, route);
    reverse(route.begin(), route.end());
    REP(i, m) {
        int j = (i+1)%m;
        cout << route[i]+1 << ' ' << route[j]+1 << endl;
    }
}

int main() {
    int n;
    cin >> n;
    REP(i, n) {
        if (i > 0) cout << endl;
        cout << "Case #" << i+1 << endl;
        solve();
    }
    return 0;
}

// Powered by Fate Testarossa
