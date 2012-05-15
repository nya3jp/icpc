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

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

typedef complex<double> P;

#define DBG 0
#define VERIFY 1
#define N 100000
#define EPS 1.0e-10

FILE* mp;

namespace std {
    bool operator<(const P& a, const P& b) {
        if (abs(a.real()-b.real()) > EPS)
            return (a.real() < b.real());
        if (abs(a.imag()-b.imag()) > EPS)
            return (a.imag() < b.imag());
        return false;
    }
}

struct Polyline {
    P a, b, c;
    int id;
};

inline double interpolate(const P& a, const P& b, double x) {
#if VERIFY
    assert(a.real() <= x + EPS && x <= b.real() + EPS);
#endif
    return (b.imag()-a.imag()) * (x-a.real())/(b.real()-a.real()) + a.imag();
}

inline double interpolate(const Polyline& p, double x) {
    return (x < p.b.real() ? interpolate(p.a, p.b, x) : interpolate(p.b, p.c, x));
}

double gx;

bool operator<(const Polyline& a, const Polyline& b) {
    double ay = interpolate(a, gx);
    double by = interpolate(b, gx);
    if (abs(ay-by) > EPS)
        return (ay < by);
    return (a.id < b.id);
}

enum EventType {
    OPEN,
    CLOSE,
};

struct Event {
    double x;
    EventType type;
    Polyline lower, upper;
};

bool operator<(const Event& a, const Event& b) {
    return (a.x < b.x);
}

inline P readPoint() {
    int x, y;
    scanf("%d%d", &x, &y);
    return P(x, y);
}

inline int ccw(const P& a, const P& b, const P& c) {
    P p = b-a, q = c-a;
    double op = (conj(p)*q).imag();
    if (abs(op) > EPS)
        return (op > 0 ? 1 : -1);
    double ip = (conj(p)*q).real();
    if (ip < -EPS)
        return -1;
    if (norm(q) > norm(p) + EPS)
        return 1;
    return 0;
}

inline bool seg_cross(const P& a, const P& b, const P& c, const P& d) {
    return (ccw(a, b, c) * ccw(a, b, d) <= 0 &&
            ccw(c, d, a) * ccw(c, d, b) <= 0);
}

inline bool poly_cross(const Polyline& a, const Polyline& b) {
    if (a.id == ~b.id)
        return false;
    return (seg_cross(a.a, a.b, b.a, b.b) ||
            seg_cross(a.b, a.c, b.a, b.b) ||
            seg_cross(a.a, a.b, b.b, b.c) ||
            seg_cross(a.b, a.c, b.b, b.c) );
}

template<class IN>
bool iterator_cross(IN a) {
    IN b = a;
    ++b;
    return (poly_cross(a->first, b->first));
}

