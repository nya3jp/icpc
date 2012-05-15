/*
 * グラフのデータ表現とヘルパ関数
 * rev.02
 */

#include <vector>


typedef double Weight;

struct Edge {
    int src, dest;
    Weight weight;

    Edge() {
    }
    Edge(int src, int dest, Weight weight = 0) :
        src(src), dest(dest), weight(weight) {
    }
    friend bool operator<(const Edge& a, const Edge& b) {
        return (a.weight < b.weight);
    }
    friend bool operator>(const Edge& a, const Edge& b) {
        return (a.weight > b.weight);
    }
};

typedef std::vector<Edge> Edges;
typedef std::vector<Edges> Graph;

inline void insert_edge(Graph& g, int a, int b, Weight w = 0) {
    g[a].push_back(Edge(a, b, w));
}

inline bool has_edge(const Graph& g, int a, int b) {
    const Edges& edges = g[a];
    for(int i = 0; i < (int)edges.size(); i++)
        if (edges[i].dest == b)
            return true;
    return false;
}


#include <vector>
#include <queue>
#include <utility>

enum PrimConst { TERMINAL = -1 };


std::pair<Weight, Edges> prim(const Graph& g)
{
    const int n = g.size();

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > q;
    std::vector<bool> visited(n, false);
    Edges tree;
    Weight tree_weight = 0;

    q.push(Edge(TERMINAL, 0, 0));

    while(!q.empty()) {
        Edge e = q.top();
        q.pop();

        if (visited[e.dest])
            continue;

        visited[e.dest] = true;
        if (e.src != TERMINAL) {
            tree.push_back(e);
            tree_weight += e.weight;
        }

        const Edges& edges = g[e.dest];
        for(int i = 0; i < (int)edges.size(); i++) {
            const Edge& f = edges[i];
            if (!visited[f.dest])
                q.push(f);
        }
    }

    return std::make_pair(tree_weight, tree);
}



#include <iostream>
#include <complex>
#include <cmath>
#include <cstdio>

using namespace std;

typedef complex<double> P;

int main() {
    int n;
    cin >> n;
    for(int ic=0; ic<n; ic++) {
        int m;
        cin >> m;
        vector<P> v;
        for(int j=0; j<m; j++) {
            double x, y;
            cin >> x >> y;
            v.push_back(P(x, y));
        }
        Graph g(m);
        for(int i=0; i<m; i++) {
            for(int j=i+1; j<m; j++) {
                double w = abs(v[i] - v[j]);
                insert_edge(g, i, j, w);
                insert_edge(g, j, i, w);
            }
        }
        double w = prim(g).first;
        printf("%s%.2f\n", ic>0?"\n":"", w);
    }
    return 0;
}


