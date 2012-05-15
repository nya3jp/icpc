#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

typedef vector<int> Edges;
typedef map<int, Edges> Graph;


int parse(Graph& g) {
    int here = -1;
    scanf(" (%d", &here);
    if (here < 0)
        return -1;
    g[here];
    for(;;) {
        char c;
        scanf(" %c", &c);
        if (c == ')') {
            break;
        }
        else if (c == '(') {
            ungetc(c, stdin);
            int there = parse(g);
            g[here].push_back(there);
            g[there].push_back(here);
        }
        else {
            assert(false);
        }
    }
    return here;
}

Graph parse() {
    Graph g;
    if (parse(g) < 0)
        return Graph();
    return g;
}


vector<int> solve(Graph g) {
    vector<int> res;
    while(g.size() > 1) {
        int next = 10000;
        FOR(it, g)
            if (it->second.size() == 1)
                next <?= it->first;
        int adj = g[next][0];
        g.erase(next);
        g[adj].erase(find(ALLOF(g[adj]), next));
        //res.push_back(next);
        res.push_back(adj);
    }
    //res.push_back(g.begin()->first);
    return res;
}


int main() {

    for(;;) {
        Graph g = parse();
        //cout << g.size() << endl;
        if (g.empty())
            break;
        vector<int> res = solve(g);
        if (res.empty()) {
            cout << endl;
        }
        else {
            REP(i, res.size()-1)
                cout << res[i] << " ";
            cout << res.back() << endl;
        }
    }

    return 0;
}

