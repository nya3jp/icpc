#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

struct C {
    double x, y, r;
};

int main() {

    int n;
    while(scanf("%d", &n), n >= 0) {

        vector<C> v(n);
        REP(i, n) {
            C& c = v[i];
            scanf("%lf%lf%lf", &c.x, &c.y, &c.r);
        }

        vector<int> u(n, -1);
        int m = 0;
        REP(a, n) {
            if (u[a] < 0) {
                vector<int> q;
                u[a] = m++;
                q.push_back(a);
                while(!q.empty()) {
                    int x = q.back();
                    q.pop_back();
                    REP(y, n) {
                        if (u[y] < 0) {
                            double d = sqrt(pow(v[y].x-v[x].x, 2.0)+pow(v[y].y-v[x].y, 2.0));
                            double r1 = min(v[x].r, v[y].r);
                            double r2 = max(v[x].r, v[y].r);
                            if (d < r1+r2 && d+r1 > r2) {
                                u[y] = u[x];
                                q.push_back(y);
                            }
                        }
                    }
                }
            }
        }

        int res = 0;
        REP(i, m)
            res >?= count(u.begin(), u.end(), i);

        printf("The largest component contains %d rings\n", res);

    }

    return 0;
}

