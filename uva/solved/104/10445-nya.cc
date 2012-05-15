/*
 * UVA 10445 Make Polygon
 * 2005-08-08
 * by nya
 */

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

typedef long double decimal;

const decimal PI = std::acos((decimal)0)*2;
const decimal EP = 1.0e-8;

struct Point2D {
    int x, y;
    Point2D(int x=0, int y=0) : x(x), y(y) {
    }
};

int operator%(const Point2D& a, const Point2D& b) {
    return (a.x*b.y - a.y*b.x);
}

int double_area_with_sign(const std::vector<Point2D>& points) {
    int s = 0;
    for(int i=0; i<(int)points.size(); i++) {
        int j = (i + 1)%(int)points.size();
        s += points[i] % points[j];
    }
    return s;
}

bool counterclockwise(const std::vector<Point2D>& points) {
    return (double_area_with_sign(points) > 0);
}


int main() {
    int n;
    while(std::scanf("%d", &n) == 1 && n >= 3) {
        std::vector<Point2D> points(n);
        for(int i=0; i<n; i++) {
            std::scanf("%d%d", &points[i].x, &points[i].y);
        }
        if (! counterclockwise(points))
            std::reverse(points.begin(), points.end());
        points.push_back(points[0]);
        points.push_back(points[1]);
        decimal max_angle = 0;
        decimal min_angle = 360;
        for(int i=0; i<n; i++) {
            Point2D p(points[i].x-points[i+1].x, points[i].y-points[i+1].y);
            Point2D q(points[i+2].x-points[i+1].x, points[i+2].y-points[i+1].y);
            decimal angle = std::atan2((decimal)p.y, (decimal)p.x) - std::atan2((decimal)q.y, (decimal)q.x);
            angle = angle * 180 / PI;

            while(angle < 0-EP) angle += 360;
            while(angle > 360+EP) angle -= 360;
            if (angle < 0) angle = 0;
            min_angle = std::min(min_angle, angle);
            max_angle = std::max(max_angle, angle);
        }
        std::printf("%.6Lf %.6Lf\n", min_angle, max_angle);
    }
    return 0;
}
