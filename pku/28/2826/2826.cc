#include <iostream>
#include <complex>
#include <cmath>
#include <cstdio>

using namespace std;

typedef long double decimal;


/// 許容誤差
#define EP 1.0e-20


/// 誤差つき符号関数
inline int SGN(decimal a) { return abs(a) < EP ? 0 : a > 0 ? 1 : -1; }
#define EQ(a,b) (SGN((a)-(b)) == 0)    ///< equal
#define NE(a,b) (SGN((a)-(b)) != 0)    ///< not equal
#define LE(a,b) (SGN((a)-(b)) <= 0)    ///< less or equal
#define LS(a,b) (SGN((a)-(b)) < 0)     ///< less

typedef complex<decimal> Pt;



/// 直線もしくは線分
/**
 * posとpos+dirを結ぶ線分、またはそれを延長した直線を表す。
 */
struct Ln {
    Pt pos, dir;

    Ln() {
    }
    Ln(const Pt& pos, const Pt& dir)
        : pos(pos), dir(dir) {
    }

    /// ax+by+c = 0なる式が表す直線を生成する
    static Ln make_line_eq(decimal a, decimal b, decimal c) {
        return Ln((NE(a, 0) ? Pt(-c/a, 0) : Pt(0, -c/b)), Pt(b, -a));
    }
};



/// 内積を求める
inline decimal inp(const Pt& a, const Pt& b) {
    return (conj(a)*b).real();
}

/// 外積を求める
inline decimal outp(const Pt& a, const Pt& b) {
    return (conj(a)*b).imag();
}


/// 射影ベクトルを求める
/**
 * \param[in] p 射影元のベクトル
 * \param[in] b 射影先のベクトル
 */
inline Pt proj(const Pt& p, const Pt& b) {
    return b*inp(p,b)/norm(b);
}

/// 点から直線に対して引いた垂線の足を求める
inline Pt perf(const Ln& l, const Pt& p) {
    const Ln m(l.pos - p, l.dir);
    return (p + (m.pos - proj(m.pos, m.dir)));
}

/// 線分を直線に射影した線分を求める
/**
 * \param[in] s 射影元の線分
 * \param[in] b 射影先の直線
 */
inline Ln proj(const Ln& s, const Ln& b) {
    return Ln(perf(b, s.pos), proj(s.dir, b.dir));
}



/// 回転の方向を調べる(Sedgewickのおせっかい版)
inline int ccw(const Pt& p, const Pt& r, const Pt& s) {
    Pt a(r-p), b(s-p);
    decimal sgn = SGN(outp(a, b));
    if (sgn != 0)
        return (int)sgn;
    if (LS(a.real()*b.real(), 0) || LS(a.imag()*b.imag(), 0))
        return -1;
    if (LS(norm(a), norm(b)))
        return 1;
    return 0;
}

/// 回転の方向を調べる
inline int rot(const Pt& p, const Pt& r, const Pt& s) {
    return SGN(outp(r-p, s-p));
}



/// 直線表現の正規化を行う
Ln normalize_line(const Ln& l) {
    return Ln(perf(l, Pt(0, 0)),
              (l.dir.imag() < 0 ? -l.dir : l.dir)/abs(l.dir));
}


/// 直線同士が交差するかどうか調べる
bool ll_intersects(const Ln& l, const Ln& m) {
    Ln a = normalize_line(l);
    Ln b = normalize_line(m);
    return NE(abs(a.dir-b.dir), 0);
}

/// 直線と線分が交差するか調べる
bool ls_intersects(const Ln& l, const Ln& s) {
    return ( ccw(l.pos, l.pos+l.dir, s.pos)
             *ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0 );
}

/// 線分同士が交差するか調べる
bool ss_intersects(const Ln& s, const Ln& t) {
    return (ls_intersects(s, t) &&
            ls_intersects(t, s));
}


