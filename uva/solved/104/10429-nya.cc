/*
 * UVA 10429 Mohr's Circle
 * 2005-08-08
 * by nya
 */

#include <iostream>
#include <cstdio>
#include <complex>
#include <string>
#include <cmath>

typedef std::complex<double> C;

const double PI = std::acos(0.0)*2;

int main() {
    double sx, sy, t;
    int iCase = 0;
    while(std::cin >> sx >> sy >> t) {
        if (t != 0) {
            std::string s;
            std::cin >> s;
            if (s == "CCW")
                t = -t;
        }
        C a(sx, t);
        C b(sy, -t);
        C c( (sx+sy)/2, 0.0 );
        double r = std::abs(a-c);

        double maxnsang = std::abs(std::arg(a-c)) / 2;
        double maxnsabs = c.real()+r;
        double minnsabs = c.real()-r;
        double maxssang = maxnsang + PI/4;
        double maxssabs = r;
        double norms = c.real();

        if (iCase > 0)
            std::printf("\n");

        std::printf("Element : %d\n"
                    "Position of maximum normal stresses : %.2f deg\n"
                    "Maximum normal stresses : %.2f MPa and %.2f MPa\n"
                    "\n"
                    "Position of maximum shear stresses : %.2f deg\n"
                    "Maximum shear stress (xy plane) : %.2f MPa\n"
                    "Normal stress at this condition : %.2f MPa\n",
                    ++iCase,
                    maxnsang * 180.0 / PI,
                    maxnsabs,
                    minnsabs,
                    maxssang * 180.0 / PI,
                    maxssabs,
                    norms);
    }
    return 0;
}




