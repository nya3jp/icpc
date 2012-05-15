/*
 * UVA 10451 Ancient Village Sports
 * 2005-08-20
 * by nya
 */

#include <cstdio>
#include <cmath>

const double PI = 2*std::acos(0.0);
const double PI2 = 4*std::acos(0.0);

int main() {
    int iCase = 0;
    int n;
    double s;
    while(std::scanf("%d%lf", &n, &s) == 2 && !(n < 3)) {
        double r = std::sqrt(s * 2 / n / std::sin(PI2 / n));
        double v = r * std::cos(PI2 / n / 2);
        double spc = PI*r*r - s;
        double off = s - PI*v*v;
        std::printf("Case %d: %.5lf %.5lf\n", ++iCase, spc, off);
    }
    return 0;
}
