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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

typedef vector<int> Edges;
typedef vector<Edges> Graph;

struct Solver {
    Graph& g;
    const int n;
    vector<int> res;
    vector<int> outer;
    vector<bool> visited;

    Solver(Graph& g) : g(g), n(g.size()) {
    }
    void solve() {
        res.clear();
        outer.resize(n);
        REP(a, n) {
            Edges& v = g[a];
            if (v.size() == 2) {
                outer[a] = -1;
            }
            else {
                REP(i, v.size()) {
                    int b = v[i];
                    if (g[b].size() == 2)
                        outer[a] = b;
                }
            }
        }

        visited.assign(n, false);

        int s = 0;
        REP(a, n)
            if (g[a].size() > 2)
                s = a;

        dfs(s);

        bool ok = (res.size() == n);

        REP(i, n) {
            int j = (i+1)%n;
            if (count(ALLOF(g[res[i]]), res[j]) == 0)
                ok = false;
        }

        if (!ok) {
            printf("-1\n");
        }
        else {
            REP(i, n)
                printf("%d%s", res[i]+1, (i < n-1 ? " " : "\n"));
        }
    }
    bool dfs(int here) {
        if (here < 0 || visited[here])
            return false;
        visited[here] = true;
        if (!dfs(outer[here])) {
            REP(i, g[here].size())
                dfs(g[here][i]);
        }
        res.push_back(here);
        return true;
    }
};

int main() {

    // May fate be with you!


    int n, m;
    scanf("%d%d", &n, &m);

    Graph g(n);

    REP(i, m) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    Solver x(g);
    x.solve();

    return 0;
}



// Powered by fate testarossa
