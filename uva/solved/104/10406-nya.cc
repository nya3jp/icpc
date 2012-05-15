/*
 * UVA 10406 Cutting Tabletops
 * 2005-08-08
 * by nya
 */

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <cstdio>
#include <algorithm>


typedef long double decimal;

struct Point2D {
    decimal x, y;
    Point2D(decimal x=0, decimal y=0) : x(x), y(y) {
    }
    decimal norm() const {
        return (x*x + y*y);
    }
    decimal abs() const {
        return std::sqrt(x*x + y*y);
    }
    Point2D normalize() const {
        return (*this)/abs();
    }
    friend Point2D operator+(const Point2D& a, const Point2D& b) {
        return Point2D(a.x+b.x, a.y+b.y);
    }
    friend Point2D operator-(const Point2D& a, const Point2D& b) {
        return Point2D(a.x-b.x, a.y-b.y);
    }
    friend decimal operator*(const Point2D& a, const Point2D& b) {
        return (a.x * b.x + a.y * b.y);
    }
    friend decimal operator%(const Point2D& a, const Point2D& b) {
        return (a.x * b.y - a.y * b.x);
    }
    friend Point2D operator*(const Point2D& a, decimal d) {
        return Point2D(a.x*d, a.y*d);
    }
    friend Point2D operator/(const Point2D& a, decimal d) {
        return Point2D(a.x/d, a.y/d);
    }
};

Point2D cut(Point2D org, Point2D first, Point2D second, decimal l) {
    Point2D a = first - org;
    Point2D b = second - org;
    Point2D e = a.normalize();
    Point2D f = b.normalize();

    Point2D x = e+f;
    decimal g = e*f;

    decimal r = l / std::sqrt(1 - g*g);

    Point2D p = x*r;
    Point2D q = p*(-1);

    Point2D z = (p%b > 0 ? p : q);
    return (z + org);
}

decimal area(const std::vector<Point2D>& points) {
    decimal s = 0;
    int nPoints = points.size();
    for(int i=0; i<nPoints; i++) {
        s += (points[i] % points[(i+1)%nPoints]) * 0.5;
    }
    return std::abs(s);
}

int main() {

    decimal dCut;
    int nPoints;
    while(std::cin >> dCut >> nPoints && nPoints != 0) {

        std::vector<Point2D> points(nPoints);
        for(int i=0; i<nPoints; i++) {
            Point2D& p = points[i];
            std::cin >> p.x >> p.y;
        }
        points.push_back(points[0]);
        points.push_back(points[1]);

        std::vector<Point2D> newpoints;

        for(int i=0; i<nPoints; i++) {
            newpoints.push_back( cut(points[i+1], points[i], points[i+2], dCut) );
        }

/*
        std::cerr << "Cut = " << dCut << std::endl;
        for(int i=0; i<nPoints; i++) {
            const Point2D& p = newpoints[i];
            std::cerr << "(" << p.x << "," << p.y << ")" << std::endl;
        }
*/
        //std::cerr << "---" << std::endl;
        std::printf("%.03f\n", (double)area(newpoints));
        //std::cerr << "---" << std::endl;

    }

    return 0;
}








