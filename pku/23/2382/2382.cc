#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Pt;

#define EP 1.0e-8

const double PI = acos(0.0)*2;

Pt readPoint() {
    double x, y;
    cin >> x >> y;
    return Pt(x, y);
}

struct C {
    Pt pt;
    double r;
};

double intersect_area(C& a, C& b) {
    double d = abs(a.pt - b.pt);
    double R = a.r;
    double r = b.r;
    if (r > R)
        swap(R, r);
    if (R+r+EP < d)
        return 0;
    if (d+r+EP < R)
        return PI*r*r;
    double X = (R*R - r*r + d*d) / 2d;
    double x = d - X;
    double h = sqrt(R*R - X*X);
    double TH = acos(X/R);
    double th = acos(x/r);
    return R*R*TH + r*r*th - d*h;
}

int main() {
    cin >> n;
    n++;

    vector<C> v(n);

    for(int i = 0; i < n; i++) {
        v[i].pt = readPoint();
        cin >> v[i].r;
    }

    vector< vector<double> > adj(n, vector<double>(n));
    for(int i = 0; i < n; i++) {
        adj[i][i] = PI * v[i].r * v[i].r;
        for(int j = i+1; j < n; j++) {
            adj[i][j] = adj[j][i] = intersect_area(v[i], v[j]);
        }
    }

    return 0;
}
