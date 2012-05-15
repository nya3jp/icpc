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

typedef long double decimal;
typedef complex<decimal> P;

const decimal PI = acos((decimal)0.0) * 2;
const decimal EPS = 1.0e-9;

int main() {

    for(;;) {
        int n;
        decimal r;

        cin >> n >> r;
        if (n == 0 && r == 0)
            break;

        vector<decimal> angles(n);
        REP(i, n) {
            decimal deg;
            cin >> deg;
            angles[i] = deg * PI / 180;
        }

        sort(angles.begin(), angles.end());

        vector<P> v(n);
        REP(i, n) {
            v[i] = polar(r, angles[i]);
        }

        P sum = 0;
        /*
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                for(int k = j+1; k < n; k++) {
                    sum += conj(v[j]-v[i])*(v[k]-v[i]);
                }
            }
        }
        */
        for(int i = 0; i < n; i++) {
            P local = 0;
            for(int j = n-1; j > i; j--) {
                sum += conj(v[j]-v[i])*local;
                local += v[j] - v[i];
            }
        }

        printf("%.0f\n", (double)(sum.imag() / 2.0));

    }

    return 0;
}