/// 直線同士が平行かどうか調べる
bool line_parallel(const Ln& l, const Ln& m) {
    return !ll_intersects(l, m);
}

/// 直線同士が一致するか調べる
bool line_equals(const Ln& l, const Ln& m) {
    Ln a = normalize_line(l);
    Ln b = normalize_line(m);
    return (EQ(abs(a.pos-b.pos), 0) && EQ(abs(a.dir-b.dir), 0));
}



/// 点と点の距離
decimal pp_distance(const Pt& a, const Pt& b) {
    return abs(a-b);
}

/// 直線と点の距離
decimal lp_distance(const Ln& l, const Pt& p) {
    return pp_distance(perf(l, p), p);
}

/// 線分と点の距離
decimal sp_distance(const Ln& s, const Pt& p) {
    const Pt r = perf(s, p);
    const decimal pos = ((r-s.pos)/s.dir).real();
    if (LE(0, pos) && LE(pos, 1))
        return lp_distance(s, p);
    return min(pp_distance(s.pos, p),
               pp_distance(s.pos+s.dir, p));
}

/// 線分と線分の距離
decimal ss_distance(const Ln& s, const Ln& t) {
    if (ss_intersects(s, t))
        return 0;
    return min(sp_distance(s, t.pos),
           min(sp_distance(s, t.pos+t.dir),
           min(sp_distance(t, s.pos),
               sp_distance(t, s.pos+s.dir))));
}

/// 直線と線分の距離
decimal ls_distance(const Ln& l, const Ln& s) {
    if (ls_intersects(l, s))
        return 0;
    return min(lp_distance(l, s.pos),
               lp_distance(l, s.pos+s.dir));
}

///直線と直線の距離
decimal ll_distance(const Ln& l, const Ln& m) {
    Ln a = normalize_line(l);
    Ln b = normalize_line(m);
    if (NE(abs(a.dir-b.dir), 0))
        return 0;
    return pp_distance(a.pos/a.dir, b.pos/b.dir);
}


int main() {
    int n;
    cin >> n;
    while(n-- > 0) {

        Ln l1, l2;
        {
            Pt a, b;
            decimal x, y;
            cin >> x >> y;
            a = Pt(x, y);
            cin >> x >> y;
            b = Pt(x, y);
            l1 = Ln(a, b-a);
            cin >> x >> y;
            a = Pt(x, y);
            cin >> x >> y;
            b = Pt(x, y);
            l2 = Ln(a, b-a);
        }

        decimal collect;
        if (!ss_intersects(l1, l2)) {
            collect = 0.0;
        }
        else if (line_equals(l1, l2)) {
            collect = 0.0;
        }
        else {
            decimal t = outp(l2.pos-l1.pos, l2.dir) / outp(l1.dir, l2.dir);
            Pt center = l1.pos + t*l1.dir;
            Pt q1 = (l1.pos.imag() > (l1.pos+l1.dir).imag()) ? l1.pos : (l1.pos+l1.dir);
            Pt q2 = (l2.pos.imag() > (l2.pos+l2.dir).imag()) ? l2.pos : (l2.pos+l2.dir);
            Pt p1 = q1 - center;
            Pt p2 = q2 - center;
            if (EQ(abs(p1), 0) || EQ(abs(p2), 0)) {
                collect = 0.0;
            }
            else {
                decimal th1 = arg(p1);
                decimal th2 = arg(p2);
                if (th2 > th1) {
                    swap(p1, p2);
                    swap(th1, th2);
                }
                if (LE(p2.real(), p1.real())) {
                    collect = 0.0;
                }
                else {
                    decimal h = min(p1.imag(), p2.imag());
                    if (EQ(h, 0)) {
                        collect = 0.0;
                    }
                    else {
                        decimal w = abs(h/tan(th1) - h/tan(th2));
                        collect = h*w/2;
                    }
                }
            }
        }

        printf("%.02f\n", (double)collect);

    }
    return 0;
}
