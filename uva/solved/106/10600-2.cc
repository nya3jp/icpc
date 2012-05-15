/*
 * Å¬Lˆæ–Ø‚ğ‹‚ß‚éKruskal‚ÌƒAƒ‹ƒSƒŠƒYƒ€
 */

#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <iostream>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;


template<class T>
struct UnionFind {
    map<T, T> repr;
    map<T, int> cnt;

    bool link(const T& a, const T& b) {
        const T& ra = getrepr(a);
        const T& rb = getrepr(b);
        if (ra != rb) {
            if (cnt[ra] > cnt[rb]) {
                cnt[ra] += cnt[rb];
                cnt[rb] = 0;
                repr[rb] = ra;
            }
            else {
                cnt[rb] += cnt[ra];
                cnt[ra] = 0;
                repr[ra] = rb;
            }
        }
        return (ra != rb);
    }
    bool check(const T& a, const T& b) {
        return (getrepr(a) == getrepr(b));
    }

    const T& getrepr(const T& a) {
        return (cnt[a] == 0 ? (repr[a] = getrepr(repr[a])) : a);
    }
};



typedef int Weight;

struct Edge {
    int src, dest;
    Weight weight;

    Edge() {
    }
    Edge(int src, int dest, Weight weight = 0) :
        src(src), dest(dest), weight(weight) {
    }
    friend bool operator>(const Edge& a, const Edge& b) {
        return (a.weight > b.weight);
    }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

const Weight WEIGHT_INFTY = 0x7fffffff; //std::numeric_limits<Weight>::max();

int dfs(const Graph& g, const Edge& edge, int goal) {
    if (edge.dest == goal)
        return edge.weight;

    const Edges& edges = g[edge.dest];
    for(int i = 0; i < (int)edges.size(); i++) {
        if (edges[i].dest != edge.src) {
            int w = dfs(g, edges[i], goal);
            if (w >= 0)
                return std::max(w, edge.weight);
        }
    }

    return -1;
}




void kruskal(Graph& g)
{
    const int n = g.size();

    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    UnionFind<int> uf;

    for(int i = 0; i < n; i++) {
        Edges& edges = g[i];
        for(int j = 0; j < (int)edges.size(); j++) {
            if (i < edges[j].dest)
                q.push(edges[j]);
        }
    }


    Edges tree;
    int tree_weight = 0;
    int next_diff = 1000000;
    Graph h(n);

    while(!q.empty()) {
        Edge e = q.top();
        q.pop();

        if (uf.link(e.src, e.dest)) {
            tree.push_back(e);
            tree_weight += e.weight;
            h[e.src].push_back(Edge(e.src, e.dest, e.weight));
            h[e.dest].push_back(Edge(e.dest, e.src, e.weight));
        }
        else {
            next_diff = std::min(next_diff,
                                 e.weight - dfs(h, Edge(-1, e.src, 0), e.dest));
        }
    }

    std::cout << tree_weight << " " << (tree_weight + next_diff) << std::endl;
}





int main() {
    int nCases;
    std::cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {

        int nNodes, nEdges;
        std::cin >> nNodes >> nEdges;

        Graph g(nNodes);

        for(int i = 0; i < nEdges; i++) {
            int a, b;
            int c;
            std::cin >> a >> b >> c;
            a--; b--;
            g[a].push_back(Edge(a, b, c));
            g[b].push_back(Edge(b, a, c));
        }

        kruskal(g);

    }

    return 0;
}

