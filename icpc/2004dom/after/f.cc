#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <complex>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)


vector<string> split(string line, char c) {
    istringstream is(line);
    vector<string> res;
    string s;
    while(getline(is, s, c))
        res.push_back(s);
    return res;
}


int main() {

    for(;;) {

        int nCrossings;
        cin >> nCrossings;
        if (nCrossings == 0)
            break;

        map<string, vector<pair<string,int> > > bg;
        map<string, map<string, int> > g;

        REP(iCrossing, nCrossings) {
            string s;
            cin >> s;
            vector<string> parsed = split(s, '-');
            string from = parsed[0], to = parsed[1];
            bg[from].push_back(make_pair(to, 1));
            bg[to].push_back(make_pair(from, -1));
            g[from][to] = 1;
        }

        FOR(it, bg) {
            string here = it->first;
            vector<pair<string,int> >& adj = bg[here];
            REP(i, adj.size()) REP(j, adj.size()) {
                pair<string,int>& a = adj[i];
                pair<string,int>& b = adj[j];
                string from = a.first, to = b.first;
                if (a.second*b.second == 1) {
                    if (g[from].count(to) == 0)
                        g[from][to] = 2;
                    if (g[to].count(from) == 0)
                        g[to][from] = 2;
                }
                else {
                    g[from][to] = g[to][from] = 0;
                }
            }
        }

        cout << (int)bg.size() << endl;

        int nQueries;
        cin >> nQueries;

        REP(iQuery, nQueries) {
            string s;
            cin >> s;
            vector<string> parsed = split(s, '-');
            string start = parsed[0], goal = parsed[1];

            map<string, int> dists;
            queue<string> q;
            dists[start] = 0;
            q.push(start);
            while(!q.empty()) {
                string here = q.front();
                q.pop();
                //cout << here << "by " << dists[here] << endl;
                FOR(it, g[here]) {
                    string there = it->first;
                    int d = it->second;
                    if (d > 0 && dists.count(there) == 0) {
                        dists[there] = (dists[here] + d) % 2;
                        q.push(there);
                    }
                }
            }

            bool res = (dists[goal] == 1);
            cout << (res ? "YES" : "NO") << endl;
        }


    }

    return 0;
}

