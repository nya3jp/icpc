#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

/*
 * 幾何基礎
 */

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

// Ptの比較演算子
namespace std {
    inline bool operator<(const P& a, const P& b) {
        if (NE(a.real(), b.real()))
            return LT(a.real(), b.real());
        return LT(a.imag(), b.imag());
    }
}


// 多角形
typedef vector<P> G;



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

/*
 * 点、線分、半直線、直線に関する交差判定と距離
 */


using namespace std;


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
    return abs(a.pos - b.pos);
}

bool sp_intersects(const L& s, const P& p) {
    P r = (p-s.pos)/s.dir;
    return (EQ(r.imag(), 0) && LE(0, r.real()) && LE(r.real(), 1));
}

// 多角形が点を含むか調べる
double polygon_contains_point(const G& g, const P& pt) {
    double sum = 0.0;
    int n = g.size();
    for(int i = 0; i < n; i++) {
        int j = (i+1)%n;
        if (sp_intersects(L(g[i], g[j]-g[i]), pt))
            return true;
        sum += arg((g[j]-pt)/(g[i]-pt));
    }
    return (abs(sum) > 1);
}
// 多角形が線分と交わるか調べる
bool gs_intersects(const G& g, const L& s) {
    int n = g.size();
    for(int i = 0; i < n; i++) {
        int j = (i+1)%n;
        L t(g[i], g[j]-g[i]);
        if (ss_intersects(s, t))
            return true;
    }
    return false;
}

double polygon_contains_segment(const G& g, const L& l) {
    return (polygon_contains_point(g, l.pos) &&
            polygon_contains_point(g, l.pos+l.dir) &&
            !gs_intersects(g, l));
}

// 凸多角形が点を含むか調べる
double convex_polygon_contains_point(const G& g, const P& pt) {
    int n = g.size();
    int sign = 0;
    for(int i = 0; i < n; i++) {
        int j = (i+1)%n;
        int s = SGN(outp(g[j]-g[i], pt-g[i]));
        if (sign*s < 0)
            return false;
        if (s == 0 && ccw(g[i], g[j], pt) == 0)
            return true;
        sign += s;
    }
    return true;
}

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))
#define BITCOUNT __builtin_popcount

int main() {
    int nSubmarines;
    cin >> nSubmarines;
    vector<L> submarines(nSubmarines);
    //printf("beginfig(1);\n");
    //printf("s=100;\no=1000;\n");
    REP(i, nSubmarines) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        submarines[i] = L(P(x1,y1), P(x2,y2)-P(x1,y1));
        //printf("draw (%.0fs+o,%.0fs+o)..(%.0fs+o,%.0fs+o);\n", x1, y1, x2, y2);
    }
    int nLands;
    cin >> nLands;
    vector<G> lands(nLands);
    REP(i, nLands) {
        G& g = lands[i];
        int k;
        cin >> k;
        REP(j, k) {
            double x, y;
            cin >> x >> y;
            g.push_back(P(x, y));
            //printf("%s(%.0fs+o,%.0fs+o)", (j==0?"draw ":"--"), x, y);
        }
        //printf("--(%.0fs+o,%.0fs+o);\n", g[0].real(), g[0].imag());
    }
    //printf("endfig;\nend.\n");

    REP(i, nSubmarines) {
        int state = 0;
        L& m = submarines[i];
        REP(j, nLands) {
            G& g = lands[j];
            if (polygon_contains_segment(g, m)) {
                state = 2;
            }
            if (gs_intersects(g, m)) {
                state >?= 1;
            }
        }
        cout << "Submarine " << i+1 << " is "
             << ((const char*[]){"still in water.","partially on land.","completely on land."})[state] << endl;
    }

    return 0;
}
