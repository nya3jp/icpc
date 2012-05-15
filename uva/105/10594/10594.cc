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

typedef long long int Weight;
typedef long long int Flow;

const Weight WEIGHT_INFTY = 0xfffffffffffffffll;
const Flow FLOW_INFTY = 0xfffffffffffffffll;
const Weight EPS = 0;

#define residue(i,j) (cap[i][j] - flow[i][j])
#define rcost(i,j) (cost[i][j] + pot[i] - pot[j])
Weight min_cost_flow(vector< vector<Flow> >& cap_, vector< vector<Weight> >& cost_, int s, int t, vector< vector<Weight> >& flow_) {
    int n = cap_.size();

    flow_.assign(n, n);

    Flow** cap = new Flow*[n];
    REP(i, n)
        cap[i] = &cap_[i][0];
    Weight** cost = new Weight*[n];
    REP(i, n)
        cost[i] = &cost_[i][0];
    Weight** flow = new Weight*[n];
    REP(i, n)
        flow[i] = &flow_[i][0];

    //vector< vector<Flow> > flow(n, n);
    vector<Weight> pot(n);

    Weight res = 0;
    for(;;) {

        vector<Weight> dists(n+1, WEIGHT_INFTY);
        vector<bool> visited(n, false);
        vector<int> trace(n, -1);
        dists[s] = 0;

        for(;;) {
            int cur = n;
            REP(i, n) if (!visited[i] && dists[i] < dists[cur])
                cur = i;
            if (cur == n)
                break;
            visited[cur] = true;
            REP(next, n) if (residue(cur, next) > EPS) {
                if (dists[next] > dists[cur] + rcost(cur, next) && !visited[next]) {
                    dists[next] = dists[cur] + rcost(cur, next);
                    trace[next] = cur;
                }
            }
        }
        if (!visited[t])
            break;

        Flow f = FLOW_INFTY;
        for(int c = t; c != s; c = trace[c])
            f <?= residue(trace[c], c);
        for(int c = t; c != s; c = trace[c]) {
            flow[trace[c]][c] += f;
            flow[c][trace[c]] -= f;
            res += cost[trace[c]][c] * f;
        }

        REP(i, n)
            pot[i] += dists[i];
    }

    return res;
}



int main() {

    for(;;) {

        int n, m;
        cin >> n >> m;
        if (!cin)
            break;

        n = 2 * n + 1;
        vector< vector<Flow> > cap(n, n);
        vector< vector<Weight> > cost(n, n);

        REP(i, m) {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            cap[a*2+1][b*2+1] = 1;
            cap[b*2+2][a*2+2] = 1;
            cost[a*2+1][b*2+1] = c;
            cost[b*2+1][a*2+1] = -c;
            cost[b*2+2][a*2+2] = c;
            cost[a*2+2][b*2+2] = -c;
        }

        Weight ttl, cp;
        cin >> ttl >> cp;
        REP(i, n) REP(j, n)
            cap[i][j] *= cp;

        for(int i = 1; i < n; i += 2)
            cap[i][i+1] = cap[i+1][i] = FLOW_INFTY;
        cap[0][1] = ttl;

        vector< vector<Flow> > flow(n, n);
        Weight res = min_cost_flow(cap, cost, 0, n-1, flow);

        if (flow[0][1] < ttl)
            cout << "Impossible." << endl;
        else
            cout << res << endl;

    }

    return 0;
}
