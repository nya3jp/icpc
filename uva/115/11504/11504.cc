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

int n, m;
vector<int> gf[100000+10];
vector<int> gr[100000+10];

void dfs(int cur, vector<int>* g, vector<bool>& visited, vector<int>& comp) {
    if (visited[cur])
        return;
    visited[cur] = true;
    vector<int>& v = g[cur];
    REP(i, v.size()) {
        int next = v[i];
        dfs(next, g, visited, comp);
    }
    comp.push_back(cur);
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        scanf("%d%d", &n, &m);

        REP(i, n) {
            gf[i].clear();
            gr[i].clear();
        }

        REP(i, m) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--; b--;
            gf[a].push_back(b);
            gr[b].push_back(a);
        }

        vector<int> order;
        vector<bool> visited(n, false);
        REP(s, n) {
            if (visited[s])
                continue;
            dfs(s, gf, visited, order);
        }
        reverse(ALLOF(order));
        visited.assign(n, false);
        vector<int> colors(n, -1);
        int color = 0;
        REP(i, n) {
            int s = order[i];
            if (visited[s])
                continue;
            vector<int> comp;
            dfs(s, gr, visited, comp);
            REP(j, comp.size())
                colors[comp[j]] = color;
            color++;
        }

        vector<bool> top(color, true);
        REP(a, n) {
            vector<int>& v = gf[a];
            REP(i, v.size()) {
                int b = v[i];
                if (colors[a] != colors[b]) {
                    top[colors[b]] = false;
                }
            }
        }

        printf("%d\n", count(ALLOF(top), true));

    }

    return 0;
}
