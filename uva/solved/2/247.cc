/**
 * @file
 * グラフ:強連結成分分解
 *
 * @version
 * rev.01
 *
 * @note
 * 参考: IHI LIBRARY
 */

#include <vector>
#include <algorithm>

//#include "graph-basic.cc"


/*
 * グラフのデータ表現とヘルパ関数
 * rev.02
 */

#include <vector>
//#include <limits>


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

template<class T>
struct Matrix : public std::vector< std::vector<T> >
{
    Matrix(int n, int m, const T& value = T()) {
        assign(n, m, value);
    }
    void assign(int n, int m, const T& value = T()) {
        std::vector< std::vector<T> >::assign(n, std::vector<T>(m, value));
    }
};


typedef Matrix<Weight> AdjacencyMatrix;

//const Weight WEIGHT_INFTY = std::numeric_limits<Weight>::max();


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

/*
void make_adjacency_matrix(AdjacencyMatrix& adj,
                           const Graph& g)
{
    const int n = g.size();

    adj.assign(n, n, WEIGHT_INFTY);
    for(int i = 0; i < n; i++) {
        const Edges& edges = g[i];
        for(int j = 0; j < (int)edges.size(); j++) {
            const Edge& e = edges[j];
            adj[e.src][e.dest] = e.weight;
        }
    }
}
*/



/*
 * 強連結成分分解に用いるDFS
 */
void strongly_connected_components_traverse(const Graph& g,
                                            int iNode,
                                            std::vector<int>& order,
                                            std::vector<bool>& visited)
{
    if (!visited[iNode]) {
        visited[iNode] = true;
        const Edges& edges = g[iNode];
        for(int i = 0; i < (int)edges.size(); i++) {
            strongly_connected_components_traverse(g, edges[i].dest, order, visited);
        }
        order.push_back(iNode);
    }
}


/*
 * 強連結成分分解
 */
std::vector< std::vector<int> >
strongly_connected_components(const Graph& g)
{
    const int n = g.size();

    std::vector<bool> visited(n, false);

    std::vector<int> order;
    for(int i = 0; i < n; i++) {
        strongly_connected_components_traverse(g, i, order, visited);
    }

    std::reverse(order.begin(), order.end());

    Graph gr(n);
    for(int i = 0; i < n; i++) {
        const Edges& edges = g[i];
        for(int j = 0; j < (int)edges.size(); j++) {
            const Edge& e = edges[j];
            insert_edge(gr, e.dest, e.src);
        }
    }

    std::vector< std::vector<int> > components;
    visited.assign(n, false);
    for(int i = 0; i < n; i++) {
        if (!visited[order[i]]) {
            components.push_back(std::vector<int>());
            strongly_connected_components_traverse(gr, order[i], components.back(), visited);
        }
    }

    return components;
}



#include <iostream>
#include <map>
#include <string>

using namespace std;


int main() {
    int n, m;
    int iCase = 0;
    while(cin >> n >> m && !(n == 0 && m == 0)) {
        Graph g(n);
        map<string, int> ids;
        vector<string> names;
        for(int i = 0; i < m; i++) {
            string s, t;
            cin >> s >> t;
            if (ids.find(s) == ids.end()) {
                ids.insert(make_pair(s, names.size()));
                names.push_back(s);
            }
            if (ids.find(t) == ids.end()) {
                ids.insert(make_pair(t, names.size()));
                names.push_back(t);
            }
            int a = ids[s];
            int b = ids[t];
            if (!has_edge(g, a, b))
                insert_edge(g, a, b);
        }
        if (iCase > 0)
            cout << endl;
        cout << "Calling circles for data set " << iCase+1 << ":" << endl;
        vector< vector<int> > st = strongly_connected_components(g);
        for(int i = 0; i < (int)st.size(); i++) {
            vector<int>& stt = st[i];
            for(int j = 0; j < (int)stt.size(); j++) {
                cout << names[stt[j]];
                if (j < (int)stt.size()-1)
                    cout << ", ";
            }
            cout << endl;
        }
        iCase++;
    }
    return 0;
}

