#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cstdio>
#include <cmath>
#include <complex>
#include <cctype>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

const int INF = 0x10000000;
int h, w;

typedef complex<int> P;
namespace std {
    bool operator<(const P& a, const P& b) {
        return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
    }
}

struct Edge {
    int src, dest, capacity;
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef map<int, map<int, int> > Flow;

void add_edge(Graph& g, int from, int to, int cap1, int cap2) {
    g[from].push_back((Edge){from, to, cap1});
    g[to].push_back((Edge){to, from, cap2});
}

int max_flow(Graph& g) {
    int n = g.size();

    vector< vector<int> > adj(n, vector<int>(n, 0));
    Flow f;

    REP(a, n) {
        Edges& v = g[a];
        REP(i, v.size()) {
            Edge& e = v[i];
            adj[e.src][e.dest] = e.capacity;
        }
    }

    int s = 0, t = 1;

#define residue(from,to) (adj[from][to] - f[from][to])

    int res = 0;
    for(;;) {
        vector<int> trace(n, -1);

        queue<int> q;
        q.push(s);
        trace[s] = s;
        while(!q.empty()) {
            int here = q.front();
            q.pop();
            if (here == t)
                break;
            Edges& v = g[here];
            REP(i, v.size()) {
                int there = v[i].dest;
                if (trace[there] < 0 && residue(here, there) > 0) {
                    q.push(there);
                    trace[there] = here;
                }
            }
        }

        if (trace[t] < 0)
            break;

        int flow = INF;
        for(int c = t; trace[c] != c; c = trace[c])
            flow <?= residue(trace[c], c);

        for(int c = t; trace[c] != c; c = trace[c]) {
            int from = trace[c];
            int to = c;
            f[from][to] += flow;
            f[to][from] = -f[from][to];
        }
        /*
        printf("go %d flow\n", flow);

        vector<int> route;
        reverse(ALLOF(route));
        printf("0");
        REP(i, route.size())
            printf(" -> %d", route[i]);
        printf("\n");
        for(int i = 2; i < n; i+=2) {
            printf("flow of %d: %d\n", i/2, f[i][i+1]);
        }
        */

        res += flow;
    }

    //printf("total flow = %d\n", res);

    return res;
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int hop;
        cin >> h >> hop;

        vector<string> field(h), lizard(h);
        REP(i, h)
            cin >> field[i];
        REP(i, h)
            cin >> lizard[i];

        w = field[0].size();

        int n = 2;
        map<int, map<int, int> > ids;

        int nLizards = 0;
        REP(i, h) REP(j, w) {
            if (field[i][j] != '0') {
                ids[i][j] = n;
                n += 2;
            }
            if (lizard[i][j] == 'L')
                nLizards++;
        }

        Graph g(n);

        REP(i, h) REP(j, w) {
            if (field[i][j] != '0') {
                int cap = (int)(field[i][j] - '0');
                add_edge(g, ids[i][j], ids[i][j]+1, cap, 0);
                if (lizard[i][j] == 'L')
                    add_edge(g, 0, ids[i][j], 1, 0);
                if (i+1 <= hop || h-i <= hop || j+1 <= hop || w-j <= hop) {
                    add_edge(g, ids[i][j]+1, 1, INF, 0);
                    //printf("(%d,%d) -> exit\n", i, j);
                }
                REP(ii, h) REP(jj, w) {
                    if (P(i,j) < P(ii,jj)) {
                        if (field[ii][jj] != '0') {
                            if ((ii-i)*(ii-i)+(jj-j)*(jj-j) <= hop*hop) {
                                add_edge(g, ids[i][j]+1, ids[ii][jj], INF, 0);
                                add_edge(g, ids[ii][jj]+1, ids[i][j], INF, 0);
                                //printf("(%d,%d) <-> (%d,%d)\n", i, j, ii, jj);
                            }
                        }
                    }
                }
            }
        }
        
        int res = nLizards - max_flow(g);

        printf("Case #%d: ", iCase+1);
        printf((res == 0 ? "no" : "%d"), res);
        printf(" lizard%s left behind.\n",
               (res < 2 ? " was" : "s were"));

    }

    return 0;
}
