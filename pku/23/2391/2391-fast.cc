#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())


#define N 402

const long long INF = numeric_limits<long long>::max() / 2;

namespace dinic {

    int n, s, t;
    int cap[N][N], flow[N][N];
    int levels[N];
    bool finished[N];

#define residue(i,j) (cap[i][j] - flow[i][j])

    void levelize() {
        memset(levels, -1, sizeof(levels));
        queue<int> q;
        levels[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int here = q.front();
            q.pop();
            REP(there, n) {
                if (levels[there] < 0 && residue(here, there) > 0) {
                    levels[there] = levels[here] + 1;
                    q.push(there);
                }
            }
        }
    }
    int augment(int here, int curflow) {
        if (curflow == 0)
            return 0;
        if (here == t) {
            return curflow;
        }
        if (!finished[here]) {
            finished[here] = true;
            REP(there, n) {
                if (levels[there] > levels[here]) {
                    int f = augment(there, min(curflow, residue(here, there)));
                    if (f > 0) {
                        flow[here][there] += f;
                        flow[there][here] -= f;
                        finished[here] = false;
                        return f;
                    }
                }
            }
        }
        return 0;
    }
    int maxflow() {
        memset(flow, 0, sizeof(flow));
        int total = 0;
        bool cont;
        do {
            levelize();
            memset(finished, 0, sizeof(finished));
            cont = false;
            for(;;) {
                int f = augment(s, numeric_limits<int>::max());
                if (f == 0)
                    break;
                total += f;
                cont = true;
            }
        } while(cont);
        return total;
    }
}

int ins[N], outs[N];
long long adj[N][N];
int nNodes, nEdges;

bool solve(long long thres) {
    dinic::n = nNodes*2+2;
    dinic::s = nNodes*2+0;
    dinic::t = nNodes*2+1;
    memset(dinic::cap, 0, sizeof(dinic::cap));
    REP(i, nNodes) REP(j, nNodes)
        if (adj[i][j] <= thres)
            dinic::cap[i][nNodes+j] = 1000;
    REP(i, nNodes)
        dinic::cap[dinic::s][i] = outs[i];
    REP(i, nNodes)
        dinic::cap[i+nNodes][dinic::t] = ins[i];
    int total = 0;
    REP(i, nNodes)
        total += outs[i];

    return (dinic::maxflow() == total);
}

int main() {

    cin >> nNodes >> nEdges;
    REP(i, nNodes)
        scanf("%d%d", &outs[i], &ins[i]);

    REP(i, nNodes) REP(j, nNodes)
        adj[i][j] = (i == j ? 0 : INF);

    REP(i, nEdges) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        adj[a][b] <?= c;
        adj[b][a] <?= c;
    }

    REP(j, nNodes) REP(i, nNodes) REP(k, nNodes)
        adj[i][k] <?= adj[i][j] + adj[j][k];

    if (!solve(INF-1)) {
        cout << "-1" << endl;
    }
    else {
        long long lower = 0, upper = 1;
        while(!solve(upper)) {
            lower = upper;
            upper *= 2;
        }
        while(upper-lower > 0) {
            long long middle = (lower+upper)/2;
            if (solve(middle))
                upper = middle;
            else
                lower = middle+1;
        }
        cout << lower << endl;
    }

    return 0;
}
