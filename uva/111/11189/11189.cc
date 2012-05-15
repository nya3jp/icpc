#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>
#include <cstdio>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef complex<double> P;

const double G = 981;
const double PI = acos(0.0) * 2;
const double EPS = 1.0e-9;

istream& operator>>(istream& in, P& p) {
    double x, y;
    in >> x >> y;
    p = P(x, y);
    return in;
}

int solve(double len, double period, const P* convex) {

    P g(0);
    REP(i, 4)
        g += convex[i];
    g /= 4.0;

    double inside = G * pow(period / (2*PI), 2.0) - len;

    printf("%.3f: \n", inside);

    double area = 0.0;
    REP(i, 4) {
        P p = convex[i];
        P q = convex[(i+1)%4];
        area += (conj(p)*q).imag() / 2;
    }
    area = abs(area);

    REP(i, 4) REP(j, 4) if (i < j) {
        assert(abs(convex[i]-convex[j]) > EPS);
    }

    if (area < EPS) {
        double width = 0;
        REP(i, 4) REP(j, 4)
            width >?= abs(convex[i]-convex[j]);
        if (inside < width/2)
            return 2;
        return 0;
    }

    int res = 0;

    REP(i, 4) {
        P p = convex[i];
        P q = convex[(i+1)%4];

        double left = abs(p-g);
        double right = abs(q-g);
        double ratio = (conj(g-p)*(q-p)).real()/norm(q-p);
        double middle = abs(g-((q-p)*ratio+p));
        if (ratio < 0 || ratio > 1)
            middle = min(left, right);

        printf("(%.3f, %.3f, %.3f) ", left, middle, right);

        if (middle+EPS < inside) {
            if (inside+EPS < min(left, right)) {
                res += 2;
            }
            else if (inside+EPS < max(left, right)) {
                res += 1;
            }
        }
    }

    printf("\n");

    assert(res%2 == 0);
    return res;
}

int main() {

    for(int iCase = 0; ; iCase++) {

        double len, period;
        cin >> len >> period;

        if (len <= 0.5)
            break;

        P convex[4];
        REP(i, 4)
            cin >> convex[i];

        int res = solve(len, period, convex);

        printf("Pendulum %d: ", iCase+1);
        if (res == 0)
            printf("No\n");
        else
            printf("Yes %d\n", res);
    }


    return 0;
}

