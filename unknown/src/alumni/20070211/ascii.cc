#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef unsigned long long int integer;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define EPS 1.0e-8

#define N 100

int n, w, h;

int xs[N];
int ys[N];

double res[N][N];

void solve_one(int x, int y, double left_y, double right_y, int sgn) {
    //fprintf(stderr, "solve_one(%d,%d,%.2f,%.2f,%d)\n", x, y, left_y, right_y, sgn);
    double upper = max(left_y, right_y);
    double lower = min(left_y, right_y);
    double& cell = res[y][x];

    double t;
    if (abs(lower-upper) < EPS) {
        if (upper > y+1)
            t = 1;
        else if (upper < y)
            t = 0;
        else
            t = upper-y;
    }
    if (y+1 <= lower && y+1 <= upper) {
        t = 1.0;
    }
    else if (lower <= y && upper <= y) {
        t = 0;
    }
    else if (y <= lower && upper <= y+1) {
        t = ((upper-y)+(lower-y))/2.0;
        //fprintf(stderr, "%f\n", t);
        assert(0 <= t && t <= 1);
    }
    else if (y <= lower && y+1 < upper) {
        double dy = y+1-lower;
        double dx = dy / (upper-lower);
        t = dx*dy/2.0 + (1-dx)*dy + (1-dy);
        //fprintf(stderr, "%f %f %f hoge\n", dx, dy, t);
        assert(0 <= t && t <= 1);
    }
    else if (lower < y && upper <= y+1) {
        double dy = upper-y;
        double dx = dy / (upper-lower);
        t = dx*dy/2.0;
        //fprintf(stderr, "%f\n", t);
        assert(0 <= t && t <= 1);
    }
    else {
        double dx1, dx2;
        {
            double dy = y-lower;
            dx1 = dy / (upper-lower);
        }
        {
            double dy = y+1-lower;
            dx2 = dy / (upper-lower);
        }
        t = ((1-dx1)+(1-dx2))/2.0;
        //fprintf(stderr, "%f\n", t);
        assert(0 <= t && t <= 1);
    }
    //fprintf(stderr, "(%d,%d): %.2f (%d)\n", x, y, t*sgn, sgn);
    cell += t*sgn;
}

void solve() {
    REP(iPoint, n) {
        int ox = xs[iPoint];
        int oy = ys[iPoint];
        int dx = xs[(iPoint+1)%n] - xs[iPoint];
        int dy = ys[(iPoint+1)%n] - ys[iPoint];
        if (dx > 0) {
            int sgn = 1;
            REP(ddx, dx) {
                int x = ox + ddx;
                double left_y = oy + (double)dy/dx * ddx;
                double right_y = oy + (double)dy/dx * (ddx+1);
                REP(y, h) {
                    solve_one(x, y, left_y, right_y, sgn);
                }
            }
        }
        if (dx < 0) {
            int sgn = -1;
            REP(ddx, -dx) {
                int x = ox - ddx - 1;
                double right_y = oy + (double)dy/(-dx) * ddx;
                double left_y = oy + (double)dy/(-dx) * (ddx+1);
                REP(y, h) {
                    solve_one(x, y, left_y, right_y, sgn);
                }
            }
        }

        /*
        if (dx != 0) {
            int sgn = (dx > 0 ? 1 : -1);
            REP(ddxa, abs(dx)) {
                int ddx = sgn*ddxa;
                int x = ox+ddx+(sgn<0 ? -1 : 0);
                double left_y = oy + (double)dy/dx * ddx;
                double right_y = oy + (double)dy/dx * (ddx+sgn);
                REP(y, h) {
                    solve_one(x, y, left_y, right_y, sgn);
                }
            }
        }
        */
    }
}

int main() {
    freopen("ascii.in", "r", stdin);
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        cin >> n >> w >> h;
        REP(i, n)
            cin >> xs[i] >> ys[i];
        REP(i, h) REP(j, w)
            res[i][j] = 0;
        solve();
        /*
        REP(i, h) {
            REP(j, w) {
                printf("%.2f ", res[h-1-i][j]);
            }
            printf("\n");
        }
        */
        REP(i, h) {
            REP(j, w) {
                const char PTN[] = ".+o$#";
                int x = (int)floor(res[h-1-i][j]*4+EPS);
                printf("%c", PTN[x]);
            }
            printf("\n");
        }
    }
    return 0;
}
