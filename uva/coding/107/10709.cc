#include <cstdio>
#include <cstring>

#include <complex>
#include <cmath>
#include <vector>

using namespace std;


// 許容誤差
#define EP 1.0e-8

// 誤差つき符号関数
inline int SGN(double a) { return abs(a) < EP ? 0 : a > 0 ? 1 : -1; }
#define EQ(a,b) (SGN((a)-(b)) == 0)    ///< equal
#define NE(a,b) (SGN((a)-(b)) != 0)    ///< not equal
#define LE(a,b) (SGN((a)-(b)) <= 0)    ///< less or equal
#define LT(a,b) (SGN((a)-(b)) < 0)     ///< less



// 点
typedef complex<double> P;


/*
 * 線分、半直線、直線
 *  posとpos+dirを結ぶ線分、またはそれを延長した直線、半直線を表す。
 */
struct L {
    P pos, dir;

    L() {}
    L(const P& pos, const P& dir) : pos(pos), dir(dir) {}
};


// 内積を求める
inline double inp(const P& a, const P& b) {
    return (conj(a)*b).real();
}

// 外積を求める
inline double outp(const P& a, const P& b) {
    return (conj(a)*b).imag();
}


/* 射影ベクトルを求める
 *  p 射影元のベクトル
 *  b 射影先のベクトル
 */
inline P proj(const P& p, const P& b) {
    return b*inp(p,b)/norm(b);
}

// 点から直線に対して引いた垂線の足を求める
inline P perf(const L& l, const P& p) {
    L m(l.pos - p, l.dir);
    return (p + (m.pos - proj(m.pos, m.dir)));
}


/* 線分を直線に射影した線分を求める
 *  s 射影元の線分
 *  b 射影先の直線
 */
inline L proj(const L& s, const L& b) {
    return L(perf(b, s.pos), proj(s.dir, b.dir));
}



// 回転の方向を調べる(Sedgewickのおせっかい版)
inline int ccw(const P& p, const P& r, const P& s) {
    P a(r-p), b(s-p);
    int sgn = SGN(outp(a, b));
    if (sgn != 0)
        return sgn;
    if (LT(a.real()*b.real(), 0) || LT(a.imag()*b.imag(), 0))
        return -1;
    if (LT(norm(a), norm(b)))
        return 1;
    return 0;
}

// 回転の方向を調べる
inline int rot(const P& p, const P& r, const P& s) {
    return SGN(outp(r-p, s-p));
}


// 直線表現の正規化を行う
L normalize_line(const L& l) {
    return L(perf(l, P(0, 0)),
             ( (LT(l.dir.imag(), 0) ||
                (EQ(l.dir.imag(), 0) && LT(l.dir.real(), 0)) )
               ? -l.dir : l.dir ) / abs(l.dir) );
}



// 直線同士が交差するかどうか調べる
bool ll_intersects(const L& l, const L& m) {
    return NE(abs(normalize_line(l).dir - normalize_line(m).dir), 0);
}

// 直線と線分が交差するか調べる
bool ls_intersects(const L& l, const L& s) {
    return (ccw(l.pos, l.pos+l.dir, s.pos)
            *ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0);
}

// 線分同士が交差するか調べる
bool ss_intersects(const L& s, const L& t) {
    return (ls_intersects(s, t) &&
            ls_intersects(t, s));
}


// 直線同士が平行かどうか調べる
bool line_parallel(const L& l, const L& m) {
    return !ll_intersects(l, m);
}

// 直線同士が一致するか調べる
bool line_equals(const L& l, const L& m) {
    L a = normalize_line(l);
    L b = normalize_line(m);
    return (EQ(abs(a.pos-b.pos), 0) && EQ(abs(a.dir-b.dir), 0));
}

// 直線同士の交点を求める
P line_cross(const L& l, const L& m) {
    double num = outp(m.dir, m.pos-l.pos);
    double denom = outp(m.dir, l.dir);
    if (EQ(denom, 0))
        throw 0; // 共有点が一つではない
    return P(l.pos + l.dir*num/denom);
}



// 点と点の距離
double pp_distance(const P& a, const P& b) {
    return abs(a - b);
}

// 直線と点の距離
double lp_distance(const L& l, const P& p) {
    return abs(perf(l, p) - p);
}

// 線分と点の距離
double sp_distance(const L& s, const P& p) {
    const P r = perf(s, p);
    const double pos = ((r-s.pos)/s.dir).real();
    if (LE(0, pos) && LE(pos, 1))
        return abs(r - p);
    return min(abs(s.pos - p),
               abs(s.pos+s.dir - p));
}

// 線分と線分の距離
double ss_distance(const L& s, const L& t) {
    if (ss_intersects(s, t))
        return 0;
    return min(sp_distance(s, t.pos),
           min(sp_distance(s, t.pos+t.dir),
           min(sp_distance(t, s.pos),
               sp_distance(t, s.pos+s.dir))));
}

// 直線と線分の距離
double ls_distance(const L& l, const L& s) {
    if (ls_intersects(l, s))
        return 0;
    return min(lp_distance(l, s.pos),
               lp_distance(l, s.pos+s.dir));
}

//直線と直線の距離
double ll_distance(const L& l, const L& m) {
    L a = normalize_line(l);
    L b = normalize_line(m);
    if (NE(abs(a.dir-b.dir), 0))
        return 0;
    return abs(a.pos/a.dir - b.pos/b.dir);
}








P readPoint() {
    double x, y;
    scanf("%lf%lf", &x, &y);
    return P(x, y);
}

L readLine() {
    P a, b;
    a = readPoint();
    b = readPoint();
    return L(a, b-a);
}

int main() {
    while(true) {
        char s[2][10];
        L l1 = readLine();
        scanf("%s", s[0]);
        L l2 = readLine();
        scanf("%s", s[1]);
        if (strcmp(s[0], "END") == 0)
            break;
        double d;
        if (strcmp(s[0], "L") == 0 && strcmp(s[1], "L") == 0)
            d = ll_distance(l1, l2);
        if (strcmp(s[0], "LS") == 0 && strcmp(s[1], "LS") == 0)
            d = ss_distance(l1, l2);
        if (strcmp(s[0], "L") == 0 && strcmp(s[1], "LS") == 0)
            d = ls_distance(l1, l2);
        if (strcmp(s[0], "LS") == 0 && strcmp(s[1], "L") == 0)
            d = ls_distance(l2, l1);
        printf("%.5f\n", d);
    }
    return 0;
}
