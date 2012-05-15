#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Edges;
typedef vector<Edges> Graph;

int color(Graph& g, int a, int c1, int c2, vector<int>& coloring) {
    if (coloring[a] >= 0)
        return (coloring[a] == c1 ? c1 : -1);
    coloring[a] = c1;
    Edges& v = g[a];
    for(int i = 0; i < (int)v.size(); i++) {
        int b = v[i];
        if (color(g, b, c2, c1, coloring) < 0)
            return -1;
    }
    return c1;
}

int count(Graph& g, int a, int c, vector<int>& coloring, vector<bool>& visited) {
    if (visited[a])
        return 0;
    visited[a] = true;
    int cnt = (coloring[a] == c ? 1 : 0);
    Edges& v = g[a];
    for(int i = 0; i < (int)v.size(); i++) {
        int b = v[i];
        cnt += count(g, b, c, coloring, visited);
    }
    return cnt;
}

int solve(Graph& g) {

    int n = g.size();

    vector<int> levels(n, -1);
    vector<int> coloring(n, -1);

    int level = 0;
    for(int a = 0; a < n; a++) {
        if (levels[a] < 0) {
            color(g, a, level, level, levels);
            level++;
        }
    }

    int nInvites = 0;
    vector<bool> visited(level, false);
    for(int a = 0; a < n; a++) {
        if (!visited[levels[a]]) {
            visited[levels[a]] = true;
            if (color(g, a, 0, 1, coloring) >= 0) {
                vector<bool> counter(n, false);
                int friends = count(g, a, 0, coloring, counter);
                counter.assign(n, false);
                int foes = count(g, a, 1, coloring, counter);
                nInvites += max(friends, foes);
            }
        }
    }
    return nInvites;
}

int main() {

    int nCases;
    cin >> nCases;

    while(nCases-- > 0) {

        int n;
        cin >> n;

        Graph g(n);
        for(int a = 0; a < n; a++) {
            int m;
            cin >> m;
            for(int j = 0; j < m; j++) {
                int b;
                cin >> b;
                b--;
                if (b < n) {
                    g[a].push_back(b);
                    g[b].push_back(a);
                }
            }
        }

        cout << solve(g) << endl;

    }

    return 0;
}
