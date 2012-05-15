/*
 * UVA 10413 Crazy Savages
 * 2005-09-17
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <cassert>

#define MAX_SAVAGES 15
#define INF 1000001


typedef long long int integer;

struct XGCD {
    integer a, b, x, y, g;
    XGCD(integer a, integer b) : a(a), b(b) {
        integer n, m, x1, x2;
        n = a; m = b;
        x1 = 1; x2 = 0;
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
    integer r;
    while((r = n%m) != 0) {
        n = m;
        m = r;
    }
    return m;
}

struct DiophantineEquation {
    bool r;
    integer a, b, c, x, y;
    integer dx, dy;
    DiophantineEquation(integer a, integer b, integer c) : a(a), b(b), c(c) {
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
                dx = dy = 0;
            }
        }
        else if (a == 0) {
            if (r = (c % b == 0)) {
                x = 0;
                y = c / b;
                dx = dy = 0;
            }
        }
        else {
            bool na = (a < 0);
            bool nb = (b < 0);
            integer aa = (na ? -a : a);
            integer bb = (nb ? -b : b);
            integer g = gcd(aa, bb);
            if (r = (c%g == 0)) {
                XGCD xgcd(aa/g, bb/g);
                x = xgcd.x*c/g;
                y = xgcd.y*c/g;
                if (na) x = -x;
                if (nb) y = -y;
                dx = bb/g;
                dy = -aa/g;
            }
        }
        //std::cerr << a << "*" << x << "+" << b << "*" << y << "=" << c << std::endl;
        assert(!r || a*x+b*y == c);
    }
    void swap() {
        std::swap(a, b);
        std::swap(x, y);
        std::swap(dx, dy);
        if (dx < 0) {
            dx = -dx;
            x = -x;
        }
    }
};





struct Savage {
    integer iInitPos, iStep, nLives;
};

bool check(const Savage& s1, const Savage& s2, const integer m) {
    // there should not be non-negative integer k such that
    // c1+p1*k == c2+p2*k (mod m) , k <= min(l1, l2)
    // <=> (p2-p1)*k == c1-c2 (mod m)
    // [ a = p2-p1, c = c1-c2 ]
    // ak + ml == c
    DiophantineEquation e(s2.iStep-s1.iStep, m, -(s2.iInitPos-s1.iInitPos));
    assert(e.dx >= 0);
    //std::cerr << "Dio: " << e.a << ' ' << e.b << ' ' << e.c << std::endl;
    if (! e.r)
        return true;
    if (e.dx != 0) {
        integer a = e.x/e.dx;
        if (e.x < 0)
            a--;
        e.x -= e.dx*a;
        e.y -= e.dy*a;
    }
    //assert( ((s1.iInitPos+s1.iStep*e.x) - (s2.iInitPos+s2.iStep*e.x))%m == 0 );
    return (e.x < 0 || e.x > std::min(s1.nLives, s2.nLives)/* ? true : false(std::cerr << "fails on " << e.x << " " , false)*/);
}

int main() {
    int nCases;
    std::cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {
        int nSavages;
        std::cin >> nSavages;
        Savage savages[MAX_SAVAGES];
        for(int i=0; i<nSavages; i++) {
            Savage& s = savages[i];
            std::cin >> s.iInitPos >> s.iStep >> s.nLives;
            s.iInitPos--;
        }
        integer m = 1;
        for(int i=0; i<nSavages; i++)
            m = std::max(m, savages[i].iInitPos+1);
        for(; m<=1000000; m++) {
            bool success = true;
            for(int i=0; i<nSavages; i++) {
                for(int j=i+1; j<nSavages; j++) {
                    if (! check(savages[i], savages[j], m)) {
                        //std::cerr << "m=" << m << ": failed on (" << i << ',' << j << ')' << std::endl;
                        success = false;
                        goto DETERMINED;
                    }
                }
            }
        DETERMINED:
            if (success)
                break;
        }
        std::cout << m << std::endl;
    }
    return 0;
}
