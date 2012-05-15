/*
 * 最大流問題
 */

#include <vector>
#include <queue>
#include <algorithm>
//#include <limits>

using namespace std;


// フローネットワーク
typedef vector< vector<int> > F;




// sからtまでの最大流を求める
const int INF = 0x7fffffff; //numeric_limits<int>::max();
#define RESIDUE(from,to) (g[from][to] - (f[from][to] - f[to][from]))
int max_flow(F& g, int s, int t) {
    int n = g.size();
    F f(n, vector<int>(n, 0));
    int flow = 0;
    while(true) {
        queue<int> q;
        q.push(s);
        vector<int> trace(n, -1);
        trace[s] = s;

        while(!q.empty()) {
            int i = q.front();
            q.pop();
            for(int j = 0; j < n; j++) {
                if (trace[j] < 0 && RESIDUE(i, j) > 0) {
                    trace[j] = i;
                    q.push(j);
                }
            }
        }

        if (trace[t] < 0)
            break;

        int w = INF;
        for(int j = t; trace[j] != j; j = trace[j])
            w = min(w, RESIDUE(trace[j], j));
        for(int j = t; trace[j] != j; j = trace[j])
            f[trace[j]][j] += w;
        flow += w;
    }
    return flow;
}

#include <iostream>

int main() {
    int n;
    while(cin >> n) {
        n += 2;
        vector<int> p(n);
        for(int i = 2; i < n; i++)
            cin >> p[i];
        F g(n, vector<int>(n, 0));
        int m;
        cin >> m;
        for(int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            a++; b++;
            g[a][b] = c;
        }
        int s, t;
        cin >> s >> t;
        for(int i = 0; i < s; i++) {
            int a;
            cin >> a;
            a++;
            g[0][a] = INF;
        }
        for(int i = 0; i < t; i++) {
            int a;
            cin >> a;
            a++;
            g[a][1] = INF;
        }
        for(int i = 2; i < n; i++) {
            for(int j = 0; j < n; j++) {
                g[i][j] = min(g[i][j], p[i]);
                g[j][i] = min(g[j][i], p[i]);
            }
        }
        cout << max_flow(g, 0, 1) << endl;
    }
    return 0;
}

