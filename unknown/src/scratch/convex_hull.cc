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

typedef complex<double> P;
typedef vector<P> G;
const double EPS = 1.0e-8;

// 一直線・重複はしないこと！
bool p_equal(const P& a, const P& b) {
    return (abs(a-b) < EPS);
}


/*
    sort(ALLOF(v), xy_less);
    v.erase(unique(ALLOF(v), p_equal), v.end());
    bool linear = true;
    for(int i = 2; i < n; i++)
        if (abs(arg((v[i]-v[0])/(v[1]-v[0]))) > EPS)
            linear = false;
    assert(!linear);
*/

bool arg_less(const P& a, const P& b) { return (arg(a) < arg(b)); }
vector<P> convex_hull(vector<P> v) {
    int n = v.size();
    P g(EPS, 0);
    REP(i, n) g += v[i] / (double)n;
    REP(i, n) v[i] -= g;
    sort(ALLOF(v), arg_less);
    P first = v[0];
    REP(i, n) if (v[i].real() < first.real()) first = v[i];
    rotate(v.begin(), find(ALLOF(v), first), v.end());
    v.push_back(first);
    int m = 2;
    for(int i = 2; i <= n; v[m++] = v[i++])
        while(m >= 2 && (conj(v[m-1]-v[m-2])*(v[i]-v[m-2])).imag() < EPS)
            m--;
    v.resize(--m);
    REP(i, m) v[i] += g;
    return v;
}

bool xy_less(const P& a, const P& b) {
    if (abs(a.imag()-b.imag()) < EPS)
        return a.real() < b.real();
    return a.imag() < b.imag();
}

double ccw(P a, P b, P c) {
    return (conj(b-a)*(c-a)).imag();
}
template<class IN>
void walk_rightside_nya(IN begin, IN end, vector<P>& v) {
    IN cur = begin;
    v.push_back(*cur++);
    vector<P>::size_type s = v.size();
    v.push_back(*cur++);
    while(cur != end) {
        if (v.size() == s || ccw(v[v.size()-2], v.back(), *cur) > EPS)
            v.push_back(*cur++);
        else
            v.pop_back();
    }
    v.pop_back();
}

vector<P> convex_hull_nya(vector<P> v) {
    sort(ALLOF(v), xy_less);
    vector<P> cv;
    walk_rightside_nya(v.begin(), v.end(), cv);
    walk_rightside_nya(v.rbegin(), v.rend(), cv);
    return cv;
}


typedef complex<double> xy;
typedef vector<xy> polygon;

/*
double ccw(xy p1, xy p2, xy p3)
{
    p2-=p1; p3-=p1;
    return imag(conj(p2)*p3);
}
*/

bool xy_sorter(const xy &a, const xy &b)
{
    if (abs(a.imag()-b.imag()) < EPS)
        return a.real() < b.real();
    return a.imag() < b.imag();
}
template<typename IN>
void walk_rightside(IN begin, IN end, polygon &ch)
{
    IN cur=begin;
    ch.push_back(*cur++);
    polygon::size_type s = ch.size();
    ch.push_back(*cur++);
    while ( cur!=end ){
        if ( ccw(ch[ch.size()-2],ch.back(),*cur)>EPS )
            ch.push_back(*cur++);
        else {
            ch.pop_back();
            if ( ch.size()==s )
                ch.push_back(*cur++);
        }
    }
    ch.pop_back();
}

polygon convexHull(polygon po)
{
    sort(po.begin(), po.end(), xy_sorter);
    polygon ch;
    walk_rightside(po.begin(), po.end(), ch);
    walk_rightside(po.rbegin(), po.rend(), ch);
    return ch;
}

double rand_real() {
    return rand() / (RAND_MAX + EPS);
}

bool table[100][100];

int main() {

    int n = 10;
    vector<P> v(n);

    int iCase = 0;
    for(;;) {

        REP(i, n) {
            double x, y;
            do {
                x = (int)(10 * rand_real());
                y = (int)(10 * rand_real());
            } while(table[(int)x][(int)y]);
            table[(int)x][(int)y] = true;
            v[i] = P(x, y);
        }
        REP(i, 10) {
            REP(j, 10) {
                fprintf(stderr, "%c", (table[j][10-1-i] ? '*' : '.'));
            }
            fprintf(stderr, "\n");
        }
        REP(i, n)
            table[(int)v[i].real()][(int)v[i].imag()] = false;

        vector<P> res1 = convex_hull_nya(v);
        vector<P> res2 = convexHull(v);

        rotate(res1.begin(), min_element(ALLOF(res1), xy_less), res1.end());
        rotate(res2.begin(), min_element(ALLOF(res2), xy_less), res2.end());

        bool match = true;
        if (match && res1.size() != res2.size()) {
            match = false;
        }
        if (match) {
            REP(i, res1.size()) {
                if (abs(res1[i]-res2[i]) > EPS)
                    match = false;
            }
        }

        if (!match) {
            fprintf(stderr, "Case %d Failed.\n", iCase+1);
            fprintf(stderr, "Unknown's answer:");
            REP(i, res1.size())
                printf(" (%.3f,%.3f)", res1[i].real(), res1[i].imag());
            printf("\n");
            fprintf(stderr, "GNC's answer:    ");
            REP(i, res2.size())
                printf(" (%.3f,%.3f)", res2[i].real(), res2[i].imag());
            printf("\n");

            printf("%d\n", n);
            REP(i, n)
                printf("%.20f %.20f\n", v[i].real(), v[i].imag());
            printf("\n\n");
            break;
        }
        else {
            fprintf(stderr, "Case %d Passed.\n", iCase+1);
        }

        iCase++;
    }

    return 0;
}
