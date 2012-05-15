#include <iostream>
#include <cmath>
using namespace std;

const double INF = numeric_limits<double>::max();

#define EP 1.0e-8
inline int SGN(double x) { return (abs(x) < EP ? 0 : x < 0 ? -1 : 1); }
#define LS(x, y) (SGN((x)-(y)) < 0)
#define LE(x, y) (SGN((x)-(y)) <= 0)
#define EQ(x, y) (SGN((x)-(y)) == 0)
inline int abs(int n) { return (n < 0 ? -n : n); }

int bit_count(int x) {
    int c = 0;
    for(int i = 0; i < 32; i++)
        if (x & (1 << i))
            c++;
    return c;
}

struct Solver {

    int n;
    int horz[10];
    int vert[10];
    int grid;
    int sx, sy;
    int dx, dy;
    int tlower, tupper;

    struct Travel {
        double time, fuel;
        Travel() : time(0), fuel(0) {
        }
    };

    Solver() {
        cin >> n >> grid;
        for(int i = 0; i < n; i++) {
            cin >> horz[i];
            horz[i] = horz[i] / 5 * 5;
        }
        for(int i = 0; i < n; i++) {
            cin >> vert[i];
            vert[i] = vert[i] / 5 * 5;
        }
        cin >> sx >> sy >> dx >> dy;
        dx -= sx; dy -= sy;
        sx--; sy--;
        cin >> tlower >> tupper;
    }

    bool calc(int pattern, Travel& tr1, Travel& tr2) {
        if (bit_count(pattern) != dy)
            return false;
        int x = sx, y = sy;
        tr1 = tr2 = Travel();
        for(int k = 0; k < dx+dy; k++) {
            int dir = (pattern >> k) & 1;
            if (dir == 0) {
                // horz
                if (horz[y] == 0)
                    return false;
                {
                    double mph = horz[y];
                    double mpg = 80 - 0.03*mph*mph;
                    tr1.time += grid / mph;
                    tr1.fuel += grid / mpg;
                }
                {
                    double mph = 5;
                    double mpg = 80 - 0.03*mph*mph;
                    tr2.time += grid / mph;
                    tr2.fuel += grid / mpg;
                }
                x+=(dx<0?-1:1);
            }
            else {
                // vert
                if (vert[y] == 0)
                    return false;
                {
                    double mph = vert[x];
                    double mpg = 80 - 0.03*mph*mph;
                    tr1.time += grid / mph;
                    tr1.fuel += grid / mpg;
                }
                {
                    double mph = 5;
                    double mpg = 80 - 0.03*mph*mph;
                    tr2.time += grid / mph;
                    tr2.fuel += grid / mpg;
                }
                y+=(dy<0?-1:1);
            }
        }
        assert(x == sx+dx && y == sy+dy);
        tr1.time *= 60;
        tr2.time *= 60;
        return true;
    }

    void solve() {
        printf("sx=%d sy=%d dx=%d dy=%d\n", sx, sy, dx, dy);
        Travel tr1, tr2;
        tr1.time = tr1.fuel = tr2.time = tr2.fuel = INF;
        for(int i = 0; i < (1<<(abs(dx)+abs(dy))); i++) {
            Travel t1, t2;
            if (calc(i, t1, t2)) {
                printf("(%.3f, %.3f), (%.3f, %.3f)\n", t1.time, t1.fuel, t2.time, t2.fuel);
                if (LE(tlower, t1.time) && LE(t1.time, tupper)) {
                    if (LS(t1.time, tr1.time) ||
                        (EQ(t1.time, tr1.time) && LS(t1.fuel, tr1.fuel))) {
                        tr1 = t1;
                    }
                    if (LS(t1.fuel, tr2.fuel) ||
                        (EQ(t1.fuel, tr2.fuel) && LS(t1.time, tr2.time))) {
                        tr2 = t1;
                    }
                }
                if (LE(tlower, t2.time) && LE(t2.time, tupper)) {
                    if (LS(t2.time, tr1.time) ||
                        (EQ(t2.time, tr1.time) && LS(t2.fuel, tr1.fuel))) {
                        tr1 = t2;
                    }
                    if (LS(t2.fuel, tr2.fuel) ||
                        (EQ(t2.fuel, tr2.fuel) && LS(t2.time, tr2.time))) {
                        tr2 = t2;
                    }
                }
            }
        }
        if (tr1.time == INF) {
            printf("IMPOSSIBLE\n");
        }
        else {
            printf("The earliest  arrival: %d minutes, fuel %.2f gallons\n",
                   (int)ceil(tr1.time), tr1.fuel);
            printf("The economical traval: %d minutes, fuel %.2f gallons\n",
                   (int)ceil(tr2.time), tr2.fuel);
        }
    }

};

int main() {
    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        printf("Scenario %d:\n", iCase+1);
        Solver s;
        s.solve();
    }
    return 0;
}

