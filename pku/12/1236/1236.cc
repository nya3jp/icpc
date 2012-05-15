#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

typedef vector<int> Edges;
typedef vector<Edges> Graph;

void dfs(Graph& g, int here, vector<bool>& visited, vector<int>& res) {
    if (!visited[here]) {
        visited[here] = true;
        REP(i, g[here].size()) {
            int there = g[here][i];
            dfs(g, there, visited, res);
        }
        res.push_back(here);
    }
}

int main() {

    int n;
    scanf("%d", &n);

    Graph g(n), r(n);

    REP(a, n) {
        for(;;) {
            int b;
            scanf("%d", &b);
            if (b == 0)
                break;
            b--;
            g[a].push_back(b);
            r[b].push_back(a);
        }
    }

    vector<int> order;
    {
        vector<bool> visited(n, false);
        REP(a, n)
            dfs(g, a, visited, order);
    }

    vector<int> sups, infs;
    {
        vector<bool> visited(n, false);
        for(int i = n-1; i >= 0; i--) {
            int a = order[i];
            if (!visited[a]) {
                vector<int> comp;
                dfs(r, a, visited, comp);
                vector<bool> in_comp(n, false);
                REP(j, comp.size())
                    in_comp[comp[j]] = true;
                bool sup = true, inf = true;
                REP(j, comp.size()) {
                    int p = comp[j];
                    REP(k, g[p].size()) {
                        int q = g[p][k];
                        if (!in_comp[q])
                            inf = false;
                    }
                    REP(k, r[p].size()) {
                        int q = r[p][k];
                        if (!in_comp[q])
                            sup = false;
                    }
                }
                if (sup)
                    sups.push_back(comp[0]);
                if (inf)
                    infs.push_back(comp[0]);
            }
        }
    }

    cout << sups.size() << endl;

    if (sups.size() == 1 && infs.size() == 1 && sups[0] == infs[0]) {
        cout << 0 << endl;
    }
    else {
        cout << max(sups.size(), infs.size()) << endl;
    }

    return 0;
}

