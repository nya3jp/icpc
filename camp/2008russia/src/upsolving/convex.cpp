#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

typedef long double decimal;

const decimal EPS = 1.0e-15;

typedef complex<decimal> P;

struct L { P a, b; };

inline decimal outp(const P& a, const P& b) {
    return ((conj(a)*b).imag());
}

P readPoint() {
    decimal x, y;
    cin >> x >> y;
    return P(x, y);
}

bool line_parallel(const L& li, const L& lj) {
    return (abs(outp(lj.b-lj.a, li.b-li.a)) < EPS);
}

P line_cross(const L& li, const L& lj) {
    decimal num = outp(lj.b-lj.a, lj.a-li.a);
    decimal denom = outp(lj.b-lj.a, li.b-li.a);
    return li.a + (li.b-li.a)*num/denom;
}

bool nearly_equal(decimal a, decimal b) {
    return (abs(a-b) < EPS);
}

bool xy_less(const L& a, const L& b) {
    if (abs(a.a.imag()-b.a.imag()) < EPS)
        return (a.a.real() < b.a.real());
    return (a.a.imag() < b.a.imag());
}
inline decimal outp(const L& a, const L& b, const L& c) {
    return outp(b.a-a.a, c.a-a.a);
}
template<class IN>
void walk_rightside(IN begin, IN end, vector<L>& v) {
    IN cur = begin;
    v.push_back(*cur++);
    vector<L>::size_type s = v.size();
    v.push_back(*cur++);
    while(cur != end) {
        if (v.size() == s || outp(v[v.size()-2], v.back(), *cur) > -EPS)
            v.push_back(*cur++);
        else
            v.pop_back();
    }
    v.pop_back();
}

vector<L> convex_hull(vector<L> v) {
    if (v.size() <= 1)
        return v;
    sort(ALLOF(v), xy_less);
    vector<L> cv;
    walk_rightside(v.begin(), v.end(), cv);
    walk_rightside(v.rbegin(), v.rend(), cv);
    return cv;
}

int main() {

    if (!freopen("convex.in", "r", stdin))
        abort();
    if (!freopen("convex.out", "w", stdout))
        abort();

    int n;
    cin >> n;

    vector<L> lines(n);
    vector<P> velocities(n);
    REP(i, n) {
        L& l = lines[i];
        P& v = velocities[i];
        l.a = readPoint();
        l.b = readPoint();
        decimal vl;
        cin >> vl;
        v = (l.b-l.a)/abs(l.b-l.a)*P(0, -1)*vl;
    }

    decimal T;
    cin >> T;

    vector<L> points;
    REP(i, n) REP(j, i) {
        L li0 = lines[i], lj0 = lines[j];
        if (!line_parallel(li0, lj0)) {
            P c0 = line_cross(li0, lj0);
            L li1 = li0, lj1 = lj0;
            li1.a += velocities[i];
            li1.b += velocities[i];
            lj1.a += velocities[j];
            lj1.b += velocities[j];
            P c1 = line_cross(li1, lj1);
            points.push_back((L){c0, c1});
        }
    }

    int m = points.size();

    vector<decimal> times;
    REP(i, m) REP(j, i) REP(k, j) {
        L la = points[i], lb = points[j], lc = points[k];
        P a1 = lb.a-la.a, a2 = lc.a-la.a;
        P b1 = (lb.b-lb.a)-(la.b-la.a), b2 = (lc.b-lc.a)-(la.b-la.a);
        P da = a2 - a1, db = b2 - b1;
        decimal A = outp(b1, db), B = outp(a1, db) + outp(b1, da), C = outp(a1, da);
        decimal D = B*B - 4*A*C;
        if (abs(A) < EPS) {
            if (abs(B) > EPS)
                times.push_back(-C / B);
        }
        else if (D <= -EPS) {
            // no solution
        }
        else if (D <= EPS) {
            times.push_back((-B) / (2*A));
        }
        else {
            times.push_back((-B + sqrt(D)) / (2*A));
            times.push_back((-B - sqrt(D)) / (2*A));
        }
    }

    times.push_back(0);
    times.push_back(T);
    sort(ALLOF(times));
    times.erase(unique(ALLOF(times), nearly_equal), times.end());

    decimal sum = 0;
    REP(iTime, times.size()-1) {
        decimal from = times[iTime], to = times[iTime+1];
        if (!(0 <= from && from < T-EPS))
            continue;

        decimal mid = (from+to)/2;
        decimal dt = (to-from)/2;

        vector<L> convex;
        REP(i, points.size())
            convex.push_back((L){(points[i].b-points[i].a)*mid+points[i].a, points[i].b-points[i].a});
        convex = convex_hull(convex);
        int k = convex.size();

        decimal lo = 0;
        REP(i, k) {
            int j = (i+1)%k;
            P ai = convex[i].a, aj = convex[j].a;
            P bi = convex[i].b, bj = convex[j].b;
            lo += dt*dt*dt*2/3*outp(bj, bi) + 2*dt*outp(aj, ai);
        }
        sum += abs(lo)/2;
    }
    sum /= T;

    printf("%.20f\n", (double)sum);

    return 0;
}

