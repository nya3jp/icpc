/*
 * UVA 273 Jack Straws
 * 2005-07-03
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

struct Point {
    int x, y;

    Point(int x=0, int y=0) : x(x), y(y) {}
};

struct Line {
    Point p, q;
};

inline Point operator+(const Point& a, const Point& b) {
    return Point(a.x+b.x, a.y+b.y);
}
inline Point operator-(const Point& a, const Point& b) {
    return Point(a.x-b.x, a.y-b.y);
}
inline int operator*(const Point& a, const Point& b) {
    return (a.x*b.x + a.y*b.y);
}
inline int operator%(const Point& a, const Point& b) {
    return (a.x*b.y - b.x*a.y);
}
inline int norm(const Point& p) {
    return p*p;
}
inline double abs(const Point& p) {
    return std::abs((double)norm(p));
}

int ccw(const Point& p, const Point& q, const Point& r) {
    Point d1 = q - p;
    Point d2 = r - p;
    if (d1%d2 > 0) return +1;
    if (d1%d2 < 0) return -1;
    if (d1.x*d2.x < 0 || d1.y*d2.y < 0) return -1;
    if (norm(d1) < norm(d2)) return +1;
    return 0;
}

bool intersects(const Line& a, const Line& b) {
    return ( ccw(a.p, a.q, b.p)*ccw(a.p, a.q, b.q) <= 0 &&
             ccw(b.p, b.q, a.p)*ccw(b.p, b.q, a.q) <= 0);
}


struct unionfinder
{
    std::vector<int> v;
    unionfinder(int n) : v(n, -1) {}

    bool check(int a, int b) {
        return (find_root(a) == find_root(b));
    }
    void unite(int a, int b) {
        int ra = find_root(a);
        int rb = find_root(b);
        if (ra != rb) {
            if (v[ra] > v[rb])
                std::swap(ra, rb);
            v[ra] += v[rb];
            v[rb] = ra;
        }
    }
    int find_root(int a) {
        if (v[a] < 0) return a;
        return (v[a] = find_root(v[a]));
    }
};




int main() {
    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        int nLines;
        std::cin >> nLines;

        std::vector<Line> lines(nLines);
        for(int i=0; i<nLines; i++) {
            Line& l = lines[i];
            std::cin >> l.p.x >> l.p.y >> l.q.x >> l.q.y;
        }

        unionfinder u(nLines);

        for(int i=0; i<nLines; i++) {
            for(int j=i; j<nLines; j++) {
                if (intersects(lines[i], lines[j])) {
                    u.unite(i, j);
                }
            }
        }

        if (iCase > 0)
            std::cout << std::endl;

        int a, b;
        while(std::cin >> a >> b && !(a == 0 && b == 0)) {
            a--; b--;
            if (! u.check(a, b))
                std::cout << "NOT ";
            std::cout << "CONNECTED" << std::endl;
        }

    }

    return 0;
}
