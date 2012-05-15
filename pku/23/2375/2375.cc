#include <cstdio>
#include <set>
#include <map>
#include <complex>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef complex<int> P;

typedef vector<P> Edges;
typedef map<P,Edges> Graph;

namespace std {
    template<class T>
    bool operator<(const complex<T>& a, const complex<T>& b) {
        return (make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag()));
    }
}

void dfs(Graph& g, P& root, Edges& result, set<P>& visited) {
    if (visited.count(root) > 0)
        return;
    visited.insert(root);
    Edges& v = g[root];
    for(int i = 0; i < (int)v.size(); i++)
        dfs(g, v[i], result, visited);
    result.push_back(root);
}
int scc(Graph& g) {

    Edges order;
    {
        set<P> visited;
        for(Graph::iterator it = g.begin(); it != g.end(); ++it) {
            P root = it->first;
            dfs(g, root, order, visited);
        }
    }

    Graph r;
    for(Graph::iterator it = g.begin(); it != g.end(); ++it) {
        P a = it->first;
        Edges& v = it->second;
        for(int i = 0; i < (int)v.size(); i++) {
            P b = v[i];
            r[b].push_back(a);
        }
    }

    int n = 0;
    {
        set<P> visited;
        for(int i = 0; i < (int)order.size(); i++) {
            P& root = order[i];
            if (visited.count(root) == 0) {
                Edges v;
                dfs(r, root, v, visited);
                n++;
            }
        }
    }

    return n;
}


const int INF = numeric_limits<int>::max();


int main() {

    int w, h;
    scanf("%d%d", &w, &h);
    vector< vector<int> > field(h+2, vector<int>(w+2, INF));
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            int t;
            scanf("%d", &t);
            field[i][j] = t;
        }
    }

    Graph g;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            if (field[i-1][j] <= field[i][j])
                g[P(i,j)].push_back(P(i-1,j));
            if (field[i][j-1] <= field[i][j])
                g[P(i,j)].push_back(P(i,j-1));
            if (field[i+1][j] <= field[i][j])
                g[P(i,j)].push_back(P(i+1,j));
            if (field[i][j+1] <= field[i][j])
                g[P(i,j)].push_back(P(i,j+1));
        }
    }

    printf("%d\n", scc(g) - 1);


    return 0;
}
