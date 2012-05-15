#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

const double PI = acos(0.0)*2;
#define EP 1.0e-5
inline int SGN(double a) { return abs(a) < EP ? 0 : a > 0 ? 1 : -1; }
#define EQ(a,b) (SGN((a)-(b)) == 0)    // equal
#define NE(a,b) (SGN((a)-(b)) != 0)    // not equal
#define LE(a,b) (SGN((a)-(b)) <= 0)    // less or equal
#define LT(a,b) (SGN((a)-(b)) <  0)    // less
#define GE(a,b) (SGN((a)-(b)) >= 0)    // greater or equal
#define GT(a,b) (SGN((a)-(b)) >  0)    // greater

typedef complex<double> P;
typedef vector<P> G;
typedef const P &CP;
namespace std {
    inline bool operator<(const P& a, const P& b) {
        if (NE(a.real(), b.real()))
            return LT(a.real(), b.real());
        return LT(a.imag(), b.imag());
    }
}
struct L { // 線分、半直線、直線
    P pos, dir; // posとpos+dirを結ぶ線分
};
inline double inp(const P& a, const P& b) { // 内積を求める
    return (conj(a)*b).real();
}
inline double outp(const P& a, const P& b) { // 外積を求める
    return (conj(a)*b).imag();
}
inline P proj(const P& p, const P& b) { // pをbに射影
    return b*inp(p,b)/norm(b);
}
inline P perf(const L& l, const P& p) { // 垂線の足
    L m = {l.pos - p, l.dir};
    return (p + (m.pos - proj(m.pos, m.dir)));
}
inline L proj(const L& s, const L& b) { // 線分を直線に射影
    return (L){perf(b, s.pos), proj(s.dir, b.dir)};
}
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
L normalize_line(const L& l) {
    return (L){perf(l, P(0, 0)),
            ( (LT(l.dir.imag(), 0) || (EQ(l.dir.imag(), 0) && LT(l.dir.real(), 0)) )
              ? -l.dir : l.dir ) / abs(l.dir) };
}
bool ll_intersects(const L& l, const L& m) {
    return NE(abs(normalize_line(l).dir - normalize_line(m).dir), 0);
}
bool ls_intersects(const L& l, const L& s) {
    return (ccw(l.pos, l.pos+l.dir, s.pos)
            *ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0);
}
bool ss_intersects(const L& s, const L& t) {
    return (ls_intersects(s, t) &&
            ls_intersects(t, s));
}
bool line_parallel(const L& l, const L& m) {
    return !ll_intersects(l, m);
}
bool line_equals(const L& l, const L& m) {
    L a = normalize_line(l);
    L b = normalize_line(m);
    return (EQ(abs(a.pos-b.pos), 0) && EQ(abs(a.dir-b.dir), 0));
}
bool sp_intersects(const L& s, const P& p) {
    P r = (p-s.pos)/s.dir;
    return (EQ(r.imag(), 0) && LE(0, r.real()) && LE(r.real(), 1));
}
bool gs_intersects(const G& g, const L& s) {
    int n = g.size();
    for(int i = 0; i < n; i++) {
        int j = (i+1)%n;
        L t = (L){g[i], g[j]-g[i]};
        if (ss_intersects(s, t))
            return true;
    }
    return false;
}
double pp_distance(const P& a, const P& b) {
    return abs(a - b);
}
double lp_distance(const L& l, const P& p) {
    return abs(perf(l, p) - p);
}
double sp_distance(const L& s, const P& p) {
    const P r = perf(s, p);
    const double pos = ((r-s.pos)/s.dir).real();
    if (LE(0, pos) && LE(pos, 1))
        return abs(r - p);
    return min(abs(s.pos - p),
               abs(s.pos+s.dir - p));
}
double ss_distance(const L& s, const L& t) {
    if (ss_intersects(s, t))
        return 0;
    return min(sp_distance(s, t.pos),
               min(sp_distance(s, t.pos+t.dir),
                   min(sp_distance(t, s.pos),
                       sp_distance(t, s.pos+s.dir))));
}
double ls_distance(const L& l, const L& s) {
    if (ls_intersects(l, s))
        return 0;
    return min(lp_distance(l, s.pos),
               lp_distance(l, s.pos+s.dir));
}
double ll_distance(const L& l, const L& m) {
    L a = normalize_line(l);
    L b = normalize_line(m);
    if (NE(abs(a.dir-b.dir), 0))
        return 0;
    return abs(a.pos - b.pos);
}