int solve(vector<Event> events) {
    sort(ALLOF(events));

    map<Polyline, int> sw;
    typedef multimap<Polyline, int>::iterator Iterator;

    sw.insert(make_pair((Polyline){P(-INT_MAX, -INT_MAX), P(0, -INT_MAX), P(+INT_MAX, -INT_MAX)}, 1));
    sw.insert(make_pair((Polyline){P(-INT_MAX, +INT_MAX), P(0, +INT_MAX), P(+INT_MAX, +INT_MAX)}, 0));

    int res = 1;
    REP(iEvent, events.size()) {
        Event& e = events[iEvent];
        gx = e.x;
#if DBG
        printf("sweepline at %.3f:\n", gx);
        FOR(it, sw) {
            printf(" [%d] id=%s%d\ty=%.3f\n",
                   it->second,
                   (it->first.id < 0 ? "~" : ""),
                   (it->first.id < 0 ? ~it->first.id : it->first.id),
                   interpolate(it->first, gx));
        }
        printf("\n");
#endif
#if VERIFY
        {
            int lv = 0;
            double ly = -INT_MAX;
            FOR(it, sw) {
                assert(abs(it->second-lv) == 1);
                lv = it->second;
                double y = interpolate(it->first, gx);
                assert(ly <= y + EPS);
                ly = y;
            }
        }
#endif

        switch(e.type) {
        case OPEN: {
            assert(abs(interpolate(e.lower, gx)-interpolate(e.upper, gx)) < EPS);
            Iterator itlower = sw.insert(make_pair(e.lower, -1)).first;
            Iterator itupper = sw.insert(make_pair(e.upper, -1)).first;
            --itupper;
            if (itlower != itupper) {
#if DBG
                printf("error: not adjacent insertion\n");
#endif
                return -1;
            }
            ++itupper;
            --itlower;
            int level = itlower->second + 1;
            ++itlower;
#if VERIFY
            ++itupper;
            assert(itupper->second == level-2 || itupper->second == level);
            --itupper;
#endif
            itlower->second = level;
            itupper->second = level-1;
            --itlower;
            if (iterator_cross(itlower) || iterator_cross(itupper)) {
#if DBG
                printf("error: crossed with neighbor\n");
#endif
                return -1;
            }
            res >?= level;
            break;
        }
        case CLOSE: {
            sw.erase(e.lower);
            sw.erase(e.upper);
            Iterator it = sw.lower_bound(e.lower);
            --it;
            if (iterator_cross(it)) {
#if DBG
                printf("error: crossed after deletion\n");
#endif
                return -1;
            }
            break;
        }
        }
    }

    return res;
}

int main() {

    FILE* fp = freopen("painter.in", "r", stdin);
    assert(fp);
#if DBG
    mp = fopen("painter.mp", "w");
    fprintf(mp, "u := 15;\n\n");
#endif

    int iCase = 0;

    for(;;) {

        int n;
        scanf("%d", &n);

        if (n < 0)
            break;

        printf("Case %d: ", ++iCase);
#if DBG
        fprintf(mp, "beginfig(%d)\n", iCase);
        fprintf(mp, "for i := 0 upto 10: draw (i*u,0u)--(i*u,20u) withcolor 0.5white; draw (0u,i*u)--(20u,i*u) withcolor 0.5white; endfor\n");
#endif

        int res = 0;
        set<P> points;
        vector<Event> events;
        //const P rot = polar(1.0, 0.01);
        const P rot = polar(1.0, 0.01);
        REP(i, n) {
            P p = readPoint();
            P q = readPoint();
            P r = readPoint();
#if DBG
            fprintf(mp, "draw (%.0fu,%.0fu)--(%.0fu,%.0fu)--(%.0fu,%.0fu)--cycle;\n",
                    p.real(), p.imag(), q.real(), q.imag(), r.real(), r.imag());
#endif
            p *= rot;
            q *= rot;
            r *= rot;
            if (p.real() > q.real())
                swap(p, q);
            if (q.real() > r.real())
                swap(q, r);
            if (p.real() > q.real())
                swap(p, q);
            P s(q.real(), interpolate(p, r, q.real()));
            if (s.imag() > q.imag())
                swap(s, q);
            if (!points.insert(p).second ||
                !points.insert(q).second ||
                !points.insert(r).second ||
                !points.insert(s).second) {
                res = -1;
            }
            Event e;
            e.lower = (Polyline){p, s, r, ~i};
            e.upper = (Polyline){p, q, r, i};
            e.x = p.real();
            e.type = OPEN;
            events.push_back(e);
            e.x = r.real();
            e.type = CLOSE;
            events.push_back(e);
        }

        if (res == 0)
            res = solve(events);

        if (res < 0)
            printf("ERROR\n");
        else
            printf("%d shade%s\n", res, (res > 1 ? "s" : ""));

#if DBG
        fprintf(mp, "endfig;\n");
#endif

    }

#if DBG
    fprintf(mp, "end.\n");
#endif

    return 0;
}
