// PKU2378 Tree Cutting
// memoization O(E)

#include <cstdio>
#include <vector>

using namespace std;

struct Edge {
    int src, dest, data;
    Edge(int src=0, int dest=0, int data=-1)
        : src(src), dest(dest), data(data) {
    }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

int solve(Graph& g, Edge& e) {
    if (e.data < 0) {
        e.data = 1;
        Edges& v = g[e.dest];
        for(int i = 0; i < (int)v.size(); i++) {
            Edge& f = v[i];
            if (f.dest != e.src)
                e.data += solve(g, f);
        }
    }
    return e.data;
}
void solve(Graph& g) {
    int n = (int)g.size();
    for(int i = 0; i < n; i++) {
        Edges& v = g[i];
        int m = 0;
        for(int j = 0; j < (int)v.size(); j++)
            m = max(m, solve(g, v[j]));
        if (m <= n/2)
            printf("%d\n", i+1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Graph g(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g[a].push_back(Edge(a, b));
        g[b].push_back(Edge(b, a));
    }
    solve(g);
    return 0;
}
