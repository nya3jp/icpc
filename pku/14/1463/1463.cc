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

typedef vector<int> Edges;
typedef vector<Edges> Graph;

int dfs(Graph& g, int here, int parent, int color, vector< vector<int> >& memo) {
    int n = g.size();

    int& res = memo[here][color];
    if (res < 0) {
        res = n+1;
        Edges& v = g[here];
        int m = v.size();
        {
            int total = 1;
            REP(i, m) {
                int there = v[i];
                if (there == parent)
                    continue;
                total += dfs(g, there, here, 1, memo);
            }
            res <?= total;
        }
        if (color == 1) {
            int total = 0;
            REP(i, m) {
                int there = v[i];
                if (there == parent)
                    continue;
                total += dfs(g, there, here, 0, memo);
            }
            res <?= total;
        }

        //printf("%d->%d[%d] = %d\n", parent, here, color, res);
    }
    return res;
}

int main() {

    for(;;) {

        int n;
        if (scanf("%d", &n) != 1)
            break;

        Graph g(n);

        REP(i, n) {
            int a, m;
            scanf("%d : (%d )", &a, &m);
            REP(j, m) {
                int b;
                scanf("%d", &b);
                g[a].push_back(b);
                g[b].push_back(a);
            }
        }

        vector< vector<int> > memo(n, vector<int>(2, -1));

        int res = dfs(g, 0, -1, 1, memo);

        printf("%d\n", res);

    }

    return 0;
}

