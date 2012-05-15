#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <complex>
#include <numeric>


using namespace std;

#define EP 1.0e-18

inline int SGN(long double a) { return (abs(a) < EP ? 0 : a > 0 ? 1 : -1); }
#define EQ(a,b) (SGN((a)-(b)) == 0)
#define NE(a,b) (SGN((a)-(b)) != 0)
#define LE(a,b) (SGN((a)-(b)) <= 0)
#define LT(a,b) (SGN((a)-(b)) < 0 )

typedef complex<long double> P;

struct L {
    P pos, dir;
    L(){}
    L(const P& pos, const P& dir) : pos(pos), dir(dir) {
    }
};

inline long double inp(const P& a, const P& b) {
    return (conj(a)*b).real();
}
inline long double outp(const P& a, const P& b) {
    return (conj(a)*b).imag();
}

inline P proj(const P& p, const P& b) {
    return b*inp(p,b)/norm(b);
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
            * ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0);
}

bool ss_intersects(const L& s, const L& t) {
    return (ls_intersects(s, t) && ls_intersects(t, s));
}

long double line_cross(const L& l, const L& m) {
    long double num = outp(m.dir, m.pos-l.pos);
    long double denom = outp(m.dir, l.dir);
    return num/denom;
}

L readLine() {
    long double ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    return L(P(ax, ay), P(bx, by) - P(ax, ay));
}

int main() {

    int nCases;
    cin >> nCases;
    while(nCases-- > 0) {

        L base = readLine();

        int n;
        cin >> n;

        vector<L> lines(n);
        vector<int> types(n);
        for(int i = 0; i < n; i++) {
            L& l = lines[i];
            l = readLine();
            int a, b;
            cin >> a >> b;
            types[i] = a^b;
        }

        vector<pair<long double, int> > intersects;

        for(int i = 0; i < n; i++) {
            if (ss_intersects(base, lines[i])) {
                long double r = line_cross(base, lines[i]);
                intersects.push_back(make_pair(r, types[i]));
            }
        }

        sort(intersects.begin(), intersects.end());

        int ans = 0;
        if (!intersects.empty()) {
            int cur = intersects[0].second;
            for(int i = 1; i < (int)intersects.size(); i++) {
                int next = intersects[i].second;
                if (next != cur) {
                    cur = next;
                    ans++;
                }
            }
        }

        cout << ans << endl;

    }


    return 0;
}
