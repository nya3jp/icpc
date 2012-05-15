#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <queue>
#include <utility>

using namespace std;

namespace std {
    template<class T>
    bool operator<(const vector<T>& a, const vector<T>& b) {
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }
    template<class T>
    bool operator>(const vector<T>& a, const vector<T>& b) {
        return (b < a);
    }
}

typedef vector<int> Route;
typedef vector<int> Edges;
typedef vector<Edges> Graph;

void dijkstra(const Graph& g, int s, vector<Route>& trace) {
    const int n = g.size();

    trace.assign(n, Route());

    priority_queue<Route, vector<Route>, greater<Route> > q;
    q.push(Route(1, s));

    while(!q.empty()) {
        Route r = q.top();
        q.pop();
        int a = r.back();
        if (trace[a].empty()) {
            trace[a] = r;
            const Edges& e = g[a];
            for(int i = 0; i < (int)e.size(); i++) {
                int b = e[i];
                if (trace[b].empty()) {
                    r.push_back(b);
                    q.push(r);
                    r.pop_back();
                }
            }
        }
    }
}


bool search(const Graph& g, int s, int t, int a, vector<bool>& trace) {
    if (trace[a])
        return false;

    trace[a] = true;
    if (a == t)
        return true;

    const Edges& edges = g[a];
    for(int i = 0; i < (int)edges.size(); i++) {
        int b = edges[i];
        if (!(a == s && b == t)) {
            if (search(g, s, t, b, trace))
                return true;
        }        
    }
    return false;
}


void makeLoopGraph(Graph& g, Graph& l) {
    const int n = g.size();

    l.assign(n, Edges());

    for(int a = 0; a < n; a++) {
        Edges& edges = g[a];
        for(int i = 0; i < (int)edges.size(); i++) {
            int b = edges[i];
            vector<bool> trace(n, false);
            if (search(g, b, a, b, trace)) {
                l[a].push_back(b);
            }
        }
        sort(edges.begin(), edges.end());
    }
}




int main() {
    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        int n, m, s;
        cin >> n >> m >> s;
        Graph g(n);
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<Route> routes;
        dijkstra(g, s, routes);
        Graph l;
        makeLoopGraph(g, l);

        cout << "Case #" << (iCase+1) << ":" << endl;
        for(int i = 0; i < n; i++) {
            Route& r = routes[i];
            for(int j = 0; j < (int)r.size() - 1; j++) {
                int z = (j == 0 ? -1 : r[j-1]);
                int a = r[j];
                int b = r[j+1];
                for(int k = 0; k < (int)g[a].size(); k++) {
                    int c = g[a][k];
                    if (c < b && c != z && binary_search(l[a].begin(), l[a].end(), c)) {
                        r.clear();
                        break;
                    }
                }
            }

            if (!r.empty()) {
                cout << r[0];
                for(int j = 1; j < (int)r.size(); j++) {
                    cout << ' ' << r[j];
                }
                cout << endl;
            }
            else {
                cout << "No drive." << endl;
            }
        }
        cout << endl;
    }
    return 0;
}

