#include <iostream>
#include <algorithm>

using namespace std;
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

/**
 * @file
 * ƒOƒ‰ƒt:Dijkstra‚ÌÅ’ZŒo˜H’TõƒAƒ‹ƒSƒŠƒYƒ€
 *
 * @version
 * rev.03
 */

#include <algorithm>
#include <vector>
#include <queue>
#include <functional>


using namespace std;


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
                vector<int>& trace)
{
    const int n = g.size();

    trace.assign(n, UNSEEN);

    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    q.push(Edge(TERMINAL, start, 0));

    while(! q.empty()) {
        Edge edge = q.top();
        q.pop();

        if (trace[edge.dest] != UNSEEN)
            continue;

        trace[edge.dest] = edge.src;

        if (edge.dest == goal)
            return edge.weight;

        const Edges& edges = g[edge.dest];
        for(int i = 0; i < (int)edges.size(); i++) {
            if (trace[edges[i].dest] == UNSEEN) {
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
vector<int> dijkstra_build_route(const vector<int>& trace,
                                 int goal)
{
    if (trace[goal] == UNSEEN)
        return vector<int>();

    vector<int> route;
    for(int i = goal; i != TERMINAL; i = trace[i])
        route.push_back(i);
    reverse(route.begin(), route.end());
    return route;
}







int main() {
    int nCases;
    cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        Graph g(n);
        for(int i = 0; i < m; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            insert_edge(g, a, b, w);
            insert_edge(g, b, a, w);
        }
        vector<int> trace;
        int dist = dijkstra(g, s, t, trace);
        cout << "Case #" << iCase+1 << ": ";
        if (dist < 0)
            cout << "unreachable"<< endl;
        else
            cout << dist << endl;
    }

    return 0;
}
