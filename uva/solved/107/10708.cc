/**
 * @file
 * 幾何
 *
 * @author qoo
 * @date   2006/02
 */

#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#include <list>
#include <utility>

using namespace std;


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// double
////////////////////////////////////////////////////////////////////////////////


/// 許容誤差
#define EP 1.0e-8
/// 誤差つき符号関数 [VERIFIED]
inline int SGN(double a) { return abs(a) < EP ? 0 : a > 0 ? 1 : -1; }
#define EQ(a,b) (SGN((a)-(b)) == 0)    ///< equal
#define NE(a,b) (SGN((a)-(b)) != 0)    ///< not equal
#define GE(a,b) (SGN((a)-(b)) >= 0)    ///< greater or equal
#define LE(a,b) (SGN((a)-(b)) <= 0)    ///< less or equal
#define GR(a,b) (SGN((a)-(b)) > 0)     ///< greater
#define LS(a,b) (SGN((a)-(b)) < 0)     ///< less
#define PS(a)   (SGN(a) > 0)           ///< positive
#define NG(a)   (SGN(a) < 0)           ///< negative
#define ZR(a)   (SGN(a) == 0)          ///< zero
#define NZ(a)   (SGN(a) != 0)          ///< nonzero



////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// geom-basic
////////////////////////////////////////////////////////////////////////////////


/// 点
typedef complex<double> Point;

/// Pointの比較演算子 [VERIFIED]
namespace std {
    inline bool operator<(const Point& a, const Point& b) {
        if (NE(a.real(), b.real()))
            return LS(a.real(), b.real());
        return LS(a.imag(), b.imag());
    }
}


/// 多角形
typedef vector<Point> Polygon;

/// 虚数単位
const Point I(0, 1);



/// 直線もしくは線分
/**
 * posとpos+dirを結ぶ線分、またはそれを延長した直線を表す。
 */
struct Line {
    Point pos, dir;

    Line() {
    }
    Line(const Point& pos, const Point& dir)
        : pos(pos), dir(dir) {
    }


    /// ax+by+c = 0なる式が表す直線を生成する
    static Line make_line_eq(double a, double b, double c) {
        return Line((NZ(a) ? Point(-c/a, 0) : Point(0, -c/b)), Point(b, -a));
    }
};


/// 長方形
struct Rect {
    Point lb, rt; /* LeftBottom, RightTop */

    Rect()
        : lb(0, 0), rt(0, 0) {
        validate();
    }
    Rect(const Point& lb, const Point& rt)
        : lb(lb), rt(rt) {
        validate();
    }
    Rect(double left, double bottom, double right, double top)
        : lb(left, bottom), rt(right, top) {
        validate();
    }
    void validate() {
        Point sz = rt - lb;
        assert(sz.real() >= 0 && sz.imag() >= 0);
    }
};


/// 三角形
struct Triangle {
    Point a, b, c;

    Triangle() {
    }
    Triangle(const Point& a, const Point& b, const Point& c)
        : a(a), b(b), c(c) {
    }
};




/// 内積を求める [VERIFIED]
double inp(const Point& a, const Point& b) {
    return (conj(a)*b).real();
}

/// 外積を求める [VERIFIED]
double outp(const Point& a, const Point& b) {
    return (conj(a)*b).imag();
}


/// 射影ベクトルを求める [VERIFIED]
/**
 * \param[in] p 射影元のベクトル
 * \param[in] b 射影先のベクトル
 */
Point proj(const Point& p, const Point& b) {
    return b*inp(p,b)/norm(b);
}

/// 点から直線に対して引いた垂線の足を求める [VERIFIED]
Point perf(const Line& l, const Point& p) {
    const Line m(l.pos - p, l.dir);
    return (p + (m.pos - proj(m.pos, m.dir)));
}

/// 線分を直線に射影した線分を求める [VERIFIED]
/**
 * \param[in] s 射影元の線分
 * \param[in] b 射影先の直線
 */
Line proj(const Line& s, const Line& b) {
    return Line(perf(b, s.pos), proj(s.dir, b.dir));
}



/// 回転の方向を調べる(Sedgewickのおせっかい版) [VERIFIED]
int ccw(const Point& p, const Point& r, const Point& s) {
    Point a(r-p), b(s-p);
    double op = outp(a, b);
    if (SGN(op) != 0)
        return SGN(op);
    if (NG(a.real()*b.real()) || NG(a.imag()*b.imag()))
        return -1;
    if (LS(norm(a), norm(b)))
        return 1;
    return 0;
}

/// 回転の方向を調べる
int rot(const Point& p, const Point& r, const Point& s) {
    return SGN(outp(r-p, s-p));
}



/// 直線表現の正規化を行う [VERIFIED]
Line normalize_line(const Line& l) {
    return Line(perf(l, Point(0, 0)),
                (l.dir.imag() < 0 ? -l.dir : l.dir)/abs(l.dir));
}



