#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long int integer;

struct XGCD {
    integer a, b, x, y, g;

    XGCD(integer a, integer b) : a(a), b(b) {
        //assert(a > 0 && b > 0);
        integer n, m, x1, x2;
        n = a;
        m = b;
        x1 = 1;
        x2 = 0;
        while(true) {
            integer q = n/m;
            integer r = n%m;
            if (r == 0)
                break;
            integer x3 = x1 - q*x2;
            x1 = x2; x2 = x3;
            n = m; m = r;
        }
        g = m;
        x = x2;
        y = (g-a*x)/b;
    }
};

integer gcd(integer n, integer m) {
    //assert(n > 0 && m > 0);
    integer r;
    while((r = n%m) != 0) {
        n = m;
        m = r;
    }
    return m;
}

struct DE {
    bool r;
    integer a, b, c, x, y;
    integer dx, dy;

    DE(integer a, integer b, integer c) : a(a), b(b), c(c) {
        if (a == 0 && b == 0) {
            if (r = (c == 0)) {
                x = y = 0;
                dx = dy = 0;
            }
        }
        else if (b == 0) {
            if (r = (c % a == 0)) {
                x = c / a;
                y = 0;
                dx = 0;
                dy = 1;
            }
        }
        else if (a == 0) {
            if (r = (c % b == 0)) {
                x = 0;
                y = c/b;
                dx = 1;
                dy = 0;
            }
        }
        else {
            bool na = (a < 0);
            bool nb = (b < 0);
            integer aa = (na ? -a : a);
            integer bb= (nb ? -b : b);
            integer g = gcd(aa, bb);
            if (r = (c%g == 0)) {
                XGCD xgcd(aa/g, bb/g);
                //printf("xgcd:%lld,%lld->%lld,%lld\n", xgcd.a, xgcd.b, xgcd.x, xgcd.y);
                x = xgcd.x*c/g;
                y = xgcd.y*c/g;
                if (na) x = -x;
                if (nb) y = -y;
                dx = b/g;
                dy = -a/g;
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                }
            }
        }
        //printf("a=%lld\nb=%lld\nc=%lld\nx=%lld\ny=%lld\ndx=%lld\ndy=%lld\n", a, b, c, x, y, dx, dy);
        normalize();
        //printf("a=%lld\nb=%lld\nc=%lld\nx=%lld\ny=%lld\ndx=%lld\ndy=%lld\n", a, b, c, x, y, dx, dy);
        //assert(!r || a*x+b*y == c);
    }

    void swap() {
        std::swap(a, b);
        std::swap(x, y);
        std::swap(dx, dy);
        if (dx < 0) {
            dx = -dx;
            x = -x;
        }
        normalize();
    }
    void normalize() {
        if (r && dx != 0) {
            integer a = x/dx;
            x -= dx*a;
            y -= dy*a;
            if (x < 0) {
                x += dx;
                y += dy;
            }
        }
    }
};



int main() {
    while(true) {
        integer a, b, c;
        int k;
        scanf("%lld%lld%lld%d", &a, &b, &c, &k);
        //scanf("%I64d%I64d%I64d%d", &a, &b, &c, &k);
        if (a == 0 && b == 0 && c == 0 && k == 0)
            break;
        integer mod = 1;
        for(int i=0; i<k; i++) mod <<= 1;
        integer d = (b - a)&(mod - 1);
        DE de(c, mod, d);
        if (de.r) {
            printf("%lld\n", de.x);
            //printf("%I64d\n", de.x);
        }
        else {
            printf("FOREVER\n");
        }
    }
    return 0;
}


