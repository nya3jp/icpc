#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

#define N 30
#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int n;
bool adj[N][N];
bool res[N];
int res_n;
bool covered[N];

void search(int a, int used = 0) {
    if (used >= res_n)
        return;
    if (a == n) {
        int c = count(covered, covered+n, true);
        if (c < res_n) {
            res_n = c;
            REP(i, n)
                res[i] = covered[i];
        }
    }
    else {
        bool should = false;
        REP(i, a)
            if (adj[a][i] && !covered[i])
                should = true;
        covered[a] = false;
        if (!should)
            search(a+1, used);
        covered[a] = true;
        search(a+1, used+1);
    }
}

int main() {

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {

        int m;
        cin >> n >> m;

        REP(i, n) REP(j, n) adj[i][j] = false;

        REP(i, m) {
            int a, b;
            cin >> a >> b;
            adj[a][b] = adj[b][a] = true;
        }

        res_n = n+1;
        REP(i, n)
            covered[i] = false;
        search(0);

        printf("Case #%d: %d\n", iCase+1, res_n);
        bool first = true;
        REP(i, n) {
            if (res[i]) {
                printf("%s%d", (first ? "" : " "), i);
                first = false;
            }
        }
        printf("\n");

    }

    return 0;
}
