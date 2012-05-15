#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

struct Edge {
    int a, b, c;
    int* state;
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

int dfs(Graph& g, int here, vector<int>& label, int& l, int index) {
    int res = -1;
    int cur = label[here];
    Edges& neighbors = g[here];
    if (index == (int)neighbors.size())
        return cur;
    Edge& e = neighbors[index];
    int there = e.b;
    int cost = e.c;
    int* state = e.state;
    if (*state == -1) {
        if (res < 0) {
            *state = 0;
            vector<int> newlabel(label);
            int ll = l;
            res = dfs(g, here, newlabel, l, index);
        }
        if (res < 0) {
            *state = 1;
            vector<int> newlabel(label);
            int ll = l;
            res = dfs(g, here, newlabel, l, index);
        }
    }
    else if (*state == 1) {
        int u = label[there];
        if (u < 0) {
            u = dfs(g, there, label, l);
            if (u < 0)
                return -1;
            if (u >= cur)
                return -1;
        }
        res = u;
    }
    return min(res, dfs(g, here, label, l, index+1));
}

int dfs(Graph& g, int here, vector<int>& label, int& l) {

    int cur = l++;
    label[here] = cur;

    return dfs(g, here, label, l, 0);
}

int solve(Graph g) {
    vector<int> label(n, -1);
    int l = 0;
    int n = g.size();
    REP(root, n) {
        if (label[root] < 0) {
            dfs0(g, root, label, l);
        }
    }
}


int main() {

    int iCase = 0;
    for(;;) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;

        Graph g(n);
        REP(i, m) {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            int* state = new int;
            *state = -1;
            g[a].push_back((Edge){a, b, c, state});
            g[b].push_back((Edge){b, a, c, state});
        }

        int res = solve(g);
        if (res < 0)
            cout << "There is no reliable net possible for test case " << ++iCase << "." << endl;
        else
            cout << "The minimal cost for test case " << ++iCase << " is " << res << "." << endl;
    }        

    return 0;
}
