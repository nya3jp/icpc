#include <iostream>
#include <algorithm>
#include <map>
#include <memory.h>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef complex<int> P;

int min_cost_matching(vector< vector<int> > adj) {
    int n = adj.size();

    vector<int> back(n, -1);
    REP(left, n) {
        typedef pair<int,pair<int,int> > K;
        priority_queue<K, vector<K>, greater<K> > q;
        REP(right, n)
            q.push(K(adj[left][right], make_pair(right, right)));
        vector<int> trace(n, -1);
        int last;
        while(!q.empty()) {
            int prev = q.top().second.first;
            int cur = q.top().second.second;
            int cost = q.top().first;
            q.pop();
            if (trace[cur] < 0) {
                trace[cur] = prev;
                if (back[cur] < 0) {
                    last = cur;
                    break;
                }
                int left = back[cur];
                REP(next, n)
                    q.push(K(cost+adj[left][cur]+adj[left][next],
                             make_pair(cur, next)));
            }
        }
        int cur = last;
        while(trace[cur] != cur) {
            back[cur] = back[trace[cur]];
            cur = trace[cur];
        }
        back[cur] = left;
    }

    int sum = 0;
    REP(right, n) {
        assert(back[right] >= 0);
        sum += adj[back[right]][right];
    }
    return sum;
}

int main() {

    for(;;) {
        int h, w;
        cin >> h >> w;
        if (h == 0 && w == 0)
            break;

        vector<string> field(h);
        REP(i, h)
            cin >> field[i];

        vector<P> houses, men;
        REP(i, h) REP(j, w) {
            switch(field[i][j]) {
            case 'H': houses.push_back(P(i, j)); break;
            case 'm': men.push_back(P(i, j)); break;
            }
        }

        int n = houses.size();
        vector< vector<int> > adj(n, n);
        REP(i, n) REP(j, n) {
            P d = houses[i] - houses[j];
            adj[i][j] = abs(d.real()) + abs(d.imag());
        }

        cout << min_cost_matching(adj) << endl;

    }
    
    return 0;
}
