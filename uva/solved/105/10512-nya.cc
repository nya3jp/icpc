/*
 * UVA 10512 A Day in Math-land
 * 2005-09-28
 * by nya
 */

#include <cstdio>
#include <cmath>
#include <utility>

typedef long long int integer;
typedef long double decimal;
const decimal EP = 1.0e-8;

inline bool EQ(decimal x, decimal y) {
    return ( std::abs(x-y) < EP );
}

integer isqrt(decimal n) {
    if (n+EP < 0)
        return 0;
    decimal t = std::sqrt(n);
    integer i = (integer)(t+0.5);
    if (EQ(t, (decimal)i))
        return i;
    return 0;
}

integer isqrt(integer n) {
    return isqrt((decimal)n);
}

inline integer abs(integer n) {
    return (n < 0 ? -n : n);
}

typedef std::pair<integer,integer> Answer;
struct NoSolution {};

bool in_short_range(integer n) {
    return (-32768 <= n && n <= 32767);
}

Answer solve2(integer p, integer q, integer x, integer y) {
    if ( x >= y && (x+y)*y == p && (x-y)*x == q && in_short_range(x) && in_short_range(y) ) {
        return std::make_pair(x, y);
    }
    throw NoSolution();
}

Answer solve1(integer p, integer q, integer lxn) {
    Answer ans;
    bool found = false;
    if (lxn % 4 == 0) {
        integer ax = isqrt(lxn/4);
        if (ax != 0) {
            if (q%ax == 0) {
                try {
                    Answer a = solve2(p, q, ax, ax-q/ax);
                    if (!found || a < ans)
                        ans = a;
                    found = true;
                }
                catch(NoSolution) {}
                try {
                    Answer a = solve2(p, q, -ax, -ax+q/ax);
                    if (!found || a < ans)
                        ans = a;
                    found = true;
                }
                catch(NoSolution) {}
            }
        }
    }
    if (!found)
        throw NoSolution();
    return ans;
}

Answer solve0(integer p, integer q) {
    if (p == 0 && q == 0)
        return std::make_pair(0, 0);

    Answer ans;
    bool found = false;

    if (p == 0 || q == 0) {
        if (p == 0) {
            {
                int x = isqrt(q);
                if (x != 0) {
                    Answer a = std::make_pair(x, 0);
                    if (!found || a < ans)
                        ans = a;
                    found = true;
                }
            }
            if (q%2 == 0) {
                int x = isqrt(q/2);
                if (x != 0) {
                    Answer a = std::make_pair(x, -x);
                    if (!found || a < ans)
                        ans = a;
                    found = true;
                }
            }
        }
        else if (q == 0) {
            {
                int y= isqrt(p);
                if (y != 0) {
                    Answer a = std::make_pair(0, -y);
                    if (!found || a < ans)
                        ans = a;
                    found = true;
                }
            }
            if (p%2 == 0) {
                int y = isqrt(p/2);
                if (y != 0) {
                    Answer a = std::make_pair(-y, -y);
                    if (!found || a < ans)
                        ans = a;
                    found = true;
                }
            }
        }
        if (found)
            return ans;
        throw NoSolution();
    }

    decimal s = (decimal)p*p + (decimal)6*p*q + (decimal)q*q;
    integer sr = isqrt(s); // p == q == 0?
    if (sr != 0) {
        try {
            Answer a = solve1(p, q, p+3*q+sr);
            if (!found || a < ans)
                ans = a;
            found = true;
        }
        catch(NoSolution) {}
        try {
            Answer a = solve1(p, q, p+3*q-sr);
            if (!found || a < ans)
                ans = a;
            found = true;
        }
        catch(NoSolution) {}
    }
    if (!found)
        throw NoSolution();
    return ans;
}

/*
#include <cassert>
int main() {
    for(int i=-1024; i<1024; i++) {
        for(int j=-1024; j<=i; j++) {
            int p = (i+j)*j;
            int q = (i-j)*i;
            Answer ans = solve0(p, q);
            if (!(ans.first == i && ans.second == j) && !(ans < std::make_pair<integer,integer>(i,j))) {
                std::printf("i=%d, j=%d\nx=%lld, y=%lld", i, j, ans.first, ans.second);
                assert(false);
            }
        }
    }
    std::printf("Complete\n");
    return 0;
}
*/

int main() {
    int nCases;
    std::scanf("%d", &nCases);
    for(int iCase=0; iCase<nCases; iCase++) {
        std::printf("Case %d:\n", iCase+1);
        integer p, q;
        std::scanf("%lld%lld", &p, &q);
        try {
            Answer ans = solve0(p, q);
            std::printf("%lld %lld\n", ans.first, ans.second);
        }
        catch(NoSolution) {
            std::printf("Impossible.\n");
        }
    }
    return 0;
}


