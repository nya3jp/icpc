#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 100

map<string,int> ids;
vector<string> names;

int ID(string s) {
    if (ids.count(s) == 0) {
        ids.insert(make_pair(s, ids.size()));
        names.push_back(s);
    }
    return ids[s];
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n, p;
        cin >> n >> p;

        ids.clear();
        names.clear();

        bool one[N][N];
        REP(i, n) REP(j, n)
            one[i][j] = (i == j);

        bool init[N];

        REP(i, n) {
            string s;
            cin >> s;
            int here = ID(s);
            int c, m;
            cin >> c >> m;
            init[here] = ((c%2) == 1);
            REP(j, m) {
                string t;
                cin >> t;
                int there = ID(t);
                one[here][there] = !one[here][there];
            }
        }

        bool nth[N][N];
        REP(i, n) REP(j, n)
            nth[i][j] = (i == j);

        bool current[N][N];
        REP(i, n) REP(j, n)
            current[i][j] = one[i][j];

        while(p > 0) {
            if (p%2 == 1)
                mul(nth, current);
            mul(current, current);
            p /= 2;
        }

        bool res[N];
        REP(i, n) {
            res[i] = false;
            REP(j, n)
                res[i] ^= init[j] && nth[j][i];
        }

        cout << count(res, res+n, true) << endl;



    }


    return 0;
}
