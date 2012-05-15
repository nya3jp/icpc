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

void paint(Graph& g, int here, int color, vector<int>& sides) {
    if (sides[here] < 0) {
        sides[here] = color;
        Edges& v = g[here];
        REP(i, v.size()) {
            int there = v[i];
            paint(g, there, color^1, sides);
        }
    }
}

bool augment(int left, vector< vector<bool> >& adj, vector<int>& back, vector<bool>& visited) {
    int m = adj[0].size();
    if (left < 0)
        return true;
    if (visited[left])
        return false;
    visited[left] = true;
    REP(right, m) if (adj[left][right]) {
        if (augment(back[right], adj, back, visited)) {
            back[right] = left;
            return true;
        }
    }
    return false;
}

int match(vector< vector<bool> >& adj) {
    int n = adj.size(), m = adj[0].size();
    vector<int> back(m, -1);
    int res = 0;
    REP(i, n) {
        vector<bool> visited(n, false);
        if (augment(i, adj, back, visited))
            res++;
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
            }
        }

        vector<int> sides(n, -1);
        REP(i, n)
            if (sides[i] < 0)
                paint(g, i, 0, sides);

        //cerr << "sides determined" << endl;

        int lefts = count(ALLOF(sides), 0);
        int rights = n - lefts;

        map<int, int> ids[2];
        REP(i, n) {
            map<int,int>& s = ids[sides[i]];
            s.insert(make_pair(i, (int)s.size()));
        }
        assert(ids[0].size() == lefts);
        assert(ids[1].size() == rights);

        vector< vector<bool> > adj(lefts, vector<bool>(rights, false));
        REP(left, n) if (sides[left] == 0) {
            Edges& v = g[left];
            REP(i, v.size()) {
                int right = v[i];
                assert(sides[right] == 1);
                adj[ids[0][left]][ids[1][right]] = true;
            }
        }

        int res;
        if (lefts == 0 || rights == 0)
            res = n;
        else
            res = n - match(adj);

        printf("%d\n", res);
        
    }

    return 0;
}

