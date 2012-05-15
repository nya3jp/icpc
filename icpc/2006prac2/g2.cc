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

int periods[N][N];
int wetime[N][N];
int flags[N][N];

struct Edge {
    int src, dest, weight, period, first;
    bool flag;
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

        REP(i, w) REP(j, h) {
            int we, sn, flag;
            cin >> sn >> we >> flag;
            periods[i][j] = we+sn;
            if (flag) {
                wetime[i][j] = we;
                flags[i][j] = false;
            }
            else {
                wetime[i][j] = sn;
                flags[i][j] = false;
            }
        }

#define ID(i,j) ((i)+(j)*w)

        int n = w*h+2;
        Graph g(n);
        REP(i, w) REP(j, h) {
            Edges& v = g[ID(i, j)];

            if (IN(i-1, 0, w)) {
                v.push_back((Edge){ID(i, j), ID(i-1, j),
                            xs[i]-xs[i-1], periods[i-1][j], wetime[i-1][j], false
                            });
            }
            if (IN(i+1, 0, w)) {
                v.push_back((Edge){ID(i, j), ID(i+1, j),
                            xs[i+1]-xs[i], periods[i+1][j], wetime[i+1][j], false
                            });
            }
            if (IN(j-1, 0, h)) {
                v.push_back((Edge){ID(i, j), ID(i, j-1),
                            ys[j]-ys[j-1], periods[i][j-1], wetime[i][j-1], false
                            });
            }
            if (IN(j+1, 0, h)) {
                v.push_back((Edge){ID(i, j), ID(i, j+1),
                            ys[j+1]-ys[j], periods[i][j+1], wetime[i][j+1], false
                            });
            }
        }
        int sx, sy, tx, ty;
        cin >> sx >> sy >> tx >> ty;


        {
            if (binary_search(xs, xs+w, sx)) { // ue
                int i = lower_bound(xs, xs+w, sx) - xs;
                int j = lower_bound(ys, ys+h, sy) - ys - 1;
                g[n-2].push_back((Edge){n-2, ID(i, j), sy-ys[j], periods[i][j], wetime[i][j], flags[i][j]});
                g[n-2].push_back((Edge){n-2, ID(i, j+1), ys[j+1]-sy, periods[i][j+1], wetime[i][j+1], flags[i][j+1]});
            }
            else { // migi
                int i = lower_bound(xs, xs+w, sx) - xs - 1;
                int j = lower_bound(ys, ys+h, sy) - ys;
                g[n-2].push_back((Edge){n-2, ID(i, j), sx-xs[i], periods[i][j], wetime[i][j], !flags[i][j]});
                g[n-2].push_back((Edge){n-2, ID(i+1, j), xs[i+1]-sx, periods[i+1][j], wetime[i+1][j], !flags[i+1][j]});
            }
        }
        {
            if (binary_search(xs, xs+w, tx)) { // ue
                int i = lower_bound(xs, xs+w, tx) - xs;
                int j = lower_bound(ys, ys+h, ty) - ys - 1;
                g[ID(i,j)].push_back((Edge){ID(i, j), n-1, ty-ys[j], 1, 1, false});//periods[i][j], wetime[i][j], flags[i][j]});
                g[ID(i,j+1)].push_back((Edge){ID(i, j+1), n-1, ys[j+1]-ty, 1, 1, false});//periods[i][j+1], wetime[i][j+1], flags[i][j+1]});
            }
            else { // migi
                int i = lower_bound(xs, xs+w, tx) - xs - 1;
                int j = lower_bound(ys, ys+h, ty) - ys;
                g[ID(i,j)].push_back((Edge){ID(i, j), n-1, tx-xs[i], 1, 1, false});//periods[i][j], wetime[i][j], flags[i][j]});
                g[ID(i+1,j)].push_back((Edge){ID(i+1, j), n-1, xs[i+1]-tx, 1, 1, false});//periods[i+1][j], wetime[i+1][j], flags[i+1][j]});
            }
        }

        vector<bool> visited(n, false);
        priority_queue<Edge, vector<Edge>, greater<Edge> > q;

        q.push((Edge){-1, n-2, 0});

        int res = -1;
        while(!q.empty()) {

            Edge e = q.top();
            q.pop();

            if (visited[e.dest])
                continue;

            cout << "(" << e.dest/w << "," << e.dest%w << ") visited cost = " << e.weight << endl;

            visited[e.dest] = true;
            if (e.dest == n-1) {
                res = e.weight;
                break;
            }

            FOR(it, g[e.dest]) if (!visited[it->dest]) {

                printf("expanding to (%d,%d) time %d : [%d][%d] flag=%d\n", it->dest%w, it->dest/w, e.weight, it->first, it->period-it->first, it->flag);

                Edge f = (Edge){it->src, it->dest, e.weight};
                int mod = f.weight % it->period;
                if ((mod >= it->first) == it->flag) {
                    // とおれる
                }
                else {
                    if (it->flag) 
                        f.weight = f.weight / it->period * it->period + it->first;
                    else
                        f.weight = f.weight / it->period * it->period + it->period;
                }
                f.weight += it->weight;
                q.push(f);

            }

        }

        cout << res << endl;


    }

    return 0;
}

// Powered by Fate Testarossa
