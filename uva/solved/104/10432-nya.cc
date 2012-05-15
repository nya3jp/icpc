/*
 * UVA 10432 Polygon Inside A Circle
 * 2005-08-14
 * by nya
 */

#include <cstdio>
#include <cmath>

const double PI = std::acos(0.0)*2;

int main() {
    double r;
    int n;
    while(std::scanf("%lf%d", &r, &n) == 2) {
        double x = 2*PI/n;
        double s = std::sin(x)*r*r/2 * n;
        std::printf("%.3lf\n", s);
    }
    return 0;
}
