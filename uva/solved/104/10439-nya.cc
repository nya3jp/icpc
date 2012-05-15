/*
 * UVA 10439 Temple of Dune
 * 2005-07-19
 * by nya
 */

#include <iostream>
#include <complex>
#include <cmath>

const double PI = 2.0*std::acos((double)0.0);
const double PI2 = 2.0*PI;
const double EP = 1.0e-3;

typedef std::complex<double> dcomplex;

inline bool EQ(double x, double y) {
    return ( std::abs(x-y) < EP );
}

int main() {
    int m;
    std::cin >> m;
    while(m-- > 0) {
        double x1, y1, x2, y2, x3, y3;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        dcomplex a(x1, y1);
        dcomplex b(x2, y2);
        dcomplex c(x3, y3);
        double d2 = std::norm(a-b);
        for(int n=3; n<=200; n++) {
            for(int i=1; i<n; i++) {
                double r = std::sqrt( d2 / (2*(1-std::cos(PI2*i/n))) );
                dcomplex rt = std::polar( 1.0, PI2*i/n );
                dcomplex o = (b - a*rt)/(dcomplex(1,0) - rt);
                double cr = std::abs(c-o);
                double ci = std::arg((c-o)/(a-o))*n/PI2;
                /*
                std::cout << "----------" << std::endl
                          << "(n,i) = " << std::complex<int>(n,i) << std::endl
                          << "d2 = " << d2 << std::endl
                          << "r = " << r << std::endl
                          << "rt = " << rt << std::endl
                          << "o = " << o << std::endl
                          << "cr = " << cr << std::endl
                          << "ci = " << ci << std::endl
                          << "round(ci) = " << round(ci) << std::endl;
                */
                if (ci < 0.0)
                    ci *= -1.0;
                if (EQ(cr, r) && EQ((double)(int)(ci+0.5), ci)) {
                    std::cout << n << std::endl;
                    goto FOUND;
                }
            }
        }
        std::cout << "Error: not found" << std::endl;
    FOUND:;
    }
    return 0;
}
