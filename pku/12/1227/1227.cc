#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) (c).begin(), (c).end()

typedef vector<int> Edges;
typedef map<int,Edges> Graph;

void dfs(Graph& g, int here, bool& bipartite, map<int,int>& reachable, int side) {

    if (reachable.count(here) > 0) {
        if (reachable[here] != side)
            bipartite = false;
        return;
    }

    reachable[here] = side;
    FOR(it, g[here]) {
        int there = *it;
        dfs(g, there, bipartite, reachable, side^1);
    }

}

bool solve(Graph& g, vector<int>& robots) {

    bool bipartite = true;
    map<int,int> reachable;

    if (robots.size() == 1) {
        //cerr << "alone" << endl;
        return true;
    }

    dfs(g, g.begin()->first, bipartite, reachable, 0);

    FOR(it, robots) {
        if (reachable.count(*it) == 0) {
            //cerr << "not reachable" << endl;
            return false;
        }
    }

    if (!bipartite) {
        //cerr << "not bipartite" << endl;
        return true;
    }

    int side = reachable[robots[0]];
    FOR(it, robots) {
        if (reachable[*it] != side) {
            //cerr << "bipartite and split" << endl;
            return false;
        }
    }

    //cerr << "bipartite but merged" << endl;
    return true;
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int nNodes, nRobots;
        cin >> nNodes >> nRobots;

        Graph g;

        REP(i, nNodes) {
            int s;
            cin >> s;

            int nEdges;
            cin >> nEdges;

            Edges edges(nEdges);
            REP(j, nEdges)
                cin >> edges[j];

            g[s] = edges;

        }

        vector<int> robots(nRobots);
        REP(i, nRobots)
            cin >> robots[i];

        cout << (solve(g, robots) ? "YES" : "NO") << endl;

    }

    return 0;
}

