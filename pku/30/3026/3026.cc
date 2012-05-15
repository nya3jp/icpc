//#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef pair<int,int> P;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

void solve() {

    int w, h;
    //cin >> w >> h >> ws;
    scanf("%d%d ", &w, &h);

    //vector<string> field(h);
    //REP(i, h)
    //    getline(cin, field[i]);
    char field[h][w+3];
    REP(i, h)
        fgets(field[i], w+3, stdin);

    vector<P> points;
    REP(i, h) REP(j, w)
        if (field[i][j] == 'A' || field[i][j] == 'S')
            points.push_back(make_pair(i, j));

    int n = points.size();

    int adj[n][n];
    //vector< vector<int> > adj(n, vector<int>(n));
    REP(a, n) {
        const int INF = 0x7fffffff;
        //map<P, int> dist;
        int dist[h][w]; REP(i, h) REP(j, w) dist[i][j] = INF;
        //set<P> visited;
        bool visited[h][w]; REP(i, h) REP(j, w) visited[i][j] = false;
        queue<P> q;
        //dist[points[a]] = 0;
        dist[points[a].first][points[a].second] = 0;
        q.push(points[a]);
        while(!q.empty()) {
            P p = q.front();
            q.pop();
            //if (visited.count(p) > 0)
            if (visited[p.first][p.second])
                continue;
            //cout << "visiting " << p.first << ',' << p.second << endl;
            //visited.insert(p);
            visited[p.first][p.second] = true;
            int DIRS[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
            REP(i, 4) {
                P pp = make_pair(p.first+DIRS[i][0], p.second+DIRS[i][1]);
                if (field[pp.first][pp.second] != '#') {
                    //dist.insert(make_pair(pp, INF));
                    //dist[pp] <?= dist[p]+1;
                    dist[pp.first][pp.second] <?= dist[p.first][p.second]+1;
                    q.push(pp);
                }
            }
        }
        REP(b, n)
            //adj[a][b] = dist[points[b]];
            adj[a][b] = dist[points[b].first][points[b].second];
    }

    //vector<bool> have(n, false);
    bool have[n]; REP(i, n) have[i] = false;
    have[0] = true;
    int cost = 0;
    REP(r, n-1) {
        int shortest = 0x7fffffff;
        int next = -1;
        REP(i, n) if (have[i])
            REP(j, n) if (!have[j])
                if (adj[i][j] < shortest)
                    shortest = adj[i][j], next = j;
        have[next] = true;
        cost += shortest;
    }

    //cout << cost << endl;
    printf("%d\n", cost);
}


int main() {
    //freopen("3026.in", "r", stdin);
    int n;
    //cin >> n;
    scanf("%d", &n);
    while(n-- > 0)
        solve();
    return 0;
}
