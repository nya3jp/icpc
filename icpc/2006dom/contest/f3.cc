#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <complex>
#include <limits>

using namespace std;

typedef pair<double,double> Interval;

#define EP 1.0e-8
inline int SGN(double a) {
    return (a < -EP ? -1:
            a > EP ? 1:
            0);
}
#define LE(a,b) (SGN(a-b) <= 0)
#define LT(a,b) (SGN(a-b) < 0)
typedef complex<double> P;

const double PI = acos(0.0)*2.0;
const double INF = 1.0e100;

double transtheta(double th) {
    return PI - th;
}

double normtheta(double th) {
    while(th > PI)
        th -= PI;
    while(LT(th, 0))
        th += PI;
    if (th < 0)
        th = 0;
    return th;
}

double interval_sum(vector<Interval>& s) {


    sort(s.begin(), s.end());

    /*
    for(int i = 0; i < (int)s.size(); i++) {
        printf("(%.2f,%.2f) ", s[i].first, s[i].second);
    }
    printf("\n");
    */

    bool exists = false;
    /*
    Interval last = make_pair(numeric_limits<double>::min(),
                              numeric_limits<double>::min());
    */
    Interval last = make_pair(-INF, -INF);

    double sum = 0.0;
    for(int i = 0; i < (int)s.size(); i++) {
        Interval& iv = s[i];
        if (LE(iv.first, last.second)) {
            //printf("hoge\n");
            last.second = max(last.second, iv.second);
        }
        else {
            //printf("piyo\n");
            if (exists) {
                sum += last.second-last.first;
            }
            last = iv;
            exists = true;
        }
    }

    if (exists) {
        sum += last.second-last.first;
    }

    return sum;
}



int main() {
    int n;


    while(cin >> n && n > 0)  {

        vector<P> points(n);
        for(int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            points[i] = P(x, y);
        }

        vector<double> thetas;
        thetas.push_back(0.0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++ ){
                P c1 = points[i];
                P c2 = points[j];
                double d = abs(c1-c2);
                double baseTheta = arg(c2-c1);
                //printf("norm=%.3f\n", d);
                double addTheta = asin(2.0/d);
                thetas.push_back(baseTheta);
                thetas.push_back(baseTheta+addTheta);
                thetas.push_back(baseTheta-addTheta);
            }
        }

        {
            int m = thetas.size();
            for(int i = 0; i < m; i++) {
                thetas.push_back(thetas[i]+PI/2);
            }
        }

        vector<double> sums;
        for(int i = 0; i < (int)thetas.size(); i++) {
            double th = thetas[i];
            vector<Interval> intervals;
            //printf("theta=%.3f\n", th);
            for(int j = 0; j < n; j++) {
                P c = points[j];
                c = c * polar(1.0, -th);
                Interval iv = make_pair(c.imag()-1.0, c.imag()+1.0);
                //printf("%.3f-%.3f\n", iv.first, iv.second);
                intervals.push_back(iv);
            }
            //printf("\n");
            sums.push_back(interval_sum(intervals));
        }

        printf("%.20f\n", transtheta(normtheta(thetas[min_element(sums.begin(), sums.end()) - sums.begin()])));
        printf("%.20f\n", transtheta(normtheta(thetas[max_element(sums.begin(), sums.end()) - sums.begin()])));

    }



    return 0;
}

