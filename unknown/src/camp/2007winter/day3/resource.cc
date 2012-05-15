#define MP 1
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

// 実数の比較誤差
#define EPS 1.0e-10
 
// 実数の符号関数
inline int SGN(double a) { return abs(a) < EPS ? 0 : a > 0 ? 1 : -1; }
 
// 実数の比較関数
#define EQ(a,b) (SGN((a)-(b)) == 0)    // equal
#define NE(a,b) (SGN((a)-(b)) != 0)    // not equal
#define LE(a,b) (SGN((a)-(b)) <= 0)    // less or equal
#define LT(a,b) (SGN((a)-(b)) <  0)    // less
#define GE(a,b) (SGN((a)-(b)) >= 0)    // greater or equal
#define GT(a,b) (SGN((a)-(b)) >  0)    // greater

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

bool sp_intersects(const L& s, const P& p) {
    return ( abs(s.pos - p) + abs(s.pos + s.dir - p) - abs(s.dir) < EPS );
}

double sp_distance(const L& s, const P& p) {
    const P r = perf(s, p);
    const double pos = ((r-s.pos)/s.dir).real();
    if (LE(0, pos) && LE(pos, 1))
        return abs(r - p);
    return min(abs(s.pos - p),
               abs(s.pos+s.dir - p));
}

bool gp_contains(const G& g, const P& p) {
    double sum = 0.0;
    int n = g.size();
    for(int i = 0; i < n; i++) {
        int j = (i+1)%n;
        if (sp_intersects((L){g[i], g[j]-g[i]}, p))
            return true;
        sum += arg((g[j]-p)/(g[i]-p));
    }
    return (abs(sum) > 1);
}

