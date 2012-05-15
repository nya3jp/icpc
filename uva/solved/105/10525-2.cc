#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Cost {
    int time, len;
    Cost(int time, int len)
        : time(time), len(len) {
    }
    Cost() {
    }
};
bool operator>(const Cost& a, const Cost& b) {
    return (make_pair(a.time, a.len) > make_pair(b.time, b.len));
}

struct Edge {
    int src, dest;
    Cost cost;
    Edge(int src, int dest, Cost cost)
        : src(src), dest(dest), cost(cost) {
    }
    Edge() {
    }
};
bool operator>(const Edge& a, const Edge& b) {
    return (a.cost > b.cost);
}

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;


Cost dijkstra(Graph& g, int start, int goal) {
    int n = g.size();
    vector<bool> trace(n, false);
    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    q.push(Edge(-1, start, Cost(0, 0)));
    while(!q.empty()) {
        Edge c = q.top();
        q.pop();
        if (!trace[c.dest]) {
            trace[c.dest] = true;
            if (c.dest == goal)
                return c.cost;
            Edges& edges = g[c.dest];
            for(int i = 0; i < (int)edges.size(); i++) {
                Edge& e = edges[i];
                if (!trace[e.dest]) {
                    q.push(Edge(e.src, e.dest, Cost(c.cost.time+e.cost.time, c.cost.len+e.cost.len)));
                }
            }
        }
    }
    return Cost(-1, -1);
}

int main() {
    int nCases;
    cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {
        int n, m;
        cin >> n >> m;
        Graph g(n);
        for(int i = 0; i < m; i++) {
            int a, b, time, len;
            cin >> a >> b >> time >> len;
            a--; b--;
            g[a].push_back(Edge(a, b, Cost(time, len)));
            g[b].push_back(Edge(b, a, Cost(time, len)));
        }

        if (iCase > 0)
            cout << endl;
        int nQueries;
        cin >> nQueries;
        for(int iQuery = 0; iQuery < nQueries; iQuery++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            Cost c = dijkstra(g, a, b);
            if (c.time < 0) {
                cout << "No Path." << endl;
            }
            else {
                cout << "Distance and time to reach destination is "
                     << c.len << " & " << c.time << "." << endl;
            }
        }
    }
    return 0;
}
