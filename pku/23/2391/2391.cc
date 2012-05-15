#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 200

const int INF = 1000000001;
const int SRC = -2;
const int UNREACHABLE = -1;

int n;
int adj[N][N];
int src[N], dest[N];
int flow[N][N];

bool solve(int limit) {
    REP(i, n) REP(j, n)
        flow[i][j] = 0;

    int outs[N], ins[N];
    REP(i, n)
        outs[i] = ins[i] = 0;

    int total = 0;
    int need = accumulate(src, src+n, (int)0);
    while(total < need) {
        int trace_left[N], trace_right[N];
        REP(i, n)
            trace_left[i] = (outs[i] < src[i] ? SRC : UNREACHABLE);
        REP(j, n)
            trace_right[j] = UNREACHABLE;

        int goal = UNREACHABLE;
        REP(r, n) {
            REP(j, n) if (trace_right[j] == UNREACHABLE)
                REP(i, n) if (trace_left[i] != UNREACHABLE && adj[i][j] <= limit)
                    trace_right[j] = i;
            
            REP(j, n)
                if (trace_right[j] != UNREACHABLE && ins[j] < dest[j])
                    goal = j;
            if (goal != UNREACHABLE)
                break;
            
            REP(i, n) if (trace_left[i] == UNREACHABLE)
                REP(j, n) if (trace_right[j] != UNREACHABLE && adj[i][j] <= limit && flow[i][j] > 0)
                    trace_left[i] = j;
        }
        if (goal == UNREACHABLE)
            break;

        int residue = INF;
        int start = trace_right[goal];
        while(trace_left[start] != SRC) {
            residue <?= flow[start][trace_left[start]];
            start = trace_right[trace_left[start]];
        }
        residue <?= dest[goal]-ins[goal];
        residue <?= src[start]-outs[start];
        
        flow[trace_right[goal]][goal] += residue;
        for(int here = trace_right[goal]; trace_left[here] != SRC; here = trace_right[trace_left[here]]) {
            flow[here][trace_left[here]] -= residue;
            flow[trace_right[trace_left[here]]][trace_left[here]] += residue;
        }
        
        outs[start] += residue;
        ins[goal] += residue;
        total += residue;

        /*
        REP(a, n) {
            REP(b, n) {
                printf("%-3d", flow[a][b]);
            }
            printf("\n");
        }
        printf("\n");
        */
    }

    return (total == need);
}

int main() {

    int nEdges;
    scanf("%d%d", &n, &nEdges);

    REP(i, n)
        scanf("%d%d", &src[i], &dest[i]);

    REP(a, n) REP(b, n)
        adj[a][b] = INF;
    REP(a, n)
        adj[a][a] = 0;

    REP(i, nEdges) {
        int a, b;
        int c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        adj[a][b] <?= c;
        adj[b][a] <?= c;
    }

    REP(j, n) REP(i, n) REP(k, n)
        adj[i][k] <?= adj[i][j] + adj[j][k];

    int res;
    if (!solve(INF)) {
        res = -1;
    }
    else {
        int upper = 1;
        while(!solve(upper))
            upper *= 2;
        int lower = upper / 2;
        while(upper-lower > 0) {
            //printf("%d-%d\n", lower, upper);
            int middle = (lower+upper)/2;
            if (solve(middle))
                upper = middle;
            else
                lower = middle+1;
        }
        res = lower;
    }

    printf("%d\n", res);
    /*
    if (res >= 0) {
        solve(res);
        REP(a, n) {
            REP(b, n) {
                printf("%-3d", flow[a][b]);
            }
            printf("\n");
        }
    }
    */

    return 0;
}
