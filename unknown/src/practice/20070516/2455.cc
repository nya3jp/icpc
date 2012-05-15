#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 200
#define M 40000

struct Edge {
    int a, b, c;
};

Edge all_edges[M];

int n;
int capacity[N][N];
int flow[N][N];
int times;

#define residue(i,j) (capacity[i][j] - flow[i][j])

bool go() {

    const int s = 0, t = n-1;

    REP(i, n) REP(j, n)
        flow[i][j] = 0;

    int res = 0;

    while(res < times) {

        vector<int> trace(n, -1);
        queue<int> q;
        q.push(s);
        trace[s] = s;
        while(!q.empty()) {
            int here = q.front();
            q.pop();
            REP(there, n) {
                if (residue(here, there) > 0 && trace[there] < 0) {
                    trace[there] = here;
                    q.push(there);
                    if (there == t)
                        goto SHORT_CIRCUIT;
                }
            }
        }
        if (trace[t] < 0)
            break;

    SHORT_CIRCUIT:
        int nextflow = numeric_limits<int>::max();
        for(int here = t; here != s; here = trace[here]) {
            int there = trace[here];
            nextflow <?= residue(there, here);
        }
        for(int here = t; here != s; here = trace[here]) {
            int there = trace[here];
            flow[there][here] += nextflow;
            flow[here][there] -= nextflow;
        }
        res += nextflow;
    }

    return (res >= times);
}

int main() {

    int m;
    scanf("%d%d%d", &n, &m, &times);

    int lower = 1, upper = 1;

    REP(i, m) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        all_edges[i] = (Edge){a, b, c};
        upper >?= c;
    }

    while(upper-lower > 0) {
        int middle = (lower+upper)/2;
        REP(i, n) REP(j, n)
            capacity[i][j] = 0;
        REP(i, m) {
            Edge& e = all_edges[i];
            if (e.c <= middle) {
                capacity[e.a][e.b]++;
                capacity[e.b][e.a]++;
            }
        }
        if (go())
            upper = middle;
        else
            lower = middle+1;
    }

    printf("%d\n", lower);

    return 0;
}
