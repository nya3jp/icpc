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

#define N 402

int g[N][N], f[N][N];
int n;

#define residue(i,j) (g[i][j] - f[i][j])
const int INF = numeric_limits<int>::max();

int maxflow(int s, int t) {
    int flow = 0;
    for(;;) {
        queue<int> q;
        q.push(s);
        vector<int> trace(n, -1);
        trace[s] = s;
        while(!q.empty() && trace[t] < 0) {
            int i = q.front();
            q.pop();
            REP(j, n) if (trace[j] < 0 && residue(i,j) > 0) {
                trace[j] = i;
                q.push(j);
            }
        }
        if (trace[t] < 0)
            break;
        int w = INF;
        for(int i = trace[t], j = t; i != j; j = i, i = trace[i])
            w <?= residue(i, j);
        for(int i = trace[t], j = t; i != j; j = i, i = trace[i]) {
            f[i][j] += w;
            f[j][i] -= w;
        }
        flow += w;
    }
    return flow;
}

int main() {

    int nCows, nFoods, nDrinks;
    scanf("%d%d%d", &nCows, &nFoods, &nDrinks);

    int s = 2*nCows+nFoods+nDrinks;
    int t = 2*nCows+nFoods+nDrinks+1;
    n = t+1;
    REP(iCow, nCows) {
        int mFoods, mDrinks;
        scanf("%d%d", &mFoods, &mDrinks);
        REP(i, mFoods) {
            int iFood;
            scanf("%d", &iFood);
            iFood--;
            g[iFood][nFoods+iCow] = 1;
        }
        REP(i, mDrinks) {
            int iDrink;
            scanf("%d", &iDrink);
            iDrink--;
            g[nFoods+nCows+iCow][nFoods+2*nCows+iDrink] = 1;
        }
    }
    REP(i, nFoods)
        g[s][i] = 1;
    REP(i, nCows)
        g[nFoods+i][nFoods+nCows+i] = 1;
    REP(i, nDrinks)
        g[nFoods+2*nCows+i][t] = 1;

    /*
    REP(i, n) {
        REP(j, n)
            printf("%d", g[i][j]);
        printf("\n");
    }
    */

    printf("%d\n", maxflow(s, t));

    return 0;
}

