#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef long long int integer;



void solve() {

    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> nodeWeight(n);
    REP(i, n)
        scanf("%d", &nodeWeight[i]);

    typedef pair<integer,int> Node;
    vector< vector<Node> > g(n);

    REP(j, m) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        g[a].push_back(Node((integer)c, b));
        g[b].push_back(Node((integer)c, a));
    }

    vector<bool> visited(n, false);
    
    priority_queue<Node, vector<Node>, greater<Node> > q;
    q.push(Node(0, 0));

    integer res = 0;
    while(!q.empty()) {
        int a = q.top().second;
        integer length = q.top().first;
        q.pop();
        if (visited[a])
            continue;
        visited[a] = true;
//      cout << "visiting " << a << " with length " << length << endl;
        res += length * nodeWeight[a];
        vector<Node>& adj = g[a];
        REP(i, adj.size())
            q.push(Node(length + adj[i].first, adj[i].second));
    }

    if (count(visited.begin(), visited.end(), false) > 0)
        cout << "No Answer" << endl;
    else
        cout << res << endl;

}

int main() {
    int n;
    scanf("%d", &n);
    while(n-- > 0)
        solve();
    return 0;
}
