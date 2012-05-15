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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

pair<int,int> read_point() {
    int x, y;
    cin >> x >> y;
    return make_pair(x, y);
}

const int INF = numeric_limits<int>::max()/4;
int dp[1<<11][11];
int adj[11][11];

int main() {

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {

        vector<pair<int,int> > v;
        read_point();
        v.push_back(read_point());
        int n;
        cin >> n;
        REP(i, n)
            v.push_back(read_point());
        n++;

        REP(i, n) REP(j, n)
            adj[i][j] = abs(v[i].first-v[j].first) + abs(v[i].second-v[j].second);

        REP(i, 1<<n) REP(j, n)
            dp[i][j] = INF;
        dp[1][0] = 0;
        REP(visited, 1<<n) REP(last, n) REP(next, n)
            dp[visited|(1<<next)][next] <?= dp[visited][last] + adj[last][next];

        int res = INF;
        REP(last, n)
            res <?= dp[(1<<n)-1][last] + adj[last][0];

        cout << "The shortest path has length " << res << endl;
    }

    return 0;
}
