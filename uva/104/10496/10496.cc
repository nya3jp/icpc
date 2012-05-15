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


int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        int x, y;
        cin >> x >> y;

        vector< pair<int,int> > v;
        cin >> x >> y;
        v.push_back(make_pair(x, y));

        int n;
        cin >> n;
        n++;
        v.resize(n);

        for(int i = 1; i < n; i++) {
            cin >> x >> y;
            v[i] = make_pair(x, y);
        }

        vector< vector<int> > adj(n, n);

        REP(i, n) REP(j, n)
            adj[i][j] = abs(v[i].first-v[j].first) + abs(v[i].second-v[j].second);

        typedef int Weight;
#define N 11
        const Weight WEIGHT_INFTY = 1000;
        Weight tsp[1<<N][N];
        const int s = 0;
        REP(i, 1<<n) REP(j, n)
            tsp[i][j] = WEIGHT_INFTY;
        tsp[1<<s][s] = 0; // sから始まるpath
        REP(i, 1<<n) REP(j, n)// if (i&(1<<j))
            REP(k, n)
                tsp[i|(1<<k)][k] <?= tsp[i][j] + adj[j][k];
        Weight* last = tsp[(1<<n)-1];
        REP(j, n)
            last[j] += adj[j][s]; // sに戻る場合
        int res = *min_element(last, last+n);

        cout << "The shortest path has length " << res << endl;

    }

    return 0;
}

