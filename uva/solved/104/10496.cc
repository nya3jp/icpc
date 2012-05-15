#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) ((c).begin()), ((c).end())

pair<int,int> readPair() {
    int a, b;
    cin >> a >> b;
    return make_pair(a, b);
}

#define INFTY 0x10000000

inline int abs(int a) {
    return a < 0 ? -a : a;
}

int main() {
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        readPair();
        vector< pair<int,int> > v;
        v.push_back(readPair());
        int n;
        cin >> n;
        REP(i, n)
            v.push_back(readPair());
        n++;
        vector< vector<int> > dist(n, vector<int>(n));
        REP(i, n) REP(j, n)
            dist[i][j] = abs(v[i].first-v[j].first) + abs(v[i].second-v[j].second);
        vector< vector<int> > tsp(1<<n, vector<int>(n, INFTY));
        tsp[1][0] = 0;
        REP(i, 1<<n) REP(j, n)
            if (i&(1<<j))
                REP(k, n)
                    tsp[i|(1<<k)][k] <?= tsp[i][j] + dist[j][k];
        REP(j, n)
            tsp[(1<<n)-1][j] += dist[j][0];
        int res = *min_element(ALLOF(tsp[(1<<n)-1]));
        cout << "The shortest path has length " << res << endl;
    }
    return 0;
}
