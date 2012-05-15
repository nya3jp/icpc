#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Edges;
typedef vector<Edges> Graph;


void dfs(Graph& g, int a, vector<bool>& visited) {
    if (visited[a])
        return;
    visited[a] = true;
    Edges& v = g[a];
    for(int i = 0; i < (int)v.size(); i++) {
        int b = v[i];
        dfs(g, b, visited);
    }
}

int cactus(Graph& g, int a, int h, vector<int>& state) {
    state[a] = h;

    int r = h;
    Edges& v = g[a];
    for(int i = 0; i < (int)v.size(); i++) {
        int b = v[i];
        int s;
        if (state[b] == -2)
            s = -1;
        else if (state[b] == -1)
            s = cactus(g, b, h+1, state);
        else
            s = state[b];

        if (r < h && s < h)
            r = -1;
        else
            r = min(r, s);
    }

    state[a] = -2;
    return r;
}

bool solve() {
    int n, m;
    cin >> n >> m;

    Graph g(n), r(n);

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        r[b].push_back(a);
    }

    if (n == 0)
        return true;

    {
        vector<bool> visited(n, false);
        dfs(g, 0, visited);
        if (count(visited.begin(), visited.end(), true) < n)
            return false;
    }
    {
        vector<bool> visited(n, false);
        dfs(r, 0, visited);
        if (count(visited.begin(), visited.end(), true) < n)
            return false;
    }

    {
        vector<int> state(n, -1);
        if (cactus(g, 0, 0, state) < 0)
            return false;
    }

    return true;
}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}