struct R {
    P pos, dir;
    inline P bl() const {
        return pos;
    }
    inline P br() const {
        return pos + P(dir.real(), 0);
    }
    inline P tl() const {
        return pos + P(0, dir.imag());
    }
    inline P tr() const {
        return pos + dir;
    }
};

double radius;
vector<P> points;
set<P> pointset;
vector<R> rects;
map<P, vector<P> > turns;

bool newpoint(const P& p) {
    REP(i, rects.size()) {
        const R& r = rects[i];
        L ls[4] = {(L){r.bl(), r.br()-r.bl()},
                   (L){r.bl(), r.tl()-r.bl()},
                   (L){r.br(), r.tr()-r.br()},
                   (L){r.tl(), r.tr()-r.tl()},};
        REP(j, 4) {
            double d = sp_distance(ls[j], p);
            fprintf(stderr, "%10.5f", d);
            if (LT(sp_distance(ls[j], p), radius)) {
                cerr << "rect" << i << endl;
                cerr << r.pos << "," << r.dir << endl;
                cerr << ls[j].pos << "->" << ls[j].pos+ls[j].dir << endl;
                cerr << p << endl;
                fprintf(stderr, "%.15f\n", radius);
                fprintf(stderr, "%.15f\n", sp_distance(ls[j], p));
                assert(false);
            }
        }
    }
    if (pointset.insert(p).second) {
        points.push_back(p);
        return true;
    }
    return false;
}

bool cango(const L& s) {
    REP(i, rects.size()) {
        const R& r = rects[i];
        L ls[4] = {(L){r.bl(), r.br()-r.bl()},
                   (L){r.bl(), r.tl()-r.bl()},
                   (L){r.tr(), r.br()-r.tr()},
                   (L){r.tr(), r.tl()-r.tr()},};
        REP(j, 4)
            if (LT(ss_distance(ls[j], s), radius))
                return false;
        REP(j, 4)
            if (LT(sp_distance(ls[j], s.pos), radius))
                return false;
        REP(j, 4)
            if (LT(sp_distance(ls[j], s.pos+s.dir), radius))
                return false;
    }
    return true;
}

void grow() {
    int nPoints = points.size();
    REP(iPoint, nPoints) {
        P p = points[iPoint];
        REP(iRect, rects.size()) {
            const R& r = rects[iRect];
            if (LE(p.imag()+radius, r.pos.imag()) &&
                LE(p.real()+radius, r.tr().real())) {
                P c = r.br();
                double th = arg(c-p) + acos(radius/abs(c-p) - EP);
                assert(!isnan(th));
                P q = c - polar(radius, th);
                if (cango((L){p, q-p}))
                    if (newpoint(q))
                        turns[p].push_back(q);
            }
        }
    }
}

void rotate() {
    const P I(0, 1);
    REP(i, points.size())
        points[i] *= I;
    REP(i, rects.size()) {
        R& r = rects[i];
        r.pos *= I;
        r.pos -= P(r.dir.real(), 0);
    }
    FOR(it, turns) REP(i, it->second.size())
        it->second[i] *= I;
    pointset.clear();
    pointset.insert(ALLOF(points));
}

