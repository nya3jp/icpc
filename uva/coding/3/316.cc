#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <functional>

using namespace std;

#define EP 1.0e-8

typedef complex<int> Pi;
typedef complex<double> P;

namespace std {
    bool operator<(const Pi& a, const Pi& b) {
        return (a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag());
    }
}

P toP(const Pi& a) {
    return P(a.real(), a.imag());
}

bool intic(double d) {
    return abs((int)(d+0.5)-d) < EP;
}

int main() {
    int n;
    while(cin >> n && n != 0) {
        vector<Pi> v(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            v[i] = Pi(x, y);
        }
        int nc;
        cin >> nc;
        for(int ic = 0; ic < nc; ic++) {
            int s;
            string name;
            cin >> s >> name;
            vector<Pi> u(s);
            for(int i = 0; i < s; i++) {
                int x, y;
                cin >> x >> y;
                u[i] = Pi(x, y);
            }

            if (s == 1) {
            }
            else {
                P d0 = toP(u[1] - u[0]);
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                        if (i == j) continue;
                        P d1 = toP(v[j] - v[i]);
                        try {
                            for(int k = 2; k < s; k++) {
                                P mp = toP(u[k]-u[0])*d1/d0+v[i];
                                if (intic(mp)) {
                                    Pi mpi = toPi(mp);
                                    if (!binary_search(v.begin(), v.end(), mpi))
                                        throw 1;
                                }
                            }
                            throw "OK";
                        }
                        catch(int) {
                        }
                    }
                }
            }
        }
    }
    return 0;
}

