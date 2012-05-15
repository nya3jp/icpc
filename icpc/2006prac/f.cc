#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>


using namespace std;

struct Edge {
    int src, dest, w;
    Edge() {
    }
    Edge(int src, int dest, int w) : src(src), dest(dest), w(w) {
    }
};

const int INF = numeric_limits<int>::max() / 4;

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

bool operator>(const Edge& a, const Edge& b) {
    return a.w > b.w;
}

int dijkstra(Graph& g, int start, int goal) {
    const int n = g.size();

    vector<int> trace(n, -2);

    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    q.push(Edge(-1, start, 0));
    while(!q.empty()) {
        Edge e = q.top();
        q.pop();
        if (trace[e.dest] >= 0)
            continue;
        trace[e.dest] = e.src;
        if (e.dest == goal)
            return e.w;
        Edges& edges = g[e.dest];
        for(int i = 0; i < (int)edges.size(); i++) {
            Edge& f = edges[i];
            if (trace[f.dest] < 0) {
                q.push(Edge(f.src,
                            f.dest,
                            e.w + f.w));
            }
        }
    }

    return INF;
}

int main() {

    while(true) {
        int n, m, s, t1, t2;
        cin >> n >> m >> s >> t1 >> t2;
        if (n == 0 && m == 0 && s == 0 && t1 == 0 && t2 == 0)
            break;

        s--; t1--; t2--;

        Graph g(n);
        for(int i = 0; i < m; i++) {
            Edge e;
            cin >> e.src >> e.dest >> e.w;
            e.src--; e.dest--;
            g[e.src].push_back(e);
        }

        int ans = INF;
        for(int iCenter = 0; iCenter < n; iCenter++) {
            int d = dijkstra(g, s, iCenter) + dijkstra(g, iCenter, t1) + dijkstra(g, iCenter, t2);
            if (d < ans)
                ans = d;
        }

        cout << ans << endl;

    }

    return 0;
}

