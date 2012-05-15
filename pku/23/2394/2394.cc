#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

struct CIN {
    CIN& operator>>(int& x) {
        scanf("%d", &x);
        return *this;
    }
} cin;

struct Edge {
    int src, dest, weight;
};
bool operator>(const Edge& a, const Edge& b) {
    return (a.weight > b.weight);
}
const int INF = 0x7fffffff;

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

int main() {

    int n, m, nCows, limit;
    cin >> n >> m >> nCows >> limit;

    Graph g(n);
    REP(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back((Edge){a, b, c});
        g[b].push_back((Edge){b, a, c});
    }

    vector<int> cows(nCows);
    REP(i, nCows) {
        int a;
        cin >> a;
        a--;
        cows[i] = a;
    }

    vector<int> cost(n, INF);
    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    q.push((Edge){-2, 0, 0});
    while(!q.empty()) {
        Edge e = q.top();
        q.pop();
        if (cost[e.dest] != INF)
            continue;
        cost[e.dest] = e.weight;
        FOR(it, g[e.dest])
            q.push((Edge){it->src, it->dest, it->weight + e.weight});
    }

    vector<int> guilts;
    REP(i, nCows)
        if (cost[cows[i]] <= limit)
            guilts.push_back(i);

    printf("%d\n", guilts.size());
    REP(i, guilts.size())
        printf("%d\n", guilts[i]+1);

    return 0;
}
