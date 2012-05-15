#include <iostream>
#include <fstream>
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

#define REP(i,n) for(int i = 0 ; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

#define N 100

int xs[N];
int ys[N];
int w, h;

enum DIR {
    VERT, HORZ
};

int periods[N][N];
int first_period[N][N];
DIR first_dir[N][N];

struct Edge {
    int src, dest, weight, period, first_period;
    bool first_cango;
};
bool operator>(const Edge& a, const Edge& b) {
    return (a.weight > b.weight);
}

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;



int main() {
    ifstream cin("G.txt");

    while(cin >> w >> h && !(w == 0 && h == 0)) {

        xs[0] = ys[0] = 0;
        REP(i, w-1) cin >> xs[i+1];
        REP(i, h-1) cin >> ys[i+1];
        partial_sum(xs, xs+w, xs);
        partial_sum(ys, ys+h, ys);

        REP(j, h) REP(i, w) {
            int ns, ew, flag;
            cin >> ns >> ew >> flag;
            periods[i][j] = ns+ew;
            if (flag) {
                // HORZ first
                first_period[i][j] = ew;
                first_dir[i][j] = HORZ;
            }
            else {
                // VERT first
                first_period[i][j] = ns;
                first_dir[i][j] = VERT;
            }
        }

        int start_x, start_y, goal_x, goal_y;
        cin >> start_x >> start_y >> goal_x >> goal_y;

#define ID(i,j) ((i)+(j)*w)
#define X(id)   (id%w)
#define Y(id)   (id/w)

        int n = w*h+2;
        Graph g(n);

        REP(i, w) REP(j, h) {
            Edges& v = g[ID(i, j)];
            if (IN(i-1, 0, w)) {
                v.push_back((Edge){ID(i, j), ID(i-1, j),
                            xs[i]-xs[i-1], periods[i-1][j], first_period[i-1][j],
                            (first_dir[i-1][j] == HORZ)});
            }
            if (IN(i+1, 0, w)) {
                v.push_back((Edge){ID(i, j), ID(i+1, j),
                            xs[i+1]-xs[i], periods[i+1][j], first_period[i+1][j],
                            (first_dir[i+1][j] == HORZ)});
            }
            if (IN(j-1, 0, h)) {
                v.push_back((Edge){ID(i, j), ID(i, j-1),
                            ys[j]-ys[j-1], periods[i][j-1], first_period[i][j-1],
                            (first_dir[i][j-1] == VERT)});
            }
            if (IN(j+1, 0, h)) {
                v.push_back((Edge){ID(i, j), ID(i, j+1),
                            ys[j+1]-ys[j], periods[i][j+1], first_period[i][j+1],
                            (first_dir[i][j+1] == VERT)});
            }
        }

        int start_i, start_j, goal_i, goal_j;
        DIR start_dir, goal_dir;
        {
            if (binary_search(xs, xs+w, start_x)) { // VERT
                int i = lower_bound(xs, xs+w, start_x) - xs;
                int j = lower_bound(ys, ys+h, start_y) - ys - 1;
                g[n-2].push_back((Edge){n-2, ID(i, j),
                            start_y-ys[j], periods[i][j], first_period[i][j],
                            (first_dir[i][j] == VERT)});
                g[n-2].push_back((Edge){n-2, ID(i, j+1),
                            ys[j+1]-start_y, periods[i][j+1], first_period[i][j+1],
                            (first_dir[i][j+1] == VERT)});
                start_i = i;
                start_j = j;
                start_dir = VERT;
            }
            else { // HORZ
                int i = lower_bound(xs, xs+w, start_x) - xs - 1;
                int j = lower_bound(ys, ys+h, start_y) - ys;
                g[n-2].push_back((Edge){n-2, ID(i, j),
                            start_x-xs[i], periods[i][j], first_period[i][j],
                            (first_dir[i][j] == HORZ)});
                g[n-2].push_back((Edge){n-2, ID(i+1, j),
                            xs[i+1]-start_x, periods[i+1][j], first_period[i+1][j],
                            (first_dir[i+1][j] == HORZ)});
                start_i = i;
                start_j = j;
                start_dir = HORZ;
            }
        }

        {
            if (binary_search(xs, xs+w, goal_x)) { // VERT
                int i = lower_bound(xs, xs+w, goal_x) - xs;
                int j = lower_bound(ys, ys+h, goal_y) - ys - 1;
                g[ID(i, j)].push_back((Edge){ID(i, j), n-1,
                            goal_y-ys[j], 1, 1, true});
                g[ID(i, j+1)].push_back((Edge){ID(i, j+1), n-1,
                            ys[j+1]-goal_y, 1, 1, true});
                goal_i = i;
                goal_j = j;
                goal_dir = VERT;
            }
            else { // HORZ
                int i = lower_bound(xs, xs+w, goal_x) - xs - 1;
                int j = lower_bound(ys, ys+h, goal_y) - ys;
                g[ID(i, j)].push_back((Edge){ID(i, j), n-1,
                            goal_x-xs[i], 1, 1, true});
                g[ID(i+1, j)].push_back((Edge){ID(i+1, j), n-1,
                            xs[i+1]-goal_x, 1, 1, true});
                goal_i = i;
                goal_j = j;
                goal_dir = HORZ;
            }
        }

        int res = -1;

        if (start_i == goal_i && start_j == goal_j && start_dir == goal_dir) {
            res = abs(start_x-goal_x)+abs(start_y-goal_y);
        }

        priority_queue<Edge, vector<Edge>, greater<Edge> > q;
        q.push((Edge){-1, n-2, 0});
        vector<bool> visited(n, false);

        while(!q.empty() && res < 0) {
            Edge e = q.top();
            q.pop();
            if (visited[e.dest])
                continue;

            visited[e.dest] = true;
            if (e.dest == n-1) {
                res = e.weight;
                break;
            }

            //printf("(%d,%d) %d\n", X(e.dest), Y(e.dest), e.weight);

            FOR(it, g[e.dest]) {
                if (!visited[it->dest]) {
                    int arrival = e.weight + it->weight;
                    int mod = arrival%it->period;
                    //printf("(%d < %d) == %d", mod, it->first_period, it->first_cango);
                    if ((mod < it->first_period) == it->first_cango) {
                        // ok
                    }
                    else {
                        if (it->first_cango) {
                            arrival = arrival / it->period * it->period + it->period;
                        }
                        else {
                            arrival = arrival / it->period * it->period + it->first_period;
                        }
                    }
                    //printf("  (%d,%d) -> (%d,%d) %d\n", X(it->src), Y(it->src), X(it->dest), Y(it->dest), arrival);
                    q.push((Edge){it->src, it->dest, arrival});
                }
            }

        }

        cout << res << endl;


    }

    return 0;
}

// Powered by Fate Testarossa
