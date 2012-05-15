#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define C 1000
#define N 100

#define INF (2*C*N*2)

int table1[2*C*N+1];
int table2[2*C*N+1];

struct Point {
    int x, y;
};

int main() {
    int n;
    while(scanf("%d", &n), n > 0) {
        Point points[N];
        for(int i = 0; i < n; i++)
            scanf("%d%d", &points[i].x, &points[i].y);

        double s = 0.0;

        {
            fill(table1, table1+2*C*n+1, -INF*2);
            table1[C*n] = 0;
            int* p = table1;
            int* q = table2;
            for(int i = 0; i < n; i++) {
                Point& pt = points[i];
                int dx = pt.x;
                int dy = pt.y;
                for(int x = 0; x < 2*C*n+1; x++) {
                    if (x+dx < 0 || x+dx >= 2*C*n+1)
                        q[x] = p[x-dx] + dy;
                    else if (x-dx < 0 || x-dx >= 2*C*n+1)
                        q[x] = p[x+dx] - dy;
                    else
                        q[x] = max(p[x-dx] + dy, p[x+dx] - dy);

                    if (q[x] < -INF)
                        q[x] = -INF*2;
                }
                swap(p, q);
            }
            for(int i = 0; i < 2*C*n+1; i++) {
                int x = i - C*n;
                int y = p[i];
                if (y > -INF) {
                    s = max(s, sqrt((double)x*x + (double)y*y));
                }
            }
        }
        {
            fill(table1, table1+2*C*n+1, INF*2);
            table1[C*n] = 0;
            int* p = table1;
            int* q = table2;
            for(int i = 0; i < n; i++) {
                Point& pt = points[i];
                int dx = pt.x;
                int dy = pt.y;
                for(int x = 0; x < 2*C*n+1; x++) {
                    if (x+dx < 0 || x+dx >= 2*C*n+1)
                        q[x] = p[x-dx] + dy;
                    else if (x-dx < 0 || x-dx >= 2*C*n+1)
                        q[x] = p[x+dx] - dy;
                    else
                        q[x] = min(p[x-dx] + dy, p[x+dx] - dy);
                    if (q[x] > INF)
                        q[x] = INF*2;
                }
                swap(p, q);
            }
            for(int i = 0; i < 2*C*n+1; i++) {
                int x = i - C*n;
                int y = p[i];
                if (y < INF)
                    s = max(s, sqrt((double)x*x + (double)y*y));
            }
        }
        printf("Maximum distance = %.3f meters.\n", s);
    }
    return 0;
}
