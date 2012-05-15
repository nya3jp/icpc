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

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

using namespace std;

#define EPS 1e-10

double
solve(int m, int p, double a, double b)
{
    double A = sqrt(a);
    double S = b * A;
    int k = (int)floor((S*A + m) / (A * A + 1) + EPS);
    int l = m - k - 1;
    if (k == m) {
        return k * pow(A, p);
    }

    double q = S - k * A + l * (1.0 / A);
    return k * pow(A, p) + l * (1.0 / pow(A, p)) + pow(q, p);
}

int main(void)
{
    freopen("maximum.in", "r", stdin);
    int m, p;
    double a,b;
    while (cin >> m >> p >> a >> b) {
        printf("%.03f\n", solve(m, p, a, b));
    }
}
