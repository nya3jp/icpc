#include <iostream>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) (c).begin(), (c).end()

typedef vector<int> Edges;
typedef vector<Edges> Graph;

void dfs(Graph& g, int here, vector<bool>& visited, vector<int>& res) {
    if (visited[here])
        return;
    visited[here] = true;
    Edges& v = g[here];
    REP(i, v.size())
        dfs(g, v[i], visited, res);
    res.push_back(here);
}

void solve(Graph& g, Graph& r) {
    int n = g.size();

    Graph r(n);
    REP(i, n) FOR(it, g[i])
        r[*it].push_back(i);

    vector<int> order;
    {
        vector<bool> visited(n, false);
        REP(i, n)
            dfs(g, i, visited, order);
    }

    reverse(ALLOF(order));

    vector<int> comps;
    {
        vector<bool> visited(n, false);
        REP(i, n) {
            int repr = order[i];
            if (!visited[repr]) {
                comps.push_back(vector<int>());
                vector<int>& comp = comps.back();
                dfs(r, repr, visited, comp);
                
            }
        }
    }

    vector<int> all;
    {
        vector<bool> visited(n, false);
        dfs(r, sink.front(), visited, all);
    }

    if (all.size() == n) {
        sort(ALLOF(res));
        cout << res[0]+1;
        for(int i = 1; i < (int)res.size(); i++)
            cout << ' ' << res[i]+1;
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    if (n == 0)
        return 0;
    int m;
    cin >> m;

    Graph g(n);

    REP(i, m) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    solve(g);

    return main();
}
