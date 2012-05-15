#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 1000

struct Edge {
    int a, b, c;
    int dp[N];

    Edge(int a=-1, int b=-1, int c=-1) : a(a), b(b), c(c) {
        REP(i, N)
            dp[i] = -1;
    }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

int read_int() {
    int x;
    scanf("%d", &x);
    return x;
}

int n;
int costs[N];
int capacities[N];

Graph g;

int go(Edge& e, int m) {
    assert(e.dp[m] < 0);
    int here = e.b;
    Edges& v = g[here];

    REP(i, v.size()) {
        Edge& f = v[i];
        if (
    }

}

int solve() {

    Edges& v = g[0];
    REP(i, v.size()) REP(m, n-1)
        go(v[i], m);

}

int main() {

    int nCases = read_int();
    REP(iCase, nCases) {

        n = read_int();

        g.assign(n, Edges());

        REP(i, n)
            costs[i] = read_int();
        REP(i, n)
            capacities[i] = read_int();

        REP(i, n-1) {
            int a, b, c;
            a = read_int()-1;
            b = read_int()-1;
            c = read_int();

            g[a].push_back(Edge(a, b, c));
            g[b].push_back(Edge(b, a, c));
        }

        printf("%d\n", solve());

    }

    return 0;
}



