#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <complex>

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



void func(double d, double theta, vector<double>& thetas) {
    double th = asin(2/d);
    printf("th=%.4f\n", th);
    thetas.push_back(theta);
    thetas.push_back(theta+th);
    thetas.push_back(theta-th);
}


int main() {
    int n;
    while(cin >> n && n > 0) {
        vector<P> points(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            points[i] = P(x, y);
        }
        vector<double> thetas;
        thetas.push_back(0.0);
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                P c1 = points[i];
                P c2 = points[j];
                double d = abs(c1-c2);
                double deltaTheta = arg(c2-c1);
                func(d, deltaTheta, thetas);
            }
        }
        double maxTheta = -1, minTheta = -1, maxSum = -INF, minSum = INF;
        for(int tindex = 0; tindex < (int)thetas.size(); tindex++) {
            double theta = thetas[tindex];
            vector<Interval> intervals;
            for(int i = 0; i < n; i++) {
                P rotated = points[i] / polar(1.0, theta);
                intervals.push_back(make_pair(rotated.imag()-1.0, rotated.imag()+1.0));
            }
            double sum = interval_sum(intervals);
            printf("theta=%.3f sum=%.3f\n", theta, sum);
            if (sum > maxSum) {
                maxSum = sum;
                maxTheta = theta;
            }
            if (sum < minSum) {
                minSum = sum;
                minTheta = theta;
            }
        }

        minTheta = normtheta(minTheta);
        maxTheta = normtheta(maxTheta);

        printf("%.20f\n", minTheta);
        printf("%.20f\n", maxTheta);

        // format theta
    }
    return 0;
}
