#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>
#include <stack>

using namespace std;

#define N 10000

typedef vector<int> Edges;
typedef vector<Edges> Graph;

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph g(n);

    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g[a].push_back(b);
    }

    //vector<int> cnt(n, 0);
    int cnt[N];
    fill(cnt, cnt+n, 0);

    Graph r(n);

    for(int a = 0; a < n; a++) {
        //vector<bool> v(n, false);
        bool v[N];
        fill(v, v+n, false);
        stack<int> s;
        s.push(a);
        v[a] = true;
        while(!s.empty()) {
            int b = s.top();
            s.pop();
            if (b < a) {
            }
            for(int i = 0; i < (int)g[b].size(); i++) {
                int c = g[b][i];
                if (!v[c]) {
                    v[c] = true;
                    s.push(c);
                }
            }
        }
        for(int b = 0; b < n; b++) {
            if (v[b])
                r[a].push_back(b);
        }
    }

    printf("%d\n", count(cnt, cnt+n, n));

    return 0;
}

