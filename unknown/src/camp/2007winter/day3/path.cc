#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

struct Edge {
    int from, to;
    int weight;
    int cap;
    int flow;
};

typedef vector<Edge> Edges;

const int INF = 0x3fffffff;

int n, m;


int next_flow(Edges& edges, int s, int t) {
    vector<int> dists(n, INF);
    vector<int> trace(n, -1);
    dists[s] = 0;

    REP(r, n-1) {
        REP(i, 2*m) {
            Edge& e = edges[i];
            if (e.flow < e.cap && dists[e.from] + e.weight < dists[e.to]) {
                dists[e.to] = dists[e.from] + e.weight;
                trace[e.to] = i;
            }
        }
    }

    if (trace[t] < 0)
        return -1;

    int res = 0;
    for(int x = t; x != s; x = edges[trace[x]].from) {
        int id1 = trace[x];
        int id2 = id1^1;
        res += edges[id1].weight;
        edges[id1].flow++;
        edges[id2].flow--;
    }

    return res;
}

int solve(Edges& edges, int s, int t) {
    int r1 = next_flow(edges, s, t);
    if (r1 < 0)
        return -1;
    int r2 = next_flow(edges, s, t);
    if (r2 < 0)
        return -1;
    return r1+r2;
}

int main() {

    freopen("path.in", "r", stdin);

    int iCase = 0;
    while(cin >> n >> m && !(n == 0 && m == 0)) {

        Edges edges;
        REP(i, m) {
            int a, b, c;
            cin >> a >> b >> c;
            edges.push_back((Edge){a, b, c, 1, 0});
            edges.push_back((Edge){b, a, -c, 0, 0});
        }

        cout << "Instance #" << ++iCase << ": ";
        int ret = solve(edges, 0, n-1);
        if (ret < 0)
            cout << "Not possible" << endl;
        else
            cout << ret << endl;
    }

    return 0;
}
