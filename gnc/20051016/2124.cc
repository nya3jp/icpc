#include <cstdio>
#include <cmath>
#include <vector>
#include <utility>
#include <cassert>

struct Point {
    double x, y;
    Point(double x=0, double y=0)
        : x(x), y(y) {
    }
};


int main() {
    int nPlates;
    std::scanf("%d", &nPlates);
    std::vector< std::pair<Point, double> > points(nPlates);
    for(int iPlate=0; iPlate<nPlates; iPlate++) {
        int nVertices;
        std::scanf("%d", &nVertices);
        std::vector<Point> shape(nVertices);
        for(int iVertice=0; iVertice<nVertices; iVertice++) {
            Point& pt = shape[iVertice];
            std::scanf("%lf%lf", &pt.x, &pt.y);
        }
        Point ptsum(0.0, 0.0);
        double dArea = 0.0;
        for(int iVertice=0; iVertice<nVertices; iVertice++) {
            const Point& pt = shape[iVertice];
            const Point& ps = shape[(iVertice+1)%nVertices];
            ptsum.x += pt.x;
            ptsum.y += pt.y;
            dArea += (ps.x*pt.y-ps.y*pt.x)/2;
        }
        dArea = std::abs(dArea);
        ptsum.x /= nVertices;
        ptsum.y /= nVertices;
        points[iPlate] = std::make_pair(ptsum, dArea);
    }

    /*
    for(int i=0; i<nPlates; i++) {
        std::printf("(%Lf,%Lf) %Lf\n", points[i].first.x, points[i].first.y, points[i].second);
    }
    */

    {
        Point ptsum(0.0, 0.0);
        double dTotalWeight = 0.0;
        for(int i=0; i<nPlates; i++) {
            ptsum.x += points[i].first.x * points[i].second;
            ptsum.y += points[i].first.y * points[i].second;
            dTotalWeight += points[i].second;
        }
        ptsum.x /= dTotalWeight;
        ptsum.y /= dTotalWeight;
        std::printf("%.4lf %.4lf\n", ptsum.x, ptsum.y);
    }
    return 0;
}



