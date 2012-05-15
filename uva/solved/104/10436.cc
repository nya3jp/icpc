#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cstdio>
#include <functional>
#include <queue>

using namespace std;

struct Edge {
    int src, dest;
    double cost;
    Edge(int src=0, int dest=0, double cost=0)
        : src(src), dest(dest), cost(cost) {
    }
    friend bool operator>(const Edge& a, const Edge& b) {
        return (a.cost > b.cost);
    }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;


double dijkstra(Graph& g, int src, int dest, vector<double>& tax, vector<int>& trace) {
    int n = g.size();
    trace.assign(n, -2);

    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    q.push(Edge(-1, src, tax[src]));

    while(!q.empty()) {
        Edge e = q.top();
        q.pop();

        if (trace[e.dest] != -2)
            continue;

        trace[e.dest] = e.src;

        if (e.dest == dest)
            return e.cost;

        Edges& edges = g[e.dest];
        for(int i = 0; i < (int)edges.size(); i++) {
            Edge& f = edges[i];
            if (trace[f.dest] == -2) {
                q.push(Edge(f.src, f.dest,
                            e.cost + f.cost + tax[f.dest]));
            }
        }

    }

    return -1;
}


void solve() {


    int n;
    cin >> n;

    map<string,int> n2i;
    vector<string> i2n(n);
    vector<double> tax(n);
    for(int i = 0; i < n; i++) {
        cin >> i2n[i] >> tax[i];
        n2i[i2n[i]] = i;
    }

    Graph g(n);

    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        string s, t;
        double len;
        cin >> s >> t >> len;
        int a = n2i[s];
        int b = n2i[t];
        double cost = len * 2;
        g[a].push_back(Edge(a, b, cost));
        g[b].push_back(Edge(b, a, cost));
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        cout << "Query #" << (i+1) << endl;
        string s, t;
        int p;
        cin >> s >> t >> p;
        int src = n2i[s];
        int dest = n2i[t];
        vector<int> trace;
        double cost = dijkstra(g, src, dest, tax, trace);
        double fare = cost * 1.1 / p;
        vector<int> route;
        for(int j = dest; j >= 0; j = trace[j])
            route.push_back(j);
        reverse(route.begin(), route.end());
        for(int j = 0; j < (int)route.size(); j++) {
            if (j > 0)
                cout << ' ';
            cout << i2n[route[j]];
        }
        cout << endl;
        cout << "Each passenger has to pay : ";
        printf("%.2f taka\n", fare);
    }

}


int main() {
    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        if (iCase > 0)
            cout << endl;
        cout << "Map #" << (iCase+1) << endl;
        solve();
    }
    return 0;
}





