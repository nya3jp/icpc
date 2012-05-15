#include <iostream>
#include <vector>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()


typedef complex<double> P;

const double EPS = 1.0e-10;


int main() {

    for(;;) {
        int n;
        cin >> n;
        if (n == 0)
            break;

        vector<P> v(n);
        REP(i, n) {
            double x, y;
            cin >> x >> y;
            v[i] = P(x, y);
        }

        int res = 1;

        REP(i, n) REP(j, i) {
            P p1 = v[i], p2 = v[j];
            if (abs(p2-p1) > 2)
                continue;
            P center = (p1 + p2) / 2.0;
            P normal = (p2 - p1) / abs(p2 - p1);
            double d_half = abs(p2 - p1) / 2;
            double r = 1.0;
            double len = sqrt(r*r - d_half*d_half);
            {
                P c = center + normal*P(0, 1)*len;
                int local = 0;
                REP(k, n) {
                    if (abs(v[k]-c) <= r+EPS)
                        local++;
                }
                res >?= local;
            }
            {
                P c = center + normal*P(0, -1)*len;
                int local = 0;
                REP(k, n) {
                    if (abs(v[k]-c) <= r+EPS)
                        local++;
                }
                res >?= local;
            }
        }

        cout << res << endl;
    }


    return 0;
}

