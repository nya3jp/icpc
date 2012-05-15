/*
 * UVA 10465 Homer Simpson
 * 2005-08-29
 * by nya
 */

#include <cstdio>
#include <algorithm>
#include <cassert>

struct XGCD {
    int a, b, x, y, g;
    XGCD(int a, int b) : a(a), b(b) {
        int n, m, x1, x2;
        n = a; m = b;
        x1 = 1; x2 = 0;
        while(true) {
            int q = n/m;
            int r = n%m;
            if (r == 0)
                break;
            int x3 = x1 - q*x2;
            x1 = x2; x2 = x3;
            n = m; m = r;
        }
        g = m;
        x = x2;
        y = (g-a*x)/b;
    }
};

int gcd(int n, int m) {
    int r;
    while((r = n%m) != 0) {
        n = m;
        m = r;
    }
    return m;
}

struct DiophantineEquation {
    bool r;
    int a, b, c, x, y;
    int dx, dy;
    DiophantineEquation(int a, int b, int c) : a(a), b(b), c(c) {
        if (a == 0 && b == 0) {
            if (r = (c == 0)) {
                x = y = 0;
                dx = dy = 0;
            }
        }
        else if (b == 0) {
            if (r = (c % a != 0)) {
                x = c / a;
                y = 0;
                dx = dy = 0;
            }
        }
        else if (a == 0) {
            if (r = (c % b != 0)) {
                x = 0;
                y = c / b;
                dx = dy = 0;
            }
        }
        else {
            int g = gcd(a, b);
            if (r = (c%g == 0)) {
                XGCD xgcd(a/g, b/g);
                x = xgcd.x*c/g;
                y = xgcd.y*c/g;
                dx = b/g;
                dy = -a/g;
            }
        }
    }
    void swap() {
        std::swap(a, b);
        std::swap(x, y);
        std::swap(dx, dy);
        dx = -dx;
        dy = -dy;
    }
};

int main() {
    int n, m, t;
    while(std::scanf("%d%d%d", &n, &m, &t) == 3) {
        for(int dt=0; dt<=t; dt++) {
            DiophantineEquation d(n, m, t-dt);
            if (d.r) {
                if (! (d.dx == 0 && d.dy == 0)) {
                    if (d.a < d.b)
                        d.swap();
                    int delta = -d.x / d.dx;
                    d.x += d.dx*delta;
                    d.y += d.dy*delta;
                    if (d.x < 0) {
                        d.x += d.dx;
                        d.y += d.dy;
                    }
                    while(d.y < 0) {
                        d.x -= d.dx;
                        d.y -= d.dy;
                    }
                    if (d.x < 0)
                        continue;
                    //std::printf("%d + %d = ", (n >= m ? d.x : d.y), (n >= m ? d.y : d.x));
                }
                std::printf("%d", d.x + d.y);
                if (dt > 0)
                    std::printf(" %d", dt);
                std::printf("\n");
                break;
            }
        }
    }
    return 0;
}