G read_polygon() {
    int n;
    cin >> n;
    G g;
    REP(i, n) {
        double x, y;
        cin >> x >> y;
        g.push_back(P(x, y));
    }
    return g;
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

double ss_distance(const L& s, const L& t) {
    if (ss_intersects(s, t))
        return 0;
    return min(sp_distance(s, t.pos),
           min(sp_distance(s, t.pos+t.dir),
           min(sp_distance(t, s.pos),
               sp_distance(t, s.pos+s.dir))));
}

void mp_draw(const vector<P>& v) {
    printf("draw ");
    REP(i, v.size())
        printf("(%.2fq,%.2fq)--", v[i].real(), v[i].imag());
    printf("cycle;\n");
}
void mp_fill(const vector<P>& v) {
    printf("fill ");
    REP(i, v.size())
        printf("(%.2fq,%.2fq)--", v[i].real(), v[i].imag());
    printf("cycle;\n");
}


int nearest_(const vector<G>& islands, const G& resource, double limit, P p) {
    int n = islands.size();
    if (!gp_contains(resource, p))
        return -2;
    vector<double> dists(n, numeric_limits<double>::max());
    REP(i, n) {
        int m = islands[i].size();
        REP(j, m) {
            int k = (j+1)%m;
            dists[i] <?= sp_distance((L){islands[i][j], islands[i][k]-islands[i][j]}, p);
        }
    }
    int k = min_element(ALLOF(dists))-dists.begin();
    if (dists[k] > limit)
        return -1;
    return k;
}
int nearest(const vector<G>& islands, const G& resource, double limit, P p) {
    int k = nearest_(islands, resource, limit, p);
    //cout << p << " => " << k << endl;
    return k;
}

P search(const vector<G>& islands, int iIsland, const G& resource, double limit, double resolution, P from, P to) {
    double dx = (to-from).real();
    double dy = (to-from).imag();
    if (max(dx, dy) < resolution)
        return P(0, dx*dy);
    P ps[4] = {from, from+P(0, dy), to, from+P(dx, 0)};
    P dp = P(dx, dy);
    bool same = true;
    int v[4];
    v[0] = nearest(islands, resource, limit, ps[0]);

    for(int i = 1; i < 4; i++) {
        v[i] = nearest(islands, resource, limit, ps[i]);
        if (v[i] != v[0]) {
            same = false;
            break;
        }
    }
    if (same) {
        if (v[0] == -2) {
            bool touch = false;
            REP(i, 4) {
                int j = (i+1)%4;
                REP(k, resource.size()) {
                    int l = (k+1)%resource.size();
                    if (ss_intersects((L){ps[i], ps[j]-ps[i]}, (L){resource[l], resource[k]-resource[l]})) {
                        touch = true;
                    }
                }
            }
            if (!touch) {
#if MP
                mp_draw(vector<P>(ps, ps+4));
#endif
                return 0;
            }
        }
        else if (v[0] == -1) {
            double dist = numeric_limits<double>::max();
            REP(i, 4) {
                int j = (i+1)%4;
                REP(k, islands[iIsland].size()) {
                    int l = (k+1)%islands[iIsland].size();
                    dist <?= ss_distance((L){ps[i], ps[j]-ps[i]}, (L){islands[iIsland][l], islands[iIsland][k]-islands[iIsland][l]});
                }
            }
            if (dist > limit) {
#if MP
                mp_draw(vector<P>(ps, ps+4));
#endif
                return 0;
            }
        }
        else {
            if (v[0] == iIsland) {
#if MP
                mp_fill(vector<P>(ps, ps+4));
#endif
            }
            else {
#if MP
                mp_draw(vector<P>(ps, ps+4));
#endif
            }
            return dp * (v[0] == iIsland ? 1. : 0.);
        }
    }

    P vs[4] = {from, from+P(dx/2, 0), from+P(0, dy/2), from+P(dx/2, dy/2)};
    P res = 0;
    REP(i, 4)
        res += search(islands, iIsland, resource, limit, resolution, vs[i], vs[i]+dp*0.5);
    return res;
}

P solve(const vector<G>& islands, int iIsland, const G& resource, double limit, double resolution) {
    double left = 10000, right = -100000, bottom = 100000, top = -100000;
    REP(i, resource.size()) {
        left <?= resource[i].real();
        right >?= resource[i].real();
        bottom <?= resource[i].imag();
        top >?= resource[i].imag();
    }

    return search(islands, iIsland, resource, limit, resolution, P(left, bottom), P(right, top));
}

int main() {

    // May fate be with you!

    freopen("resource.in", "r", stdin);

#if MP
    printf("beginfig(1);\nq := 0.4cm;\n");
#endif

    int iCase = 0;
    for(;;) {
        int n, m;
        double limit;
        cin >> n >> m >> limit;

        if (n == 0 && m == 0)
            break;

        vector<G> islands, resources;
        vector<double> ratios(m);

        REP(i, n)
            islands.push_back(read_polygon());
        REP(i, m) {
            cin >> ratios[i];
            resources.push_back(read_polygon());
        }

#if MP
        printf("pickup pencircle scaled 3\n");
        REP(i, n)
            mp_draw(islands[i]);
        printf("pickup pencircle scaled 2\n");
        REP(i, m)
            mp_draw(resources[i]);
        printf("pickup pencircle\n");
#endif

        vector<P> res;
        res.assign(n, P(-1, 0));
        for(double resolution = 0.03; ; resolution /= 2) {
            bool ok = true;
            REP(i, n) {
                if (res[i].imag()-res[i].real() > 0.05) {
                    res[i] = 0;
                    REP(j, resources.size())
                        res[i] += solve(islands, i, resources[j], limit, resolution) * ratios[j];
                    fprintf(stderr, "%d: %.3f - %.3f\n", i, res[i].real(), res[i].imag());
                    ok = false;
                }
            }
            if (ok)
                break;
            break;
        }

        if (iCase > 0)
            printf("%% \n");

        REP(i, n) {
            printf("%% %.1f\n", (res[i].real()+res[i].imag())/2.0);
        }
        
    }

#if MP
    printf("%%currentpicture := currentpicture shifted 1/2(210mm,297mm);\nendfig;\nend;\n");
#endif
    return 0;
}



// Powered by fate testarossa
