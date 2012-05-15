#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 100

int adj[N][N];
int n;
int route[N];
int routeLen;

const int INF = numeric_limits<int>::max() / 3;

int dijkstra(int s, int t) {
    int dists[N];
    bool visited[N];
    REP(i, N) {
        dists[i] = INF;
        visited[i] = false;
    }
    dists[s] = 0;

    for(;;) {
        int next = -1;
        REP(i, n) if (!visited[i]) {
            if (next < 0 || dists[i] < dists[next])
                next = i;
        }
        if (next < 0)
            break;
        //printf("dists[%d] = %d\n", next, dists[next]);
        visited[next] = true;
        REP(i, n)
            dists[i] <?= dists[next] + adj[next][i];
    }

    return dists[t];
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        scanf("%d", &n);
        REP(i, n) REP(j, n) {
            int x;
            scanf("%d", &x);
            if (x == 0)
                x = INF;
            adj[i][j] = x;
        }

        {
            string line;
            getline(cin, line);
            getline(cin, line);
            istringstream is(line);
            routeLen = 0;
            int x;
            while(is >> x) {
                x--;
                route[routeLen++] = x;
            }
        }

        int shortest = 0;
        REP(iStart, routeLen-1) {
            int s = route[iStart];
            int t = route[iStart+1];
            shortest += adj[s][t];
        }

        //printf("shortest = %d\n", shortest);

        int worst = 0;
        int cur = 0;
        REP(iStart, routeLen-1) {
            int s = route[iStart];
            int t = route[iStart+1];
            int backup = adj[s][t];
            adj[s][t] = INF;
            {
                int now = cur + dijkstra(s, route[routeLen-1]);
                worst >?= now;
                //printf("removing %d-%d comes %d\n", s, t, now);
            }
            adj[s][t] = backup;
            cur += backup;
        }

        printf("%d\n", worst-shortest);

    }

    return 0;
}

