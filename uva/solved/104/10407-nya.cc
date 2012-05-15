/*
 * UVA 10407 Simple Division
 * 2005-08-08
 * by nya
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

unsigned long long int gcd(unsigned long long int n, unsigned long long int m) {
    unsigned long long int r;
    while( (r = n%m) != 0 ) {
        n = m;
        m = r;
    }
    return m;
}

unsigned long long int dist(long long int n, long long int m) {
    if (n < m)
        std::swap(n, m);
    return (unsigned long long int)(n - m);
}

int main() {
    long long int base;
    while(std::scanf("%Ld", &base), base != 0) {
        unsigned long long int g;
        long long int n;
        std::scanf("%Ld", &n);
        g = dist(n, base);
        while(std::scanf("%Ld", &n), n != 0) {
            if (n != base)
                g = gcd(g, dist(n, base));
        }
        std::printf("%Lu\n", g);
    }
    return 0;
}
