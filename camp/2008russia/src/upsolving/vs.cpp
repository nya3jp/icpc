#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <map>
#include <numeric>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "vs"

#define EPS 1.0e-10

typedef complex<double> P;
struct L { P a, b; };

namespace std {
    bool operator<(const P& a, const P& b) {
        if (abs((a-b).real()) > EPS)
            return (a-b).real() < 0;
        if (abs((a-b).imag()) > EPS)
            return (a-b).imag() < 0;
        return false;
    }
}

bool nearly_equal(const P& a, const P& b) {
    return (abs(a-b) < EPS);
}

double inp(P a, P b) {
    return (conj(a)*b).real();
}

double outp(P a, P b) {
    return (conj(a)*b).imag();
}

bool line_parallel(const L& li, const L& lj) {
    return (abs(outp(lj.b-lj.a, li.b-li.a)) < EPS);
}

P line_cross(const L& li, const L& lj) {
    double num = outp(lj.b-lj.a, lj.a-li.a);
    double denom = outp(lj.b-lj.a, li.b-li.a);
    return li.a + (li.b-li.a)*num/denom;
}

bool by_arg(const P& a, const P& b) {
    return arg(a) < arg(b);
}

struct Edge {
    int src, dest;
    double inarg, outarg;
    bool circular;
    bool seen;
};

const double PI = acos(0.0)*2;

double norm_arg(double x) {
    while(x >= 2*PI-EPS)
        x -= 2*PI;
    while(x < -EPS)
        x += 2*PI;
    return x;
}

double go(double* areas, int n, double alpha = -1e100, double beta = 1e100, double t = 0, int turn = 1) {
    if (n == 0)
        return 0;
    if (t < -EPS*turn)
        return -go(areas, n, -beta, -alpha, -t, -turn);
    REP(i, n) {
        double k = areas[i];
        swap(areas[i], areas[n-1]);
        alpha >?= k + go(areas, n-1, alpha-k, beta-k, t-k, turn);
        swap(areas[i], areas[n-1]);
        if (alpha >= beta)
            break;
    }
    return alpha;
}



