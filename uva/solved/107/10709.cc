/**
 * @file
 * 幾何:基礎 (geom-basic)
 *
 * @author qoo
 * @date   2006/02/01
 */

#include <complex>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define EP 1.0e-8

#define EQ(a,b) (abs((a)-(b)) < EP)
#define NE(a,b) (!EQ(a,b))
#define GE(a,b) ((a) > (b) - EP)
#define LE(a,b) ((a) < (b) + EP)
#define GR(a,b) ((a) > (b) + EP)
#define LS(a,b) ((a) < (b) - EP)

/// 点
typedef complex<double> Point;

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

    /// 平行移動
    friend Line operator+(const Line& l, const Point& p) {
        return Line(l.pos+p, l.dir);
    }
    /// 平行移動
    friend Line operator-(const Line& l, const Point& p) {
        return Line(l.pos-p, l.dir);
    }

    /// ax+by+c = 0なる式が表す直線を生成する
    static Line make_line_eq(double a, double b, double c) {
        return Line((NE(a, 0) ? Point(-c/a, 0) : Point(0, -c/b)), Point(b, -a));
    }
};

/// 長方形
struct Rect {
    Point lb, rt;

    Rect() {
    }
    Rect(const Point& lb, const Point& rt)
        : lb(lb), rt(rt) {
    }
    Rect(double left, double bottom, double right, double top)
        : lb(left, bottom), rt(right, top) {
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

/// 内積を求める
double inp(const Point& a, const Point& b) {
    return (conj(a)*b).real();
}
/// 外積を求める
double outp(const Point& a, const Point& b) {
    return (conj(a)*b).imag();
}

/// 射影ベクトルを求める
/**
 * \param[in] p 射影元のベクトル
 * \param[in] b 射影先のベクトル
 */
Point proj(const Point& p, const Point& b) {
    return b*inp(p,b)/norm(b);
}
/// 点から直線に対して引いた垂線の足を求める
Point perf(const Line& l, const Point& p) {
    const Line m = l - p;
    return (p + (m.pos - proj(m.pos, m.dir)));
}
/// 線分を直線に射影した線分を求める
/**
 * \param[in] s 射影元の線分
 * \param[in] b 射影先の直線
 */
Line proj(const Line& s, const Line& b) {
    return Line(perf(b, s.pos), proj(s.dir, b.dir));
}

/// 回転の方向を調べる
int ccw(const Point& p, const Point& r, const Point& s) {
    Point a(r-p), b(s-p);
    double op = outp(a, b);
    if (LS(op, 0)) return -1;
    if (GR(op, 0)) return 1;
    if (LS(a.real()*b.real(), 0) || LS(a.imag()*b.imag(), 0))
        return -1;
    if (LS(norm(a), norm(b)))
        return 1;
    return 0;
}


/// 直線がx軸正方向となす角度のようなもの
/**
 * \return 直線がx軸正方向となす角についてatanと同じ順序を持つ0から360までの値
 */
double psuedo_theta(const Line& l) {
    double dx, dy, ax, ay;
    dx = l.dir.real(); ax = abs(dx);
    dy = l.dir.imag(); ay = abs(dy);
    double t = (EQ(ax+ay, 0) ? 0 : (double)dy/(ax+ay));
    if (dx < 0) t = 2-t; else if (dy < 0) t = 4+t;
    return t*90;
}

/// 直線表現の正規化を行う
Line normalize_line(const Line& l) {
    Line n(perf(l, Point(0, 0)), l.dir/abs(l.dir));
    if (n.dir.imag() < 0)
        n.dir = -n.dir;
    return n;
}

///////////////////////////////////////////////* geom-basic end */

///////////////////////////////////////////////* intersection */

/// 直線と線分が交差するか調べる
bool ls_intersects(const Line& l, const Line& s) {
    return ( ccw(l.pos, l.pos+l.dir, s.pos)
             *ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0 );
}
/// 線分同士が交差するか調べる
bool ss_intersects(const Line& s, const Line& t) {
    return (ls_intersects(s, t) &&
            ls_intersects(t, s));
}

/// 直線同士が一致するか調べる
bool line_equals(const Line& l, const Line& m) {
    Line a = normalize_line(l);
    Line b = normalize_line(m);
    return (EQ(abs(a.pos-b.pos), 0) && EQ(abs(a.dir-b.dir), 0));
}

/// 長方形同士が交差するか調べる
bool rect_intersects(const Rect& r, const Rect& s) {
    Point a = s.rt - r.lb;
    Point b = r.rt - s.lb;
    return !(LS(a.real(), 0) || LS(a.imag(), 0) ||
             LS(b.real(), 0) || LS(b.imag(), 0));
}


///////////////////////////////////////////////* distance */


/// 点と点の距離
double pp_distance(const Point& a, const Point& b) {
    return abs(a-b);
}
/// 直線と点の距離
double lp_distance(const Line& l, const Point& p) {
    return pp_distance(perf(l, p), p);
}
/// 線分と点の距離
double sp_distance(const Line& s, const Point& p) {
    const Point r = perf(s, p);
    const double pos = ((r-s.pos)/s.dir).real();
    if (LE(0, pos) && LE(pos, 1))
        return lp_distance(s, p);
    return min(pp_distance(s.pos, p),
               pp_distance(s.pos+s.dir, p));
}
/// 線分と線分の距離
double ss_distance(const Line& s, const Line& t) {
    if (ss_intersects(s, t))
        return 0;
    return min(sp_distance(s, t.pos),
           min(sp_distance(s, t.pos+t.dir),
           min(sp_distance(t, s.pos),
               sp_distance(t, s.pos+s.dir))));
}
/// 直線と線分の距離
double ls_distance(const Line& l, const Line& s) {
    if (ls_intersects(l, s))
        return 0;
    return min(lp_distance(l, s.pos),
               lp_distance(l, s.pos+s.dir));
}
///直線と直線の距離
double ll_distance(const Line& l, const Line& m) {
    Line a = normalize_line(l);
    Line b = normalize_line(m);
    if (NE(abs(a.dir-b.dir), 0))
        return 0;
    return pp_distance(a.pos/a.dir, b.pos/b.dir);
}




int main() {
    while(true) {
        double x1, y1, x2, y2;
        string s, s1, s2;
        Point p1, p2;
        Line l1, l2;
        cin >> x1 >> y1 >> x2 >> y2 >> s;
        p1 = Point(x1, y1); p2 = Point(x2, y2);
        l1 = Line(p1, p2-p1); s1 = s;
        cin >> x1 >> y1 >> x2 >> y2 >> s;
        p1 = Point(x1, y1); p2 = Point(x2, y2);
        l2 = Line(p1, p2-p1); s2 = s;
        double d;
        if (s1 == "L" && s2 == "L") {
            d = ll_distance(l1, l2);
        }
        if (s1 == "L" && s2 == "LS") {
            d = ls_distance(l1, l2);
        }
        if (s1 == "LS" && s2 == "L") {
            d = ls_distance(l2, l1);
        }
        if (s1 == "LS" && s2 == "LS") {
            d = ss_distance(l1, l2);
        }
        if (s1 == "END" && s2 == "END") {
            break;
        }
        printf("%.5f\n", d);
    }
    return 0;
}


