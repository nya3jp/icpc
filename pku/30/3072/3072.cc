#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 20
const double PI = acos(0.0) * 2;
typedef complex<double> P;
const double INF = 1.0e100;

double adj[N+1][N+1][N+1];
double res[N+1][N+1];

double diff(double a, double b) {
    double d = abs(a-b);
    if (d > PI)
        d = 2*PI - d;
    return d;
}

int main() {

    double r;
    int n;
    while(scanf("%lf%d", &r, &n) == 2 && n >= 0) {

        vector<P> points(n+1);
        REP(i, n) {
            int x, y;
            scanf("%d%d", &x, &y);
            points[i] = P(x, y);
        }
        points[n] = points[0] - (points[n-1]-points[0]);

        REP(i, n+1) REP(j, n+1) REP(k, n+1) {
            double angle = diff(arg(points[j]-points[i]), arg(points[k]-points[j]));
            double dist = abs(points[k]-points[j]);
            if (dist < r)
                adj[i][j][k] = angle/PI*180 + dist;
            else
                adj[i][j][k] = INF;
            //printf("%d->%d->%d = %.3f\n", i, j, k, (adj[i][j][k] == INF ? -1 : adj[i][j][k]));
        }

        REP(i, n+1) REP(j, n+1)
            res[i][j] = INF;

        typedef pair<int,int> position;
        typedef pair<double,position> node;
        priority_queue<node, vector<node>, greater<node> > q;
        q.push(node(0.0, position(n, 0)));
        while(!q.empty()) {

            position here = q.top().second;
            double dist = q.top().first;
            q.pop();

            if (res[here.first][here.second] == INF) {
                //printf("%d-%d: %.3f\n", here.first, here.second, dist);
                res[here.first][here.second] = dist;
                REP(next, n) {
                    if (adj[here.first][here.second][next] < INF) {
                        q.push(node(dist+adj[here.first][here.second][next],
                                    position(here.second, next)));
                    }
                }
            }

        }

        double ans = INF;
        REP(i, n)
            ans <?= res[i][n-1];

        if (ans < INF)
            printf("%.0f\n", ans);
        else
            printf("impossible\n");

    }

    return 0;
}