int main() {

    if (0) {
        vector<double> v;
        v.push_back(2);
        v.push_back(5);
        v.push_back(9);
        v.push_back(10);
        cout << go(&v[0], v.size()) << endl;
        return 0;
    }

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    int n;
    double R;
    cin >> n >> R;

    vector<L> lines;
    REP(i, n) {
        int a, b, c;
        cin >> a >> b >> c;
        P d(-b, a);
        P p(a, b);
        p /= norm(p);
        p *= c;
        double D = inp(p, d)*inp(p, d)-inp(d, d)*(inp(p, p)-R*R);
        double ta = (-inp(p, d)+sqrt(D))/inp(d, d);
        double tb = (-inp(p, d)-sqrt(D))/inp(d, d);
        P pa = p + ta * d;
        P pb = p + tb * d;
        lines.push_back((L){pa, pb});
        assert(abs(abs(pa)-R) < EPS);
        assert(abs(abs(pb)-R) < EPS);
    }

    vector<P> points;
    REP(i, n) {
        points.push_back(lines[i].a);
        points.push_back(lines[i].b);
    }

    REP(i, n) REP(j, i) {
        L la = lines[i], lb = lines[j];
        if (!line_parallel(la, lb)) {
            P c = line_cross(la, lb);
            points.push_back(c);
        }
    }

    sort(ALLOF(points));
    points.erase(unique(ALLOF(points), nearly_equal), points.end());

    int m = points.size();
    map<P, int> ids;
    REP(i, m)
        ids[points[i]] = i;

    /*
    REP(i, m)
        cerr << "pt" << i << ": " << points[i] << endl;
    */

    vector< vector<Edge> > g(m);
    {
        vector<P> circular;
        REP(i, m) {
            P p = points[i];
            if (abs(abs(p)-R) < EPS)
                circular.push_back(p);
        }
        sort(ALLOF(circular), by_arg);

        int k = circular.size();
        /*
        cerr << "circular points:";
        REP(i, k)
            cerr << " " << circular[i];
        cerr << endl;
        */

        REP(i, k) {
            int j = (i+1)%k;
            int a = ids[circular[i]];
            int b = ids[circular[j]];
            g[a].push_back((Edge){a, b, arg(circular[i]*P(0, 1)), arg(circular[j]*P(0, 1)), true, false});
            //g[b].push_back((Edge){b, a, arg(circular[j]*P(0, -1)), arg(circular[i]*P(0, -1)), true, false});
            //cerr << "circular " << a << "-" << b << endl;
        }
    }

    REP(l, n) {
        L line = lines[l];
        vector<P> onlines;
        REP(i, m) {
            P p = points[i];
            if (abs(p-line.a)+abs(p-line.b)-abs(line.a-line.b) < EPS)
                onlines.push_back(p);
        }
        sort(ALLOF(onlines));
        int k = onlines.size();
        REP(i, k-1) {
            int j = i + 1;
            int a = ids[onlines[i]];
            int b = ids[onlines[j]];
            g[a].push_back((Edge){a, b, arg(onlines[j]-onlines[i]), arg(onlines[j]-onlines[i]), false, false});
            g[b].push_back((Edge){b, a, arg(onlines[i]-onlines[j]), arg(onlines[i]-onlines[j]), false, false});
            //cerr << "linear " << a << "-" << b << endl;
        }
    }

    vector<double> areas;
    REP(iStartPoint, m) {
        REP(iStartEdge, g[iStartPoint].size()) {
            Edge& startEdge = g[iStartPoint][iStartEdge];
            if (!startEdge.seen) {
                vector<Edge> region;
                region.push_back(startEdge);
                //cerr << points[iStartPoint];
                startEdge.seen = true;
                Edge curEdge = startEdge;
                while(curEdge.dest != iStartPoint) {
                    //cerr << "-[" << curEdge.inarg*180/PI << "," << curEdge.outarg*180/PI << "]-" << points[curEdge.dest];
                    vector<Edge>& edges = g[curEdge.dest];
                    int iNextEdge = -1;
                    double rev_arg = curEdge.outarg + PI;
                    REP(i, edges.size())
                        if (abs(norm_arg(rev_arg-edges[i].inarg)) > EPS &&
                            (iNextEdge < 0 || norm_arg(rev_arg - edges[i].inarg) < norm_arg(rev_arg - edges[iNextEdge].inarg)))
                            iNextEdge = i;
                    assert(iNextEdge >= 0);
                    Edge& nextEdge = edges[iNextEdge];
                    //cerr << "{darg=" << norm_arg(rev_arg-nextEdge.inarg)*180/PI << "}";
                    assert(!nextEdge.seen);
                    nextEdge.seen = true;
                    region.push_back(nextEdge);
                    curEdge = nextEdge;
                }
                //cerr << "-[" << curEdge.inarg*180/PI << "," << curEdge.outarg*180/PI << "]-" << points[curEdge.dest];
                //cerr << endl;
                {
                    double area = 0;
                    REP(i, region.size()) {
                        Edge e = region[i];
                        P a = points[e.src];
                        P b = points[e.dest];
                        if (e.circular) {
                            double th = norm_arg(arg(b/a));
                            //cerr << "theta=" << th << endl;
                            area += PI*R*R * th / (2*PI);
                        }
                        else {
                            area += outp(a, b)/2;
                        }
                    }
                    if (abs(area-PI*R*R) > EPS) {
                        //cerr << "area=" << area << endl;
                        areas.push_back(area);
                    }
                }
            }
        }
    }

    double sum = accumulate(ALLOF(areas), 0.0);
    double res = go(&areas[0], areas.size());
    double res_a = (sum + res) / 2;
    double res_b = (sum - res) / 2;

    printf("%.10f %.10f\n", res_a, res_b);

    return 0;
}

