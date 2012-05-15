#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

typedef vector<int> Edges;
typedef vector<Edges> Graph;

int main() {

    int m, n;
    cin >> m >> n;

    Graph g(n);

    REP(i, m) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    vector<int> trace(n, -1);
    queue<int> q;
    q.push(0);
    trace[0] = 0;

    while(!q.empty()) {
        int here = q.front();
        q.pop();

        Edges& v = g[here];
        REP(i, v.size()) {
            int there = v[i];
            if (trace[there] < 0) {
                trace[there] = here;
                q.push(there);
            }
        }
    }

    int start = 0, goal = n-1;
    if (trace[goal] < 0) {
        cout << -1 << endl;
    }
    else {
        vector<int> route;
        for(int here = goal; here != start; here = trace[here])
            route.push_back(here+1);
        route.push_back(start+1);
        reverse(ALLOF(route));
        cout << (int)route.size() << endl;
        copy(ALLOF(route), ostream_iterator<int>(cout, "\n"));
    }

    return 0;
}
