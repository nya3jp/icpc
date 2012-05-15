/*
 * ƒOƒ‰ƒt‚Ìƒf[ƒ^•\Œ»‚Æƒwƒ‹ƒpŠÖ”
 * rev.02
 */

#include <vector>
//#include <limits>


typedef int Weight;

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

const Weight WEIGHT_INFTY = 0x7fffffff;//std::numeric_limits<Weight>::max();

typedef Matrix<Weight> AdjacencyMatrix;
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

/*
 * Warshall-Floyd‚ÌƒAƒ‹ƒSƒŠƒYƒ€
 * rev.01
 *
 * REQUIRES "graph-basic"
 * [NOT VERIFIED]
 *
 */

#include <vector>

//#include "graph-basic.cc"


enum WarshallFloydConst { DIRECT = -1 };

/*
 * Warshall-Floyd‚ÌƒAƒ‹ƒSƒŠƒYƒ€‚ÅŠe“_ŠÔ‚ÌÅ’ZŒo˜H’·‚ğ‹‚ß‚é
 * ÀsŒãAinternodes‚ğwarshall_floyd_build_route()‚É“n‚·‚Æ
 * Å’ZŒo˜H‚ğ\’z‚Å‚«‚é
 */
void warshall_floyd(AdjacencyMatrix& adj, Matrix<int>& internodes)
{
    const int n = adj.size();

    internodes.assign(n, n, DIRECT);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (adj[j][i] != WEIGHT_INFTY)
                for(int k = 0; k < n; k++)
                    if (adj[i][k] != WEIGHT_INFTY)
                        if (adj[j][k] > adj[j][i] + adj[i][k])
                            adj[j][k] = adj[j][i] + adj[i][k], internodes[j][k] = i;
}

/*
 * warshall_floyd()‚Ìinternodes‚©‚çÅ’ZŒo˜H‚ğ\’z‚·‚é
 */
void warshall_floyd_build_route(std::vector<int>& route,
                                const Matrix<int>& internodes,
                                int src,
                                int dest,
                                bool rec = false)
{
    if (!rec)
        route.clear();
    int internode = internodes[src][dest];
    if (internode == DIRECT) {
        route.push_back(src);
    }
    else {
        warshall_floyd_build_route(route, internodes, src, internode, true);
        warshall_floyd_build_route(route, internodes, internode, dest, true);
    }
    if (!rec)
        route.push_back(dest);
}

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdio>

using namespace std;



int main() {
    cout << "SHIPPING ROUTES OUTPUT" << endl << endl;

    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        int nNodes, nLinks, nShips;
        cin >> nNodes >> nLinks >> nShips;
        Graph g(nNodes);

        map<string,int> names;
        for(int i = 0; i < nNodes; i++) {
            string s;
            cin >> s;
            names[s] = i;
        }

        for(int i = 0; i < nLinks; i++) {
            string s, t;
            cin >> s >> t;
            int a, b;
            a = names[s];
            b = names[t];
            insert_edge(g, a, b, 1);
            insert_edge(g, b, a, 1);
        }

        AdjacencyMatrix adj(nNodes, nNodes);
        make_adjacency_matrix(adj, g);
        Matrix<int> trace(nNodes, nNodes);

        warshall_floyd(adj, trace);

        printf("DATA SET %2d\n\n", iCase+1);
        //cout << "DATA SET " << iCase+1 << endl << endl;

        for(int i = 0; i < nShips; i++) {
            int size;
            string s, t;
            cin >> size >> s >> t;
            int a, b;
            a = names[s];
            b = names[t];
            if (adj[a][b] == WEIGHT_INFTY) {
                cout << "NO SHIPMENT POSSIBLE" << endl;
            }
            else {
                cout << "$" << (size*adj[a][b]*100) << endl;
            }
        }
        cout << endl;
    }
    cout << "END OF OUTPUT" << endl;
    return 0;
}
