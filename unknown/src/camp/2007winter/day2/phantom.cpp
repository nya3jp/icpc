#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>
#include <cmath>

using namespace std;


#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

#define EP 1.0e-10
inline int SGN(double a) { return abs(a) < EP ? 0 : a > 0 ? 1 : -1; }
#define LE(a,b) (SGN((a) - (b)) <= 0)
#define LT(a,b) (SGN((a) - (b)) <  0)

typedef complex<double> P;
struct L { P pos, dir; };

unsigned long long int counter = 0;

// library
inline double inp(const P& a, const P& b)
{
    return (conj(a) * b).real();
}

inline double outp(const P& a, const P& b)
{
    return (conj(a) * b).imag();
}

inline P proj(const P& p, const P& b)
{
    return b * inp(p, b) / norm(b);
}

inline P perf(const L& l, const P& p)
{
    L m = { l.pos - p, l.dir };
    return (p + (m.pos - proj(m.pos, m.dir)));
}

inline int ccw(const P& p, const P& r, const P& s)
{
    P a(r - p), b(s - p);
    int sgn = SGN(outp(a, b));
    if (sgn != 0)
        return sgn;
    if (LT(a.real() * b.real(), 0) || LT(a.imag() * b.imag(), 0))
        return -1;
    if (LT(norm(a), norm(b)))
        return 1;
    return 0;
}

bool ls_intersects(const L& l, const L& s)
{
    return (ccw(l.pos, l.pos + l.dir, s.pos)
            * ccw(l.pos, l.pos + l.dir, s.pos + s.dir) < 0);
}

bool ss_intersects(const L& s, const L& t)
{
    return (ls_intersects(s, t) && ls_intersects(t, s));
}

// main
P reflect(P p, L l)
{
    P foot = perf(l, p);
    return p + (foot - p) * 2.0;
}

bool lookable(P from, P to, L l1)
{
    L l2 = { from, to - from };
    return ss_intersects(l1, l2);
}

bool check(P orig, P target, vector<L>& hist, L kabe)
{
    L seg = { orig, target - orig };
    if (ss_intersects(seg, kabe))
        return false;

    REP(i, hist.size()) {
        if (ss_intersects(seg, hist[i]) == false)
            return false;
    }
    return true;
}

void step(P origP, P p, L l1, L l2, vector<L>& hist, L kabe, int ndepth)
{
    P reflectP = reflect(p, l1);
    hist.push_back(l1);

    if (check(origP, reflectP, hist, kabe)) {
        counter++;
    }

    if (counter >= 100)
        return;

    if (ndepth == 200)
        return;

    // new mirror
    P tmp = reflect(l2.pos, l1);
    L newL = { tmp, reflect(l2.pos + l2.dir, l1) - tmp };
    step(origP, reflectP, newL, l1, hist, kabe, ndepth + 1);
}

void solve(P myP, L l1, L l2)
{
    counter = 0;

    {
        vector<L> empty;
        P myreflectionP = reflect(myP, l1);
        if (!ss_intersects((L){ myP, myreflectionP - myP }, l2))
            step(myP, myP, l1, l2, empty, l2, 0);
    }

    {
        vector<L> empty;
        P myreflectionP = reflect(myP, l2);
        if (!ss_intersects((L){ myP, myreflectionP - myP }, l1))
            step(myP, myP, l2, l1, empty, l1, 0);
    }

    if (counter >= 100)
        cout << "TOO MANY" << endl;
    else
        cout << counter << endl;
}

int main(void)
{
    freopen("mirror.in", "r", stdin);
    
    int myX, myY;
    while (true) {
        cin >> myX >> myY;
        if (myX == 0 && myY == 0)
            return 0;

        P myP(myX, myY);

        int mirX, mirY;
        cin >> mirX >> mirY;
        P mirP1(mirX, mirY);
        cin >> mirX >> mirY;
        P mirP2(mirX, mirY);
        cin >> mirX >> mirY;
        P mirP3(mirX, mirY);
        cin >> mirX >> mirY;
        P mirP4(mirX, mirY);

        L l1 = { mirP1, mirP2 - mirP1 };
        L l2 = { mirP3, mirP4 - mirP3 };

        solve(myP, l1, l2);
    }
    return 0;
}
