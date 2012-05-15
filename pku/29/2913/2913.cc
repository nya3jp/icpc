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

#define EPS 1.0e-8
const double G = (-1.0+sqrt(5.0))/2.0;

struct P {
    double x, y, z;
};
istream& operator>>(istream& s, P& p) {
    s >> p.x >> p.y >> p.z;
    return s;
}
P scanp() {
    P p;
    scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
    return p;
}

P operator*(const P& a, double b) {
    return (P){a.x*b, a.y*b, a.z*b};
}
P operator+(const P& a, const P& b) {
    return (P){a.x+b.x, a.y+b.y, a.z+b.z};
}
P operator-(const P& a, const P& b) {
    return (P){a.x-b.x, a.y-b.y, a.z-b.z};
}
double inp(const P& a, const P& b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
double abs(const P& p) {
    return sqrt(inp(p, p));
}

double incos(double a, double b, double c) {
    return (a*a + b*b - c*c) / (2*a*b);
}
double area(double a, double b, double c) {
    double s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
double sp_distance(const P& s, const P& t, const P& p) {
    double a = abs(s-p), b = abs(t-p), c = abs(t-s);
    if (a+b-c < EPS)
        return 0;
    if (incos(c, a, b) >= 0 && incos(c, b, a) >= 0)
        return area(a, b, c) / c * 2;
    return min(a, b);
}


int main() {

    P s, t, u, v, p;
    double d;
    //while(cin >> s >> t >> u >> v >> p >> d) {
    for(;;) {
        s = scanp();
        t = scanp();
        u = scanp();
        v = scanp();
        p = scanp();
        if (scanf("%lf", &d) != 1)
            break;

        double len = abs(t-s);
        double pos = abs(p-s);

        double inf = max(pos-d, 0.0);
        double sup = min(pos+d, len);
        double upper = inf+(sup-inf)*G;
        double lower = sup-(sup-inf)*G;
        double x = sp_distance(u, v, s+(t-s)*(lower/len));
        double y = sp_distance(u, v, s+(t-s)*(upper/len));

        while(sup-inf > 1.0e-5) {
            //printf("%.15f ... %.15f\n", inf, sup);
            if (x < y) {
                sup = upper;
                upper = lower;
                lower = sup-(sup-inf)*G;
                y = x;
                x = sp_distance(u, v, s+(t-s)*(lower/len));
            }
            else {
                inf = lower;
                lower = upper;
                upper = inf+(sup-inf)*G;
                x = y;
                y = sp_distance(u, v, s+(t-s)*(upper/len));
            }
        }

        double res = sp_distance(u, v, s+(t-s)*(inf/len));
        printf("%.3f\n", res+EPS);

    }

    return 0;
}

// Powered by fate testarossa
