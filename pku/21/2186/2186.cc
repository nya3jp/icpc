#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Edges;
typedef vector<Edges> Graph;


void dfs(Graph& g, int a, vector<bool>& v, vector<int>& s) {
    if (v[a])
        return;
    v[a] = true;
    Edges& e = g[a];
    for(int i = 0; i < (int)e.size(); i++) {
        int b = e[i];
        dfs(g, b, v, s);
    }
    s.push_back(a);
}

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph g(n), r(n);

    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g[a].push_back(b);
        r[b].push_back(a);
    }

    vector<bool> v;
    vector<int> s;

    v.assign(n, false);
    for(int a = 0; a < n; a++) {
        dfs(g, a, v, s);
    }

    v.assign(n, false);
    vector<int> scc;
    while(!s.empty()) {
        int a = s.back();
        s.pop_back();
        if (!v[a]) {
            scc.clear();
            dfs(r, a, v, scc);
        }
    }

    v.assign(n, false);
    vector<int> w;
    dfs(r, scc.back(), v, w);

    int result;
    if ((int)w.size() == n)
        result = (int)scc.size();
    else
        result = 0;
    printf("%d\n", result);

    return 0;
}