////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// intersection
////////////////////////////////////////////////////////////////////////////////


/// 直線同士が平行かどうか調べる
bool line_parallel(const Line& l, const Line& m) {
    Line a = normalize_line(l);
    Line b = normalize_line(m);
    return ZR(abs(a.dir-b.dir));
}

/// 直線同士が一致するか調べる
bool line_equals(const Line& l, const Line& m) {
    Line a = normalize_line(l);
    Line b = normalize_line(m);
    return (ZR(abs(a.pos-b.pos)) && ZR(abs(a.dir-b.dir)));
}

/// 直線と線分が重なるか調べる
bool ls_overlaps(const Line& l, const Line& s) {
    return ( ccw(l.pos, l.pos+l.dir, s.pos)
             *ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0 );
}

/// 線分同士が重なるか調べる
bool ss_overlaps(const Line& s, const Line& t) {
    return (ls_overlaps(s, t) && ls_overlaps(t, s));
}

/// 直線同士が重なるか調べる
bool ll_overlaps(const Line& l, const Line& m) {
    return (!line_parallel(l, m) || line_equals(l, m));
}

/// 直線と線分が交差するか調べる
bool ls_intersects(const Line& l, const Line& s) {
    int a = rot(l.pos, l.pos+l.dir, s.pos);
    int b = rot(l.pos, l.pos+l.dir, s.pos+s.dir);
    return (a*b <= 0 && a-b != 0);
}

/// 線分同士が交差するか調べる
bool ss_intersects(const Line& l, const Line& m) {
    return (ls_intersects(l, m) && ls_intersects(m, l));
}

/// 線分同士が交差するか調べる
bool ll_intersects(const Line& l, const Line& m) {
    return (ls_intersects(l, m) && ls_intersects(m, l));
}

/// 直線同士の交点を求める
Point ll_intersection(const Line& l, const Line& m) {
    double t = outp(m.pos-l.pos, m.dir) / outp(l.dir, m.dir);
    return (l.pos + t*l.dir);
}


/// 長方形同士が交差するか調べる
bool rect_intersects(const Rect& r, const Rect& s) {
    Point a = s.rt - r.lb;
    Point b = r.rt - s.lb;
    return !(NG(a.real()) || NG(a.imag()) ||
             NG(b.real()) || NG(b.imag()) );
}



////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// distance
////////////////////////////////////////////////////////////////////////////////


/// 点と点の距離 [VERIFIED]
double pp_distance(const Point& a, const Point& b) {
    return abs(a-b);
}

/// 直線と点の距離 [VERIFIED]
double lp_distance(const Line& l, const Point& p) {
    return pp_distance(perf(l, p), p);
}

/// 線分と点の距離 [VERIFIED]
double sp_distance(const Line& s, const Point& p) {
    const Point r = perf(s, p);
    const double pos = ((r-s.pos)/s.dir).real();
    if (LE(0, pos) && LE(pos, 1))
        return lp_distance(s, p);
    return min(pp_distance(s.pos, p),
               pp_distance(s.pos+s.dir, p));
}

/// 線分と線分の距離 [VERIFIED]
double ss_distance(const Line& s, const Line& t) {
    if (ss_intersects(s, t))
        return 0;
    return min(sp_distance(s, t.pos),
           min(sp_distance(s, t.pos+t.dir),
           min(sp_distance(t, s.pos),
               sp_distance(t, s.pos+s.dir))));
}

/// 直線と線分の距離 [VERIFIED]
double ls_distance(const Line& l, const Line& s) {
    if (ls_intersects(l, s))
        return 0;
    return min(lp_distance(l, s.pos),
               lp_distance(l, s.pos+s.dir));
}

///直線と直線の距離 [VERIFIED]
double ll_distance(const Line& l, const Line& m) {
    Line a = normalize_line(l);
    Line b = normalize_line(m);
    if (NZ(abs(a.dir-b.dir)))
        return 0;
    return pp_distance(a.pos/a.dir, b.pos/b.dir);
}



////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// polygon
////////////////////////////////////////////////////////////////////////////////


/// 多角形の符号付面積を求める
double signed_area(const Polygon& polygon) {
    int n = polygon.size();
    double s = 0.0;
    for(int i = 0; i < n; i++) {
        s += outp(polygon[i], polygon[(i+1)%n]);
    }
    return s/2;
}
/// 多角形の面積を求める
double area(const Polygon& polygon) {
    return abs(signed_area(polygon));
}

/// 多角形の回転方向を調べる
bool polygon_ccw(const Polygon& polygon) {
    return PS(signed_area(polygon));
}


/// 三角形が点を含むか調べる
bool triangle_contains_point(const Triangle& t, const Point& p, bool inclusive) {
    int a = rot(t.a, t.b, p);
    int b = rot(t.b, t.c, p);
    int c = rot(t.c, t.a, p);
    return (a*b >= 0 && b*c >= 0 && c*a >= 0 && (inclusive || a*b*c != 0));
}

