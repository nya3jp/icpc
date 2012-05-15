/*
 * UVA 10456 Intelligent Cats
 * 2005-09-26
 * by nya
 */

#define NDEBUG
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cassert>

typedef long long int integer;

struct Point {
    integer x, y;
    Point(integer x=0, integer y=0)
        : x(x), y(y) {
    }
};

inline integer abs(integer n) {
    return (n < 0 ? -n : n);
}
inline integer gcd(integer n, integer m) {
    integer r;
    while( (r = n%m) != 0 ) {
        n = m;
        m = r;
    }
    return m;
}

struct Frac {
    integer num, denom;
    Frac(int num=0, int denom=1)
        : num(num), denom(denom) {
    }
    void normalize() {
        assert(denom != 0);
        if (denom < 0) {
            denom = -denom;
            num = -num;
        }
        if (num == 0) {
            denom = 1;
        }
        else {
            int g = gcd(abs(num), denom);
            num /= g;
            denom /= g;
        }
    }
};





void solve(const std::vector<Point>& _points, Point pt) {
    int nPoints = _points.size();
    std::vector<Point> points(_points);
    {
        for(int iPoint=0; iPoint<nPoints; iPoint++) {
            points[iPoint].x *= 2;
            points[iPoint].y *= 2;
        }
        pt.x *= 2;
        pt.y *= 2;
    }
    for(int iPoint=0; iPoint<nPoints; iPoint++) {
        const Point& p1 = points[iPoint];
        const Point& p2 = points[(iPoint+1)%nPoints];
        if ((p2.x-p1.x)*(pt.y-p1.y) - (pt.x-p1.x)*(p2.y-p1.y) == 0) {
            std::rotate(points.begin(), points.begin()+iPoint, points.end());
            std::rotate(points.begin(), points.begin()+1, points.end());
            break;
        }
    }
    integer iWholeArea = 0;
    {
        const Point& p0 = points[0];
        for(int iPoint=1; iPoint<nPoints-1; iPoint++) {
            const Point& p1 = points[iPoint];
            const Point& p2 = points[iPoint+1];
            integer iDelta = (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
            iWholeArea += iDelta;
        }
#ifndef NDEBUG
        std::printf("iWholeArea = %lld\n", iWholeArea);
#endif
    }
    {
        integer iArea = 0;
        for(int iPoint=0; iPoint<nPoints-1; iPoint++) {
            const Point& p1 = points[iPoint];
            const Point& p2 = points[iPoint+1];
            integer iDelta = (p1.x-pt.x)*(p2.y-pt.y) - (p1.y-pt.y)*(p2.x-pt.x);
            iArea += iDelta;
#ifndef NDEBUG
            std::printf("iPoint = %d : (%lld,%lld) - (%lld,%lld) - (%lld,%lld) : iArea = %lld\n",
                        iPoint,
                        pt.x/2, pt.y/2,
                        p1.x/2, p1.y/2,
                        p2.x/2, p2.y/2,
                        iArea);
#endif
            if (iArea >= iWholeArea/2) {
                iArea -= iDelta;
                integer iTargetDelta = (iWholeArea/2 - iArea);
                Frac t(iTargetDelta, (p1.x-pt.x)*(p2.y-p1.y) - (p1.y-pt.y)*(p2.x-p1.x));
                t.normalize();
                Frac x(t);
                x.num *= (p2.x-p1.x);
                x.num += p1.x*x.denom;
                x.denom *= 2;
                x.normalize();
                Frac y(t);
                y.num *= (p2.y-p1.y);
                y.num += p1.y*y.denom;
                y.denom *= 2;
                y.normalize();
                std::printf("(%lld/%lld),(%lld/%lld)\n",
                            x.num, x.denom, y.num, y.denom);
                break;
            }
        }
    }
}



int main() {
    int nPoints;
    while(std::cin >> nPoints) {
        std::vector<Point> points(nPoints);
        for(int i=0; i<nPoints; i++) {
            std::cin >> points[i].x >> points[i].y;
        }
        int nQueries;
        std::cin >> nQueries;
        for(int iQuery=0; iQuery<nQueries; iQuery++) {
            Point pt;
            std::cin >> pt.x >> pt.y;
            solve(points, pt);
        }
    }
    return 0;
}
