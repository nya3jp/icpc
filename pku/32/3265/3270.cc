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

#define N 10000

void dfs(int here, vector< pair<int,int> >& sorted, vector<bool>& visited, vector<int>& route) {
    if (!visited[here]) {
        visited[here] = true;
        route.push_back(here);
        int there = sorted[here].second;
        dfs(there, sorted, visited, route);
    }
}

int main() {

    int n;
    scanf("%d", &n);

    vector< pair<int,int> > v(n);

    REP(i, n) {
        int x;
        scanf("%d", &x);
        v[i] = make_pair(x, i);
    }
    sort(ALLOF(v));

    int res = 0;
    vector<bool> visited(n, false);
    vector<int> route;
    int minimini = -1;
    route.reserve(n);
    REP(i, n) {
        if (!visited[i]) {
            route.clear();
            dfs(i, v, visited, route);
            int mini = numeric_limits<int>::max();
            int sum = 0;
            int m = route.size();
            REP(j, m) {
                mini <?= v[route[j]].first;
                sum += v[route[j]].first;
            }
            
            if (minimini < 0) {
                res += sum + (m-2)*mini;
                minimini = mini;
            }
            else {
                res += sum + min(-mini+(m-1)*minimini + 2*(minimini+mini),
                                 (m-2)*mini);
            }
        }
    }

    cout << res << endl;

    return 0;
}
