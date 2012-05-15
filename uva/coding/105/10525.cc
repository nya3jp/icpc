#include <vector>
//#include <limits>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <complex>
#include <utility>

using namespace std;


typedef complex<int> Weight;

namespace std {
    bool operator<(const Weight& a, const Weight& b) {
        return (make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag()));
    }
    bool operator>(const Weight& a, const Weight& b) {
        return (make_pair(a.real(), a.imag()) > make_pair(b.real(), b.imag()));
    }
}

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

const Weight WEIGHT_INFTY = 1.0e100; //std::numeric_limits<Weight>::max();



/*
 * Dijkstra‚ÌƒAƒ‹ƒSƒŠƒYƒ€‚É‚æ‚Á‚Ästart‚©‚çgoal‚Ü‚Å‚ÌÅ’ZŒo˜H’·‚ğ
 * ŒvZ‚·‚é
 * start‚©‚çgoal‚ÉŠ‚é“¹‚ª–³‚¢‚Æ‚«‚Í•‰‚Ì”‚ğ•Ô‚·
 * goal‚É-1‚ğw’è‚·‚é‚Æ‘S“_‚É‘Î‚·‚éÅ’ZŒo˜H‚ğ‹‚ß‚é
 */
Weight dijkstra(Graph& g, int start, int goal, vector<int>& trace)
{
    const int n = g.size();

    trace.assign(n, -2);  // UNSEEN

    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    q.push(Edge(-1, start, 0)); // TERMINAL

    while(! q.empty()) {
        Edge e = q.top();
        q.pop();

        if (trace[e.dest] >= 0)
            continue;

        trace[e.dest] = e.src;

        if (e.dest == goal)
            return e.weight;

        Edges& edges = g[e.dest];
        for(int i = 0; i < (int)edges.size(); i++) {
            Edge& f = edges[i];
            if (trace[f.dest] < 0) {
                q.push(Edge(f.src,
                            f.dest,
                            e.weight + f.weight));
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
    if (trace[goal] < 0)
        return vector<int>();

    vector<int> route;
    for(int i = goal; i >= 0; i = trace[i])
        route.push_back(i);
    reverse(route.begin(), route.end());
    return route;
}

#include <iostream>


void solve() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for(int i = 0; i < m; i++) {
        int a, b, t, l;
        cin >> a >> b >> t >> l;
        a--; b--;
        g[a].push_back(Edge(a, b, Weight(t, l)));
        g[b].push_back(Edge(b, a, Weight(t, l)));
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        vector<int> trace;
        Weight w = dijkstra(g, a, b, trace);
        if (w.real() < 0)
            cout << "No Path." << endl;
        else
            cout << "Distance and time to reach destination is "
                 << w.imag() << " & " << w.real() << "." << endl;
    }
    cout << endl;
}


int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}

