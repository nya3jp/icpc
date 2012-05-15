#include <iostream>
#include <string>
#include <utility>
#include <complex>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

const double EPS = 1.0e-10;

// 点
typedef complex<double> P;
 
// 線分・半直線・直線
struct L { P pos, dir; };
 
// 多角形
typedef vector<P> G;

// 二つのベクトルの内積を計算する
inline double inp(const P& a, const P& b) {
    return (conj(a)*b).real();
}
 
// 二つのベクトルの外積を計算する
inline double outp(const P& a, const P& b) {
    return (conj(a)*b).imag();
}

inline int signum(double x) {
    return (abs(x) < EPS ? 0 : x > 0 ? 1 : -1);
}

// ベクトルpをベクトルbに射影したベクトルを計算する
inline P proj(const P& p, const P& b) {
    return b*inp(p,b)/norm(b);
}
 
// 点pから直線lに引いた垂線の足となる点を計算する
inline P perf(const L& l, const P& p) {
    L m = {l.pos - p, l.dir};
    return (p + (m.pos - proj(m.pos, m.dir)));
}
 
// 線分sを直線bに射影した線分を計算する
inline L proj(const L& s, const L& b) {
     return (L){perf(b, s.pos), proj(s.dir, b.dir)};
}

inline int ccw(const P& p, const P& r, const P& s) {
    P a(r-p), b(s-p);
    int sgn = signum(outp(a, b));
    if (sgn != 0)
        return sgn;
    if (a.real()*b.real() < -EPS || a.imag()*b.imag() < -EPS)
        return -1;
    if (norm(a) < norm(b) - EPS)
        return 1;
    return 0;
}

bool ss_intersects(const L& s, const L& t) {
    return (ccw(s.pos, s.pos+s.dir, t.pos) *
            ccw(s.pos, s.pos+s.dir, t.pos+t.dir) <= 0 &&
            ccw(t.pos, t.pos+t.dir, s.pos) *
            ccw(t.pos, t.pos+t.dir, s.pos+s.dir) <= 0);
}

bool ls_intersects(const L& l, const L& s) {
    return (signum(outp(l.dir, s.pos-l.pos)) *
            signum(outp(l.dir, s.pos+s.dir-l.pos)) <= 0);
}

double sp_distance(const L& s, const P& p) {
    const P r = perf(s, p);
    const double pos = ((r-s.pos)/s.dir).real();
    if (-EPS <= pos && pos <= 1 + EPS)
        return abs(r - p);
    return min(abs(s.pos - p),
               abs(s.pos+s.dir - p));
}

double lp_distance(const L& l, const P& p) {
    return abs(outp(l.dir, p-l.pos) / abs(l.dir));
}

double ss_distance(const L& s, const L& t) {
    if (ss_intersects(s, t))
        return 0;
    return (sp_distance(s, t.pos) <?
            sp_distance(s, t.pos+t.dir) <?
            sp_distance(t, s.pos) <?
            sp_distance(t, s.pos+s.dir));
}

double ls_distance(const L& l, const L& s) {
    if (ls_intersects(l, s))
        return 0;
    return min(lp_distance(l, s.pos), lp_distance(l, s.pos+s.dir));
}

bool ll_intersects(const L& l, const L& m) {
    return (abs((l.dir/m.dir).imag()) > EPS);
}

double ll_distance(const L& l, const L& m) {
    return (ll_intersects(l, m) ? 0 : lp_distance(l, m.pos));
}

P read_point() {
    double x, y;
    cin >> x >> y;
    return P(x, y);
}

pair<L, bool> read_line() {
    P first, last;
    first = read_point();
    last = read_point();
    string s;
    cin >> s;
    if (s == "END")
        exit(0);
    return make_pair((L){first, last-first}, (s == "L"));
}

int main() {

    for(;;) {

        pair<L,bool> one = read_line();
        pair<L,bool> two = read_line();

        double res;
        if (one.second && two.second) {
            res = ll_distance(one.first, two.first);
        }
        else if (one.second) {
            res = ls_distance(one.first, two.first);
        }
        else if (two.second) {
            res = ls_distance(two.first, one.first);
        }
        else {
            res = ss_distance(one.first, two.first);
        }

        printf("%.5f\n", res);

    }

    return 0;
}

