#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct UF {
    vector<int> v;
    UF(int n) : v(n, -1) {}
    void link(int a, int b) {
        v[root(a)] = root(b);
    }
    int check(int a, int b) {
        return (root(a) == root(b));
    }
    int root(int i) {
        return (v[i] < 0 ? i : (v[i] = root(v[i])));
    }
};

struct Edge {
    int src, dest, w;
    Edge() {
    }
    Edge(int src, int dest, int w) : src(src), dest(dest), w(w) {
    }
};

bool operator<(const Edge& a, const Edge& b) {
    return (a.w < b.w);
}

int solve(vector<Edge>& edges, int n) {

    UF uf(n);

    // assume there is always at least one MST
    int totalWeight = 0;
    int lastWeight;
    int iEdge = 0, nTreeEdge = 0;
    while(iEdge < (int)edges.size() && nTreeEdge < n-1) {
        Edge& e = edges[iEdge];
        iEdge++;
        if (!uf.check(e.src, e.dest)) {
            uf.link(e.src, e.dest);
            totalWeight += e.w;
            lastWeight = e.w;
            nTreeEdge++;
        }
    }

    bool tie = (iEdge < (int)edges.size() && edges[iEdge].w == lastWeight);

    return (tie ? -1 : totalWeight);
}

int main() {
    int nCases;
    scanf("%d", &nCases);
    while(nCases-- > 0) {

        int n, m;
        scanf("%d%d", &n, &m);
        vector<Edge> edges(m);
        for(int i = 0; i < m; i++) {
            Edge& e = edges[i];
            scanf("%d%d%d", &e.src, &e.dest, &e.w);
            e.src--; e.dest--;
        }

        int cost = solve(edges, n);

        if (cost < 0)
            printf("Not Unique!\n");
        else
            printf("%d\n", cost);
    }
}

