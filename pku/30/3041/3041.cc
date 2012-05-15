#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

int n;
bool g[500][500];
bool visited[500];
int toleft[500];

bool augment(int left) {
    if (left < 0)
        return true;
    if (visited[left])
        return false;
    visited[left] = true;

    REP(right, n) {
        if (g[left][right] && augment(toleft[right])) {
            toleft[right] = left;
            return true;
        }
    }

    return false;
}

int main() {

    int m;
    scanf("%d%d", &n, &m);

    REP(i, n) REP(j, n)
        g[i][j] = false;

    REP(i, m) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g[a][b] = true;
    }

    REP(i, n)
        toleft[i] = -1;

    int res = 0;
    REP(i, n) {
        REP(j, n) visited[j] = false;
        if (augment(i))
            res++;
    }
    printf("%d\n", res);

    return 0;
}
