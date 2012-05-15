#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef double Weight;
typedef double Flow;

const Weight WEIGHT_INFTY = 1.0e100;
const Flow FLOW_INFTY = 1.0e100;
const double EPS = 1.0e-8;

#define residue(i,j) (cap[i][j] - flow[i][j])
#define rcost(i,j) (cost[i][j] + pot[i] - pot[j])
Weight min_cost_flow(vector< vector<Flow> > cap, vector< vector<Weight> > cost, int s, int t) {
    int n = cap.size();

    vector< vector<Flow> > flow(n, n);
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

        if (n == 0 && m == 0)
            break;

        vector< vector<double> > adj(n, m);
        REP(i, n) REP(j, m) {
            cin >> adj[i][j];
        }
        vector< vector<double> > weights(n+m+2, n+m+2);
        REP(i, n) REP(j, m) {
            weights[2+i][2+n+j] = adj[i][j];
            weights[2+n+j][2+i] = -adj[i][j];
        }

        vector< vector<double> > cap(n+m+2, vector<double>(n+m+2, 0));
        REP(i, n) REP(j, m)
            cap[2+i][2+n+j] = 1;
        REP(i, n)
            cap[0][2+i] = 1;
        REP(j, m)
            cap[2+n+j][1] = 1;

        //*
        double res = min_cost_flow(cap, weights, 0, 1);
        /*/
        vector<int> matching = min_cost_match(adj);
        double res = 0;
        REP(i, n)
            res += adj[i][matching[i]];
        //*/
        printf("%.2f\n", res / n + EPS);
    }

    return 0;
}
