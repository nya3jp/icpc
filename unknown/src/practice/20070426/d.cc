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


Graph solve(vector<int> v, int n) {

    Graph g;

    vector<bool> used(n, false);

    REP(iStep, v.size()) {

        int here = v[iStep];

        vector<bool> cand(used);

        for(int i = iStep; i < (int)v.size(); i++)
            cand[v[i]] = true;

        int there = find(ALLOF(cand), false) - cand.begin();

        g[here].push_back(there);
        g[there].push_back(here);

        used[there] = true;

    }

    return g;
}

void print(Graph& g, int here, int last) {
    cout << "(" << here+1;
    FOR(it, g[here]) {
        int there = *it;
        if (there == last)
            continue;
        cout << " ";
        print(g, there, here);
    }
    cout << ")";
}

void print(Graph& g) {
    print(g, g.begin()->first, -1);
    cout << endl;
}



int main() {

    for(string line; getline(cin, line); ) {

        vector<int> v;
        istringstream is(line);
        for(int x; is >> x; )
            v.push_back(x);

        if (v.empty()) {
            cout << "(1)" << endl;
        }
        else {
            int n = v.back();

            REP(i, v.size())
                v[i]--;

            Graph g = solve(v, n);

            print(g);
        }

    }

    return 0;
}