/// 多角形を三角形に分解する
/**
 * 
 * \param[out] triangles 分解後の三角形の配列
 * \param[in] polygon 分解前の多角形
 */
void triangle_decompose(vector<Triangle>& triangles, const Polygon& polygon) {
    triangles.clear();

    list<Point> lst(polygon.begin(), polygon.end());

    while(lst.size() >= 3) {
        list<Point>::iterator it1, it2, it3;
        it1 = lst.begin();
        it2 = it1; ++it2;
        it3 = it2; ++it3;
        while(true) {
            assert(it3 != lst.end());
            if (PS(outp(*it2-*it1, *it3-*it1))) {
                Triangle tr(*it1, *it2, *it3);
                list<Point>::iterator it;
                for(it = lst.begin(); it != lst.end(); ++it) {
                    if (triangle_contains_point(tr, *it, false))
                        break;
                }
                if (it != lst.end()) {
                    triangles.push_back(tr);
                    lst.erase(it2);
                    break;
                }
            }
            ++it1, ++it2, ++it3;
        }
    }
}

/// 多角形が点を含むか調べる
double polygon_contains_point(const Polygon& polygon, const Point& pt) {
    vector<Triangle> triangles;
    triangle_decompose(triangles, polygon);
    for(int i = 0; i < (int)triangles.size(); i++) {
        if (triangle_contains_point(triangles[i], pt, true))
            return true;
    }
    return false;
}

/// 凸多角形が点を含むか調べる
double convex_polygon_contains_point(const Polygon& polygon, const Point& pt) {
    int n = polygon.size();
    int sign = 0;
    for(int i = 0; i < n; i++) {
        int j = (i+1)%n;
        int s = SGN(outp(polygon[j]-polygon[i], pt-polygon[i]));
        if (sign*s < 0)
            return false;
        if (s == 0 && ccw(polygon[i], polygon[j], pt) == 0)
            return true;
        sign += s;
    }
    return true;
}


/// Graham Scanに用いるcomparator [VERIFIED]
// Thanks to IHI
struct polar_less {
    polar_less(const Point& pivot)
        : pivot(pivot) {
    }
    bool operator()(const Point& a, const Point& b) {
        Point z = (a - pivot)/(b - pivot);
        if (NZ(arg(z)))
            return (arg(z) < 0);
        return (abs(z) < 1);
    }
    Point pivot;
};

/// 凸包を求める [VERIFIED]
/**
 * \param[out] polygon 凸包である多角形
 * \param[in] vertices 点の配列
 */
// Thanks to IHI
void convex_hull(Polygon& polygon, const Polygon& vertices) {
    const int n = vertices.size();
    assert(n >= 3);

    polygon = vertices;
    swap(polygon[0], *min_element(polygon.begin(), polygon.end()));
    Point pivot = polygon[0];

    sort(polygon.begin()+1, polygon.end(), polar_less(pivot));

    {
        int tail = n - 1;
        while(tail > 1 &&
              EQ(arg(polygon[tail-1] - pivot),
                 arg(polygon[n-1] - pivot)))
            tail--;
        reverse(polygon.begin()+tail, polygon.end());
    }

    int m = 3;
    for(int i = 3; i < n; i++) {
        Point pt = polygon[i];
        while(ccw(polygon[m-2], polygon[m-1], pt) <= 0)
            m--;
        polygon[m++] = pt;
    }
    polygon.resize(m);
}






#include <cstdio>
#include <iostream>

const double PI = acos(0.0)*2;

struct not_found {};

int main() {
    int n;
    cin >> n;
    for(int ic = 0; ic < n; ic++) {
        double cx, cy, px, py, p, u, v, l;
        cin >> cx >> cy >> px >> py >> p >> u >> v >> l;
        p *= PI/180;

        try {
            Point C(cx, cy);
            Point P(px, py);
            
            Point d = P - C;
            Point b = polar(u, p);
            double th = arg(d) - asin(outp(b, d) / (v * abs(d)));
            Point a;
            Point a1 = polar(v, th);
            Point a2 = polar(v, PI/2 - th);
            if ( (d/(a1-b)).real() >= 0)
                a = a1;
            else if ( (d/(a2-b)).real() >= 0)
                a = a2;
            else
                throw not_found();

            double c = arg(a);
            double t = (d/(a-b)).real();
            Point x = C + a*t;

            if (c < 0)
                c += 2*PI;

            if (LE(t, l)) {
                printf("%.2f %.2f %.2f %.2f\n",
                       c * 180/PI,
                       t,
                       x.real(),
                       x.imag());
            }
            else
                throw not_found();
        }
        catch(not_found) {
            printf("sorry, buddy\n");
        }

    }
    return 0;
}

