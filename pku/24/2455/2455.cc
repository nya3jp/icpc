#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

template<class T>
inline T mymax(const T& a, const T& b) {
    if (a > b)
        return a;
    return b;
}

struct Edge {
    int src, dest, weight;
    Edge* rev;
};

Edge* newEdge(int src, int dest, int weight) {
    Edge* p = new Edge();
    p->src = src;
    p->dest = dest;
    p->weight = weight;
    p->rev = new Edge();
    p->rev->src = dest;
    p->rev->dest = src;
    p->rev->weight = weight;
    p->rev->rev = p;
    return p;
}

typedef vector<Edge*> Edges;
typedef vector<Edges> Graph;

int augment(Graph& g) {
    int n = g.size();
    int start = 0, goal = n-1;

    typedef pair<int, Edge*> node;
    priority_queue<node, vector<node>, greater<node> > q;
    Edge* terminal = newEdge(-1, start, 0);
    q.push(make_pair(0, terminal));

    Edges trace(n, (Edge*)0);

    int flow;

    while(!q.empty()) {
        int cost = q.top().first;
        Edge* back = q.top().second;
        q.pop();

        int here = back->dest;

        if (!trace[here]) {
            trace[here] = back;
            //printf("flow to %d: %d\n", here, cost);
            if (here == goal) {
                flow = cost;
                break;
            }
            Edges& v = g[here];
            {REP(i, v.size()) {
                Edge* edge = v[i];
                int there = edge->dest;
                if (!trace[there])
                    q.push(make_pair(mymax(cost, edge->weight), edge));
                }}
        }
    }

    {
    for(int here = goal; here != start; ) {
        Edge* edge = trace[here];
        int there = edge->src;
        edge->weight = 0x10000000;
        edge->rev->weight = 0;
        here = there;
    }
    }

    return flow;
}


int main() {

    int n, m, nPaths;
    //cin >> n >> m >> nPaths;
    scanf("%d%d%d", &n, &m, &nPaths);

    Graph g(n);
    {REP(i, m) {
        int a, b, w;
        //cin >> a >> b >> w;
        scanf("%d%d%d", &a, &b, &w);
        a--; b--;
        Edge* e = newEdge(a, b, w);
        g[a].push_back(e);
        g[b].push_back(e->rev);
        }}

    int res = 0;
    {REP(i, nPaths)
        res = augment(g);
    }
    cout << res << endl;

    return 0;
}
