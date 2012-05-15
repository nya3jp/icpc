#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "art"

const double EPS = 1.0e-10;

typedef complex<double> P;

struct Rect {
    P lb, rt;
    inline double width() const { return (rt-lb).real(); }
    inline double height() const { return (rt-lb).imag(); }
};

P readPoint() {
    double x, y;
    cin >> x >> y;
    return P(x, y);
}

Rect readRect() {
    Rect r;
    r.lb = readPoint();
    r.rt = readPoint();
    return r;
}

bool nearly_equal(double a, double b) {
    return (abs(a-b) < EPS);
}


int ceil2(int n) {
    while(n&(n-1))
        n |= n+1;
    return n;
}

template<class T>
struct range_tree {
    int m;
    vector< pair<T, T> > tree;
    const T zero, inf;

    range_tree(int n, const T& zero, const T& inf) : zero(zero), inf(inf) {
        m = n;
        while(m&(m-1))
            m += m&-m;
        tree.assign(2*m, make_pair(zero, zero));
        for(int k = n; k < m; k++)
            tree[k] = make_pair(inf, inf);
        for(int k = m; k < 2*m-1; k++)
            tree[k] = make_pair(zero,
                                min(tree[((k&~m)<<1)^0].second,
                                    tree[((k&~m)<<1)^1].second));
    }
    void range_add(int a, int b, const T& d) {
        while(a < b) {
            int r = 1, k = a;
            while((a & r) == 0 && a + (r<<1) <= b) {
                r <<= 1;
                k = (k >> 1) | m;
            }
            tree[k].first += d;
            do {
                tree[k].second = tree[k].first +
                    (k < m ? zero :
                     min(tree[((k&~m)<<1)^0].second,
                         tree[((k&~m)<<1)^1].second));
                k = (k >> 1) | m;
            } while(k < 2*m-1);
            a += r;
        }
    }
    T range_min(int a, int b) {
        T res(inf);
        while(a < b) {
            int r = 1, k = a;
            while((a & r) == 0 && a + (r<<1) <= b) {
                r <<= 1;
                k = (k >> 1) | m;
            }
            res = min(res, tree[k].second);
            a += r;
        }
        return res;
    }
    T query(int k) {
        T res(zero);
        while(k < 2*m-1) {
            res += tree[k].first;
            k = (k >> 1) | m;
        }
        return res;
    }

    void print() {
        cout << "range_tree: m = " << m << ", tree = { ";
        REP(i, 2*m-1)
            cout << tree[i].first << "." << tree[i].second << " ";
        cout << "}" << endl;
    }
};




struct Event {
    double x;
    int i, j;
    int d;
};

bool operator<(const Event& a, const Event& b) {
    if (abs(a.x-b.x) > EPS)
        return (a.x < b.x);
    return (a.d < b.d);
}

