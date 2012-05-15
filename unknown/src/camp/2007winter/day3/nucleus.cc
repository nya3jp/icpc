#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 100

int g[2*N+2][2*N+2];
int f[2*N+2][2*N+2];
int adj[N][N];
int n;
int out[N], in[N];
int limit;

const int INF = 0x3fffffff;

#define RESIDUE(from,to) (g[from][to] - f[from][to])

int max_flow(int s, int t) {

    int nn = 2*n+2;

    int flow = 0;
    for(;;) {
        queue<int> q;
        q.push(s);
        vector<int> trace(nn, -1);
        trace[s] = s;
        while(!q.empty() && trace[t] < 0) {
            int i = q.front();
            q.pop();
            REP(j, nn) if (trace[j] < 0 && RESIDUE(i, j) > 0) {
                trace[j] = i;
                q.push(j);
            }
        }
        if (trace[t] < 0)
            break;
        int w = INF;
        for(int j = t; trace[j] != j; j = trace[j]) {
            //printf("%d <- ", j);
            w <?= RESIDUE(trace[j], j);
        }
        //printf("%d = %d\n", s, w);
        for(int j = t; trace[j] != j; j = trace[j]) {
            f[trace[j]][j] += w;
            f[j][trace[j]] -= w;
        }
        flow += w;

        //printf("flow:\n");
        /*
        REP(i, 2*n+2) {
            REP(j, 2*n+2) {
                printf("%10d", f[i][j]);
            }
            printf("\n");
        }
        */
    }

    return flow;
}


int solve() {

    REP(i, 2*n+2) REP(j, 2*n+2)
        g[i][j] = f[i][j] = 0;

    REP(j, n) REP(i, n) REP(k, n)
        adj[i][k] <?= adj[i][j] + adj[j][k];

    int total = 0;
    REP(i, n)
        total += out[i];

    REP(i, n) REP(j, n) {
        if (adj[i][j] < limit) {
            //printf("%d -> %d\n", i+2, j+2+n);
            g[i+2][j+2+n] = total; // check later
        }
    }

    int s = 0, t = 1;
    REP(i, n) {
        //printf("%d=%d : %d\n", s, i+2, out[i]);
        g[s][i+2] = out[i];
        g[i+2+n][t] = in[i];
    }

    /*
    printf("graph:\n");
    REP(i, 2*n+2) {
        REP(j, 2*n+2) {
            printf("%10d", g[i][j]);
        }
        printf("\n");
    }
    */

    return max_flow(s, t);
}

int main() {

    freopen("nucleus.in", "r", stdin);

    for(;;) {
        int m;
        cin >> n >> m >> limit;
        if (!cin)
            break;

        REP(i, n) REP(j, n)
            adj[i][j] = (i == j ? 0 : INF);
        
        REP(i, m) {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            adj[a][b] = adj[b][a] = c;
        }
        
        REP(i, n)
            cin >> out[i];
        REP(i, n)
            cin >> in[i];

        // input end

        cout << solve() << endl;

    }
    
    return 0;
}
