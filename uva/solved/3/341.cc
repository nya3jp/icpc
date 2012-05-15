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


typedef Matrix<Weight> AdjacencyMatrix;

const Weight WEIGHT_INFTY = 0x7fffffff;//std::numeric_limits<Weight>::max();


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
 * Dijkstra‚ÌÅ’ZŒo˜H’TõƒAƒ‹ƒSƒŠƒYƒ€
 * rev.02
 *
 * REQUIRES "graph-basic"
 * [NOT VERIFIED]
 *
 */

#include <algorithm>
#include <vector>
#include <queue>

//#include "graph-basic.cc"


// ’è”
enum DijkstraConst { UNSEEN = -2, TERMINAL = -1 };


/*
 * Dijkstra‚ÌƒAƒ‹ƒSƒŠƒYƒ€‚É‚æ‚Á‚Ästart‚©‚çgoal‚Ü‚Å‚ÌÅ’ZŒo˜H’·‚ğ
 * ŒvZ‚·‚é
 * start‚©‚çgoal‚ÉŠ‚é“¹‚ª–³‚¢‚Æ‚«‚Í•‰‚Ì”‚ğ•Ô‚·
 * goal‚É-1‚ğw’è‚·‚é‚Æ‘S“_‚É‘Î‚·‚éÅ’ZŒo˜H‚ğ‹‚ß‚é
 */
Weight dijkstra(const Graph& g,
                int start,
                int goal,
                std::vector<int>& previous)
{
    const int n = g.size();

    previous.assign(n, UNSEEN);

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > q;
    q.push(Edge(TERMINAL, start, 0));

    while(! q.empty()) {
        Edge edge = q.top();
        q.pop();

        if (previous[edge.dest] != UNSEEN)
            continue;

        previous[edge.dest] = edge.src;

        if (edge.dest == goal)
            return edge.weight;

        const Edges& edges = g[edge.dest];
        for(int i = 0; i < (int)edges.size(); i++) {
            if (previous[edges[i].dest] == UNSEEN) {
                q.push(Edge(edge.dest,
                            edges[i].dest,
                            edge.weight + edges[i].weight));
            }
        }
    }

    return -1;
}


/*
 * dijkstra()‚ÌÀsŒ‹‰Ê‚©‚çÅ’ZŒo˜H‚ğ\’z‚·‚é
 */
std::vector<int> dijkstra_build_route(const std::vector<int>& previous,
                                      int goal)
{
    if (previous[goal] == UNSEEN)
        return std::vector<int>();

    std::vector<int> route;
    for(int i = goal; i != TERMINAL; i = previous[i])
        route.push_back(i);
    std::reverse(route.begin(), route.end());
    return route;
}


#include <iostream>

using namespace std;


int main() {
    int iCase = 0;
    int n;
    while(cin >> n && n != 0) {
        Graph g(n);
        for(int i = 0; i < n; i++) {
            int m;
            cin >> m;
            for(int j = 0; j < m; j++) {
                int k, w;
                cin >> k >> w;
                k--;
                insert_edge(g, i, k, w);
            }
        }
        int a, b;
        cin >> a >> b;
        a--; b--;
        vector<int> trace;
        int w = dijkstra(g, a, b, trace);
        vector<int> route = dijkstra_build_route(trace, b);
        cout << "Case " << ++iCase << ": Path =";
        for(int i=0; i<(int)route.size(); i++)
            cout << ' ' << route[i]+1;
        cout << "; " << w << " second delay" << endl;
    }
    return 0;
}


