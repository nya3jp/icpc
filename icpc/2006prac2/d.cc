#include <iostream>
#include <fstream>
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

#define REP(i,n) for(int i = 0 ; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

int n;
vector<int> g;
vector<int> deltas;

int main() {
    ifstream cin("D.txt");

    while(cin >> n && n > 0) {
        g.resize(n);
        deltas.resize(n);
        map<string,int> nameToId;
        vector<string> idToName;
        int cost = 0;
        REP(i, n) {
            string s, t;
            int c1, c2;
            cin >> s >> c1 >> t >> c2;
            if (nameToId.count(s) == 0) {
                nameToId.insert(make_pair(s, (int)idToName.size()));
                idToName.push_back(s);
            }
            if (nameToId.count(t) == 0) {
                nameToId.insert(make_pair(t, (int)idToName.size()));
                idToName.push_back(t);
            }
            int is = nameToId[s];
            int it = nameToId[t];
            deltas[is] = c1 - c2;
            g[is] = it;
            cost += c2;
        }
        /*
        REP(i, n)
            cout << idToName[i] << " depends " << idToName[g[i]] << " with " << deltas[i] << endl;
        */


        int res = 0;
        vector<int> v(n, 0);
        REP(a, n) {
            if (v[a] == 0) {
                int b = a;
                while(v[b] == 0) {
                    v[b] = 1;
                    b = g[b];
                }
                if (v[b] == 3) {
                    replace(v.begin(), v.end(), 1, 3);
                    continue;
                }
                int d = 0x7fffffff;
                while(v[b] == 1) {
                    v[b] = 2;
                    d <?= deltas[b];
                    b = g[b];
                }
                res += d;
                replace(v.begin(), v.end(), 1, 3);
                replace(v.begin(), v.end(), 2, 3);
            }
        }

        cout << cost+res << endl;

    }

    return 0;
}

// Powered by Fate Testarossa