P go(const Rect& white, const vector<Rect>& blacks, double ratio, double h, double w) {
    int n = blacks.size();
    double cutWidth = w * ratio;
    double cutHeight = h * ratio;
    Rect candArea = { white.rt - P(cutWidth, cutHeight), white.lb };

    candArea.lb = P(max(0.0, candArea.lb.real()), max(0.0, candArea.lb.imag()));
    candArea.rt = P(min(w-cutWidth, candArea.rt.real()), min(h-cutHeight, candArea.rt.imag()));

    //cerr << "ratio=" << ratio << endl;
    //cerr << cutWidth << "," << cutHeight << endl;
    //cerr << candArea.lb << "-" << candArea.rt << endl;

    vector<Rect> covers;
    REP(i, n) {
        Rect cov = blacks[i];
        cov.lb -= P(cutWidth, cutHeight);
        if (cov.lb.imag() < candArea.rt.imag() - EPS && candArea.lb.imag() < cov.rt.imag() - EPS) {
            //cerr << cov.lb << "-" << cov.rt << endl;
            /*
            cov.lb = P(cov.lb.real(),
                       max(cov.lb.imag(), candArea.lb.imag()));
            cov.rt = P(cov.rt.real(),
                       min(cov.rt.imag(), candArea.rt.imag()));
            */
            //cerr << " -> " << cov.lb << "-" << cov.rt << endl;
            covers.push_back(cov);
        }
    }
    //covers.push_back((Rect){candArea.lb+P(-1, -1), P(candArea.lb.real(), candArea.rt.imag()+1)});

    vector<double> ys;
    ys.push_back(candArea.lb.imag());
    ys.push_back(candArea.rt.imag());
    REP(i, covers.size()) {
        ys.push_back(covers[i].lb.imag());
        ys.push_back(covers[i].rt.imag());
    }
    sort(ALLOF(ys));
    ys.erase(unique(ALLOF(ys), nearly_equal), ys.end());

    int m = ys.size(); // without upperbound

    /*
    REP(i, m)
        cerr << "ys" << i << " = " << ys[i] << endl;
    */

    /*
    cerr << m << endl;
    REP(i, m)
        cerr << ys[i] << endl;
    //*/

    vector<Event> events;
    events.push_back((Event){candArea.lb.real()-1, 0, m, +1});
    events.push_back((Event){candArea.lb.real(),
                lower_bound(ALLOF(ys), candArea.lb.imag()-3*EPS)-ys.begin(),
                lower_bound(ALLOF(ys), candArea.rt.imag()+3*EPS)-ys.begin(),
                -1});
    /*if (m == 0) {
        m = 1;
        REP(i, covers.size()) {
            Rect& cov = covers[i];
            //cerr << cov.lb << "-" << cov.rt << endl;
            events.push_back((Event){cov.lb.real(),
                        0,
                        1,
                        +1});
            events.push_back((Event){cov.rt.real(),
                        0,
                        1,
                        -1});
        }
    }
    else */{
        REP(i, covers.size()) {
            Rect& cov = covers[i];
            //cerr << cov.lb << "-" << cov.rt << endl;
            events.push_back((Event){cov.lb.real(),
                        lower_bound(ALLOF(ys), cov.lb.imag()+3*EPS)-ys.begin(),
                        lower_bound(ALLOF(ys), cov.rt.imag()-3*EPS)-ys.begin(),
                        +1});
            events.push_back((Event){cov.rt.real(),
                        lower_bound(ALLOF(ys), cov.lb.imag()+3*EPS)-ys.begin(),
                        lower_bound(ALLOF(ys), cov.rt.imag()-3*EPS)-ys.begin(),
                        -1});
        }
    }
    sort(ALLOF(events));

    range_tree<int> tree(m, 0, 12345678);

    double beginline = candArea.lb.real();
    double endline = candArea.rt.real();

    REP(iEvent, events.size()) {
        Event& e = events[iEvent];
        /*
        cerr << e.x << ": (" << e.i << "," << e.j << ") " << e.d << ":";
        REP(i, m)
            cerr << " " << tree.query(i);
        cerr << endl;
        //*/

        if (e.x >= endline+EPS)
            break;
        tree.range_add(e.i, e.j, e.d);

        /*
        cerr << e.x << ": (" << e.i << "," << e.j << ") " << e.d << ":";
        REP(i, m)
            cerr << " " << tree.query(i);
        cerr << endl;
        //*/

        if (e.x >= beginline-EPS && e.d < 0) {
            //cerr << "range_min = " << tree.range_min(0, m) << endl;
            if (tree.range_min(0, m) == 0) {
                REP(i, m) if (tree.query(i) == 0)
                    return P(e.x, ys[i]);
            }
        }
    }
    //cerr << "impossible" << endl;

    return P(-1, -1);
}


int main() {

    /*
    range_tree<int> tree(5, 0, 123);

    tree.range_add(0, 3, 10);
    tree.print();
    tree.range_add(2, 4, 100);
    tree.print();
    tree.range_add(3, 5, 5);
    tree.print();

    REP(i, 5)
        cout << tree.query(i) << endl;

    return 0;
    */

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
#ifndef LOCAL
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();
#endif

#ifdef LOCAL
    for(;;) {
#endif
    double h, w;
    cin >> w >> h;

    if (!cin)
        return 0;

    Rect white = readRect();

    int n;
    cin >> n;
    vector<Rect> blacks(n);
    REP(i, n)
        blacks[i] = readRect();

    P lb;
    double lo = max(white.width() / w, white.height() / h), hi = 1;
    //double lo = 0.5-6e-13, hi = 0.5+6e-13;
    double res = -1;

    lb = go(white, blacks, 1, h, w);
    //cerr << lb << endl;
    if (lb.real() >= -0.5)
        res = 1;

    while(hi-lo > 1e-14) {
        //cerr << "==================== " << lo << " " << hi << endl;
        double mid = (lo+hi)/2;
        P p = go(white, blacks, mid, h, w);
        if (p.real() < -0.5) {
            hi = mid;
        }
        else {
            lo = mid;
            lb = p;
            res = mid;
        }
    }

    if (res < -0.5) {
        puts("-1");
    }
    else {
        printf("%.10f\n", res);
        printf("%.10f %.10f\n", lb.real(), lb.imag());
    }

#ifdef LOCAL
    }
#endif

    return 0;
}

