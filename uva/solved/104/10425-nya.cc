/*
 * UVA 10425 Mobile Destroyer
 * 2005-07-09
 * by nya
 */

#include <iostream>
#include <string>
#include <cmath>

const double EP = 1.0e-10;
inline bool EQ(double a, double b) {
    return (std::abs(a-b) < EP);
}
inline bool LS(double a, double b) {
    return (a < b-EP);
}
inline bool LE(double a, double b) {
    return (a < b+EP);
}


struct Point {
    double x, y, z;

    Point(double x=0,
          double y=0,
          double z=0)
        : x(x), y(y), z(z) {
    }
    inline double norm() const {
        return (x*x+y*y+z*z);
    }
    inline double abs() const {
        return std::sqrt(norm());
    }
};

Point operator+(const Point& a, const Point& b) {
    return Point(a.x+b.x, a.y+b.y, a.z+b.z);
}
Point operator-(const Point& a, const Point& b) {
    return Point(a.x-b.x, a.y-b.y, a.z-b.z);
}
Point operator*(const Point& a, double m) {
    return Point(a.x*m, a.y*m, a.z*m);
}
Point operator/(const Point& a, double m) {
    return Point(a.x/m, a.y/m, a.z/m);
}
double operator*(const Point& a, const Point& b) {
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}
std::istream& operator>>(std::istream& s, Point& p) {
    return (s >> p.x >> p.y >> p.z);
}

int main() {

    while(true) {
        std::string s;
        Point amd1, amd2, mobile;
        double amd1r, amd2r;
        std::cin >> s
                 >> amd1 >> amd1r
                 >> amd2 >> amd2r
                 >> mobile;
        if (! std::cin)
            break;

        bool amd1b, amd2b;
        amd1b = LE((amd1-mobile).abs() , amd1r );
        amd2b = LE((amd2-mobile).abs() , amd2r );

        bool amd0b;
        if (amd1b && amd2b) {
            /*
             * R1^2 - r1^2 = R2^2 - (d-r1)^2
             * -> R1^2 - R2^2 + d^2 = 2 d r1
             * r2 = d - r1
             */
            double r1, r2;
            double d;
            d = (amd1-amd2).abs();
            r1 = (amd1r*amd1r - amd2r*amd2r + d*d)
                / (2 * d);
            r2 = d - r1;
            Point u = (amd2-amd1)/(amd2-amd1).abs();
            Point p1 = amd1 + u*r1;
            Point p2 = amd1 - u*r1;
            Point p;
            p = ( EQ((p1-amd2).abs() , r2) ? p1 : p2);
            amd0b = !EQ( (mobile - p)*u , 0.0 );
        }
        else {
            amd0b = (amd1b || amd2b);
        }

        std::cout << s << std::endl
                  << ( amd1b ? "y" : "n" ) << std::endl
                  << ( amd2b ? "y" : "n" ) << std::endl
                  << ( amd0b ? "y" : "n" ) << std::endl;
    }

    return 0;
}
