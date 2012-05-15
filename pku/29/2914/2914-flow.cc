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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

#define N 500

typedef vector<int> Edges;
typedef vector<Edges> Graph;

Graph g;
int cap[N][N];
int flow[N][N];
int n;

#define residue(i,j) (cap[i][j]-flow[i][j])

int max_flow(int s, int t) {
    REP(i, n) REP(j, n)
        flow[i][j] = 0;

    int res = 0;

    for(;;) {

        queue<int> q;
        vector<int> trace(n, -1);
        q.push(s);
        trace[s] = s;
        while(!q.empty()) {
            int here = q.front();
            q.pop();
            //printf("> %d -> %d\n", trace[here], here);
            Edges& v = g[here];
            REP(i, v.size()) {
                int there = v[i];
                if (trace[there] < 0 && residue(here, there) > 0) {
                    trace[there] = here;
                    q.push(there);
                    if (there == t)
                        goto END_AUGMENT;
                }
            }
        }
        // no augmenting path
        break;

    END_AUGMENT:
        int f = numeric_limits<int>::max();
        for(int here = t; trace[here] != here; here = trace[here])
            f <?= residue(trace[here], here);
        for(int here = t; trace[here] != here; here = trace[here])
            flow[trace[here]][here] += f, flow[here][trace[here]] -= f;
        //printf("flow %d\n", f);

        res += f;
    }

    //printf("flow from %d to %d is %d\n", s, t, res);

    return res;
}

int solve() {
    int res = numeric_limits<int>::max();
    for(int t = 1; t < n; t++)
        res <?= max_flow(0, t);
    return res;
}

int main() {
    int m;
    while(scanf("%d%d", &n, &m) == 2) {

        REP(i, n) REP(j, n)
            cap[i][j] = 0;
        g.assign(n, Edges());

        REP(i, m) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            cap[a][b] = cap[b][a] = c;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        printf("%d\n", solve());
    }
    
    return 0;
}



// Powered by Fate Testarossa
