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

#define N (100+2)

int n, m;
int cap[N][N];
int flow[N][N];

#define residue(i,j) (cap[i][j]-flow[i][j])

int maxflow(int src, int sink) {

    int total = 0;

    for(;;) {

        int trace[N];
        REP(i, n)
            trace[i] = -1;

        queue<int> q;
        q.push(src);
        trace[src] = src;

        while(!q.empty()) {
            int here = q.front();
            q.pop();
            if (here == sink)
                break;
            REP(there, n) {
                if (residue(here, there) > 0 && trace[there] < 0) {
                    trace[there] = here;
                    q.push(there);
                }
            }
        }

        if (trace[sink] < 0)
            break;

        int f = numeric_limits<int>::max();
        for(int t = sink; t != src; t = trace[t]) {
            f <?= residue(trace[t], t);
        }
        for(int t = sink; t != src; t = trace[t]) {
            flow[trace[t]][t] += f;
            flow[t][trace[t]] -= f;
        }

        total += f;

    }

    return total;
}

int main() {

    for(;;) {
        int nProducers, nConsumers;
        if (scanf("%d%d%d%d", &n, &nProducers, &nConsumers, &m) != 4)
            break;

        int src = n, sink = n+1;
        n += 2;

        REP(i, n) REP(j, n)
            cap[i][j] = flow[i][j] = 0;

        REP(i, m) {
            int a, b, c;
            scanf(" (%d ,%d )%d", &a, &b, &c);
            cap[a][b] = c;
        }

        REP(i, nProducers) {
            int a, c;
            scanf(" (%d )%d", &a, &c);
            cap[src][a] = c;
        }
        REP(i, nConsumers) {
            int a, c;
            scanf(" (%d )%d", &a, &c);
            cap[a][sink] = c;
        }
        int res = maxflow(src, sink);
        printf("%d\n", res);

    }

    return 0;
}

