#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


struct Edge {
    int src, dest;
    int weight;

    Edge() {
    }
    Edge(int src, int dest, int weight = 0) :
        src(src), dest(dest), weight(weight) {
    }
    friend bool operator>(const Edge& a, const Edge& b) {
        return (a.weight > b.weight);
    }
};

typedef std::vector<Edge> Edges;
typedef std::vector<Edges> Graph;

inline void insert_edge(Graph& g, int a, int b, int w = 0) {
    g[a].push_back(Edge(a, b, w));
}

inline bool has_edge(const Graph& g, int a, int b) {
    const Edges& edges = g[a];
    for(int i = 0; i < (int)edges.size(); i++)
        if (edges[i].dest == b)
            return true;
    return false;
}

struct UnionFind {
    std::vector<int> data;
    const int n;

    UnionFind(int n) : data(n, -1), n(n) {
    }
    bool link(int a, int b) {
        int ra = find_root(a);
        int rb = find_root(b);
        if (ra != rb) {
            if (data[rb] < data[ra])
                std::swap(ra, rb);
            data[ra] += data[rb];
            data[rb] = ra;
        }
        return (ra != rb);
    }
    bool check(int a, int b) {
        return (find_root(a) == find_root(b));
    }

    int find_root(int a) {
        return ((data[a] < 0) ? a : (data[a] = find_root(data[a])));
    }
};



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


Edges kruskal2(const Graph& g)
{
    const int n = g.size();

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > q;
    UnionFind uf(n);

    for(int i = 0; i < n; i++) {
        const Edges& edges = g[i];
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
            insert_edge(h, e.src, e.dest, e.weight);
            insert_edge(h, e.dest, e.src, e.weight);
        }
        else {
            next_diff = std::min(next_diff,
                                 e.weight - dfs(h, Edge(-1, e.src, 0), e.dest));
        }
    }

    std::cout << tree_weight << " " << (tree_weight + next_diff) << std::endl;

    return tree;
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
            insert_edge(g, a, b, c);
            insert_edge(g, b, a, c);
        }

        kruskal2(g);

    }

    return 0;
}

