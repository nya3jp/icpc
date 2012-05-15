#include <iostream>
#include <queue>
#include <cstdio>
#include <string>
#include <map>
#include <set>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) (c).begin(), (c).end()

typedef map<char, vector<pair<char,int> > > Graph;

int dijkstra(Graph& g, char start, char goal) {
    map<char, int> dists;
    set<char> visited;

    FOR(it, g)
        dists[it->first] = numeric_limits<int>::max()/3;

    dists[start] = 0;

    for(;;) {
        char next = 0;
        FOR(it, g) {
            char here = it->first;
            if (visited.count(here) == 0) {
                if (next == 0 || dists[here] < dists[next])
                    next = here;
            }
        }
        if (next == 0)
            break;
        visited.insert(next);
        FOR(it, g[next])
            dists[it->first] <?= dists[next] + it->second;
    }

    return dists[goal];
}

int main() {

    for(;;) {

        Graph g;

        int total = 0;
        for(string s; cin >> s && s != "deadend"; ) {
            char a = s[0];
            char b = s[s.size()-1];
            int len = s.size();
            g[a].push_back(make_pair(b, len));
            g[b].push_back(make_pair(a, len));
            total += len;
        }
        if (!cin)
            break;

        vector<char> odds;
        FOR(it, g)
            if (it->second.size()%2 == 1)
                odds.push_back(it->first);

        if (!odds.empty()) {
            total += dijkstra(g, odds[0], odds[1]);
        }

        cout << total << endl;

    }


    return 0;
}

