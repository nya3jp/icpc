#include <iostream>
#include <complex>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef complex<double> P;

struct L {
    P pos, dir;
};

typedef vector<P> G;

#define EP 1.0e-10
inline int SGN(double a) { return abs(a) < EP ? 0 : a > 0 ? 1 : -1; }
#define EQ(a,b) (SGN((a)-(b)) == 0)    // equal
#define NE(a,b) (SGN((a)-(b)) != 0)    // not equal
#define LE(a,b) (SGN((a)-(b)) <= 0)    // less or equal
#define LT(a,b) (SGN((a)-(b)) <  0)    // less
#define GE(a,b) (SGN((a)-(b)) >= 0)    // greater or equal
#define GT(a,b) (SGN((a)-(b)) >  0)    // greater
namespace std {
    inline bool operator<(const P& a, const P& b) {
        if (NE(a.real(), b.real()))
            return LT(a.real(), b.real());
        return LT(a.imag(), b.imag());
    }
}
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


bool ls_intersects(const L& l, const L& s) {
    return (ccw(l.pos, l.pos+l.dir, s.pos)
            *ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0);
}
bool ss_intersects(const L& s, const L& t) {
    return (ls_intersects(s, t) &&
            ls_intersects(t, s));
}

bool gp_contains(const G& g, const P& p) {
    int n = g.size();

    double sum = 0;
    REP(i, n) {
        int j = (i+1)%n;
        sum += arg((g[j]-p)/(g[i]-p));
    }

    return (abs(sum) > 1);
}

bool gg_intersects(const G& a, const G& b) {
    int n = a.size();
    int m = b.size();
    REP(i, n) REP(j, m) {
        L s1 = (L){a[i], a[(i+1)%n]-a[i]};
        L s2 = (L){b[j], b[(j+1)%m]-b[j]};
        if (ss_intersects(s1, s2))
            return true;
    }
    return gp_contains(a, b[0]) || gp_contains(b, a[0]);
}

void solve() {
    int nPolygons;
    cin >> nPolygons;

    vector<G> polygons(nPolygons);
    REP(iPolygon, nPolygons) {
        G& g = polygons[iPolygon];
        int n;
        cin >> n;
        REP(i, n) {
            int x, y;
            scanf("%d,%d", &x, &y);
            g.push_back(P(x, y));
        }
    }

    bool hit = false;
    REP(i, nPolygons) REP(j, nPolygons) {
        if (!(i < j))
            continue;
        if (gg_intersects(polygons[i], polygons[j])) {
            hit = true;
            cout << (i+1) << ' ' << (j+1) << endl;
        }
    }

    if (!hit)
        cout << "no collisions" << endl;
}


int main() {
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        cout << "Data Set #" << (iCase+1) << endl;
        solve();
    }
    return 0;
}






