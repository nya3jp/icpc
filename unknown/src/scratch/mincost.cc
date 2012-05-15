#define residue(i,j) (cap[i][j] - flow[i][j])
#define rcost(i,j) (weights[i][j] + pot[i] - pot[j])
Weight min_cost_flow(vector< vector<Flow> > cap, vector< vector<Weight> > cost, int s, int t) {
    int n = cap.size();

    vector< vector<Flow> > flow(n, n);
    vector<Weight> pot(n);

    Weight res = 0;
    for(;;) {

        vector<Weight> dists(n+1, INF);
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

        Flow f = INF;
        for(int c = t; c != s; c = trace[c])
            f <?= residue(trace[c], c);
        for(int c = t; c != s; c = trace[c]) {
            flow[trace[c]][c] += f;
            flow[c][trace[c]] -= f;
            res += weights[trace[c]][c] * f;
        }

        REP(i, n)
            pot[i] += dists[i];
    }

    return res;
}