void mirror() {
    const P M(-1, 0);
    REP(i, points.size())
        points[i] *= M;
    REP(i, rects.size()) {
        R& r = rects[i];
        r.pos *= M;
        r.pos -= r.dir;
    }
    FOR(it, turns) REP(i, it->second.size())
        it->second[i] *= M;
    pointset.clear();
    pointset.insert(ALLOF(points));
}


void setup() {
    int n = rects.size();
    REP(i, n) REP(j, n) {
        const R& r1 = rects[i];
        const R& r2 = rects[j];
        P c1 = r1.br();
        P c2 = r2.tl();
        if (LE(c1.real(), c2.real()-radius*2) && LE(c1.imag(), c2.imag()+radius*2)) {
            double th = arg(c2-c1) - acos((2*radius)/abs(c2-c1) - EP);
            assert(!isnan(th));
            P p1 = c1 + polar(radius, th);
            P p2 = c2 - polar(radius, th);
            if (cango((L){p1, p2-p1})) {
                bool r1 = newpoint(p1);
                bool r2 = newpoint(p2);
                if (r1 || r2) {
                    turns[c1].push_back(p1);
                    turns[c2].push_back(p2);
                }
            }
        }
    }
    REP(i, n) REP(j, n) {
        const R& r1 = rects[i];
        const R& r2 = rects[j];
        P c1 = r1.br();
        P c2 = r2.br();
        if (LE(c1.real(), c2.real()) && LE(c1.imag(), c2.imag())) {
            double th = arg(c2-c1)-PI/2;
            P p1 = c1 + polar(radius, th);
            P p2 = c2 + polar(radius, th);
            if (cango((L){p1, p2-p1})) {
                bool r1 = newpoint(p1);
                bool r2 = newpoint(p2);
                if (r1 || r2) {
                    turns[c1].push_back(p1);
                    turns[c2].push_back(p2);
                }
            }
        }
    }

}

void emit() {
    REP(i, points.size())
        cout << points[i].real() << " " << points[i].imag() << endl;

    REP(i, rects.size()) {
        R& r = rects[i];
        int N = 20;
        REP(x, N+1) {//REP(y, N+1) {
            int y = x;
            P p = P(r.dir.real()*x/N, r.dir.imag()*y/N) + r.pos;
            cout << p.real() << " " << p.imag() << endl;
        }
    }

    cout << endl << endl << endl;
}

void solve() {
    {
        REP(iRotate, 4) {
            setup();
            rotate();
        }
        mirror();
        REP(iRotate, 4) {
            setup();
            rotate();
        }
        mirror();

        //cout << "# >>> " << points.size() << endl;
    }

        REP(iRotate, 4) {
            emit();
            rotate();
        }
        mirror();
        REP(iRotate, 4) {
            emit();
            rotate();
        }
        mirror();
    return;

    int nPointsLast = 0;
    do {

        nPointsLast = points.size();
        REP(iRotate, 4) {
            grow();
            rotate();
        }
        mirror();
        REP(iRotate, 4) {
            grow();
            rotate();
        }
        mirror();

        //cout << "# >>> " << points.size() << endl;

        emit();

    } while(points.size() > nPointsLast);

    /*
      int nPoints = points.size();
      Graph g(nPoints);
      REP(i, nPoints) {
      REP(j, nPoints) {
      if (cango(L(points[i], points[j]-points[i])))
      g[i].push_back(j);
      }
      }
    */
}


int main() {

    // May fate be with you!

    int n;
    cin >> radius >> n;

    rects.resize(n);
    {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        P s(x1, y1), t(x2, y2);
        if (s == t) {
            cout << 0 << endl;
            return 0;
        }
        points.push_back(s);
        points.push_back(t);
        pointset.insert(s);
        pointset.insert(t);
    }
    REP(i, n) {
        R& r = rects[i];
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        r.pos = P(x1, y1);
        r.dir = P(x2-x1, y2-y1);
    }
    solve();

    return 0;
}



// Powered by fate testarossa
