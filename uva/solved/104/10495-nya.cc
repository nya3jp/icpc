/*
 * UVA 10495 Conic Distance
 * 2005-07-21
 * by nya
 */

#include <iostream>
#include <complex>
#include <algorithm>
#include <cmath>
#include <cstdio>

const double PI = std::acos(0.0)*2.0;

int main() {
    double r, h, d1, a1, d2, a2;
    while(std::cin >> r >> h >> d1 >> a1 >> d2 >> a2) {
        double th = std::abs(a2 - a1);
        if (th > 180.0)
            th = 360.0 - th;
        double l = std::sqrt(r*r+h*h);
        double rad = PI*r*th/180.0/l;
        double dist = std::abs( std::polar(d1, 0.0) - std::polar(d2, rad) );
        std::printf("%.2f\n", dist);
    }
    return 0;
}
