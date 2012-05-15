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

#define N 200

typedef complex<double> P;
typedef P Range;

P center[N];
double radius[N];
int n;

P go(P bl, P tr, double resol) {
    P rect = tr - bl;
    double area = rect.real()*rect.imag();
    if (max(rect.real(), rect.imag()) < resol)
        return P(0, area);
    P vs[4] = {bl, tr,
               P(bl.real(), tr.imag()),
               P(tr.real(), bl.imag())};
    bool freedom = true;
    REP(i, n) {
        P cen = center[i];
        double r = radius[i];
        if (bl.real() < cen.real() && cen.real() < tr.real() &&
            bl.imag()-r < cen.imag() && cen.imag() < tr.imag()+r)
            freedom = false;
        if (bl.imag() < cen.imag() && cen.imag() < tr.imag() &&
            bl.real()-r < cen.real() && cen.real() < tr.real()+r)
            freedom = false;
        int cnt = 0;
        REP(k, 4)
            if (abs(vs[k]-cen) < r)
                cnt++;
        if (cnt == 4)
            return P(0, 0);
        if (cnt > 0)
            freedom = false;
    }
    if (freedom)
        return P(area, area);
    P mi = (bl + tr) * 0.5;
    P bot(mi.real(), bl.imag()),
        lft(bl.real(), mi.imag()),
        rit(tr.real(), mi.imag()),
        top(mi.real(), tr.imag());
    return (go(bl, mi, resol) +
            go(bot, rit, resol) +
            go(lft, top, resol) +
            go(mi, tr, resol));
}
P draw(P bl, P tr, double resol) {
    P rect = tr - bl;
    double area = rect.real()*rect.imag();
    P tl(bl.real(), tr.imag()), br(tr.real(), bl.imag());
    if (max(rect.real(), rect.imag()) < resol) {
        cout << "draw " << bl << "--" << br << "--" << tr << "--" << tl << "--cycle;" << endl;
        return P(0, area);
    }
    P vs[4] = {bl, tr, tl, br};
    bool freedom = true;
    REP(i, n) {
        P cen = center[i];
        double r = radius[i];
        if (bl.real() < cen.real() && cen.real() < tr.real() &&
            bl.imag()-r < cen.imag() && cen.imag() < tr.imag()+r)
            freedom = false;
        if (bl.imag() < cen.imag() && cen.imag() < tr.imag() &&
            bl.real()-r < cen.real() && cen.real() < tr.real()+r)
            freedom = false;
        int cnt = 0;
        REP(k, 4)
            if (abs(vs[k]-cen) < r)
                cnt++;
        if (cnt == 4) {
            cout << "draw " << bl << "--" << br << "--" << tr << "--" << tl << "--cycle;" << endl;
            return P(0, 0);
        }
        if (cnt > 0)
            freedom = false;
    }
    if (freedom) {
        cout << "draw " << bl << "--" << br << "--" << tr << "--" << tl << "--cycle;" << endl;
        return P(area, area);
    }
    P mi = (bl + tr) * 0.5;
    P bot(mi.real(), bl.imag()),
        lft(bl.real(), mi.imag()),
        rit(tr.real(), mi.imag()),
        top(mi.real(), tr.imag());
    return (draw(bl, mi, resol) +
            draw(bot, rit, resol) +
            draw(lft, top, resol) +
            draw(mi, tr, resol));
}

int main() {

    for(;;) {
        double w, h;
        int ns, nl;
        scanf("%lf%lf%d%d", &w, &h, &ns, &nl);
        if (w == 0)
            break;

        n = 0;
        REP(i, ns) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            center[n] = P(x, y);
            radius[n] = 0.58;
            n++;
        }
        REP(i, nl) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            center[n] = P(x, y);
            radius[n] = 1.31;
            n++;
        }

        Range r(0, 1e10);
        double resolution;
        for(resolution = 0.01; (r.imag()-r.real()) > 5e-3; resolution *= 0.25) {
            r = go(P(0, 0), P(w, h), resolution);
        }

        //draw(P(0, 0), P(w, h), resolution);

        printf("%.2f\n", (r.real()+r.imag())/2);
    }

    return 0;
}
