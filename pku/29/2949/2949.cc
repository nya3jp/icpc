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

struct Edge {
    int src, dest, weight;
};

inline int NODEOF(char* p) {
    return (int)(p[0]-'a') * 26 + (int)(p[1]-'a');
}

#define N (26*26)
#define M 100000

Edge edges[M];

typedef double Weight;
const double INF = numeric_limits<double>::infinity();

int main() {

    for(;;) {
        int nEdges;
        scanf("%d", &nEdges);
        if (nEdges == 0)
            break;

        REP(i, nEdges) {
            char str[1024];
            scanf("%s", str);
            int len = strlen(str);
            Edge& e = edges[i];
            e.src = NODEOF(str);
            e.dest = NODEOF(str+len-2);
            e.weight = -len;
        }

        int n = N;
        int m = nEdges;

        Weight dp[N+2][N] = {{0}};
        REP(k, n) {
            REP(i, n)
                dp[k+1][i] = INF;
            REP(i, m) {
                Edge& e = edges[i];
                if (dp[k][e.src] < INF)
                    dp[k+1][e.dest] <?= dp[k][e.src] + e.weight;
            }
        }

        Weight res = INF;
        REP(i, n) {
            Weight lo = -INF;
            REP(k, n) if (dp[n][i] < INF && dp[k][i] < INF)
                lo >?= (dp[n][i] - dp[k][i]) / (n - k);
            if (lo > -INF)
                res <?= lo;
        }
        if (res == INF) {
            puts("No solution.");
        }
        else {
            printf("%.2f\n", -res);
        }

    }

    return 0;
}
