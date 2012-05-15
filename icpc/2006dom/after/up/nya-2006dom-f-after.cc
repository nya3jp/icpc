/*
 * 2006 Japan Domestic Contest
 * Problem F - Secrets in Shadows
 *
 * 都合上、太陽はX=+∞、射影はY軸に行う
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> P;

// 浮動点小数の比較
#define EP 1.0e-12
inline int SGN(double x) { return (x < -EP ? -1 : x > EP ? 1 : 0); }
inline int EQ(double a, double b) { return (SGN(a-b) == 0); }
inline int LE(double a, double b) { return (SGN(a-b) <= 0); }
inline int LT(double a, double b) { return (SGN(a-b) <  0); }

// πは3.1以上である
const double PI = acos(0.0) * 2.0;

// 数直線上の範囲[first,second]を示す
typedef pair<double, double> Interval;


// 角度を[0,π)に正規化する
double normalize_angle(double angle) {
    while(LE(PI, angle))
        angle -= PI;
    while(LT(angle, 0))
        angle += PI;
    if (LE(angle, 0))
        angle = 0.0;
    return angle;
}


// 柱の集合を受け取って、影の長さと、影の左端・右端に対応する柱を計算する
// 左端に対応する柱はsgn=-1,右端に対応する柱はsgn=1になる
// それ以外はsgn=0
double interval_scan(vector<P>& points, vector<int>& sgns) {

    int n = points.size();

    // Y軸に射影する
    vector< pair<Interval, int> > intervals;
    for(int i = 0; i < n; i++)
        intervals.push_back(make_pair(make_pair(points[i].imag()-1, points[i].imag()+1),
                                      i));

    sort(intervals.begin(), intervals.end());

    double sum = 0.0;
    sgns.assign(n, 0);

    // 左側から走査
    int left = 0, right = 0; // 今見ている影の左端,右端に対応する柱のインデックス
    for(int i = 1; i < n; i++) {
        if (LT(intervals[right].first.second, intervals[i].first.first)) {
            sgns[intervals[left].second]--;
            sgns[intervals[right].second]++;
            sum += intervals[right].first.second - intervals[left].first.first;
            left = i; right = i;
        }
        else if (intervals[right].first.second < intervals[i].first.second) {
            right = i;
        }
    }
    sgns[intervals[left].second]--;
    sgns[intervals[right].second]++;
    sum += intervals[right].first.second - intervals[left].first.first;

    return sum;
}



int main() {

    for(int n; cin >> n && n > 0; ) {

        // よみこみ
        vector<P> points(n);
        for(int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            points[i] = P(x, y);
        }
        // C0を原点に持ってくる
        for(int i = 1; i < n; i++)
            points[i] -= points[0];
        points[0] = P(0, 0);


        // 影の端点が一致するような角度を列挙
        vector<double> sunAngles;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                P c1 = points[i];
                P c2 = points[j];
                double ar = arg(c2-c1);
                double d = abs(c2-c1);
                double th = asin(2.0/d);
                sunAngles.push_back(ar);
                sunAngles.push_back(ar+th);
                sunAngles.push_back(ar-th);
            }
        }
        // あと、影の動きが折り返す点にも注目
        for(int i = 1; i < n; i++)
            sunAngles.push_back(arg(points[i]) + PI/2);


        // ソート＆ユニーク 0, PIを仕込んでおく
        transform(sunAngles.begin(), sunAngles.end(), sunAngles.begin(), normalize_angle);
        sunAngles.push_back(0.0);
        sunAngles.push_back(PI);
        sort(sunAngles.begin(), sunAngles.end());
        sunAngles.erase(unique(sunAngles.begin(), sunAngles.end(), EQ), sunAngles.end());


        // 各角度に対する結果 pair< Sum, Theta >
        vector< pair<double, double> > results;

        // 角度区間の走査
        for(int iAngle = 0; iAngle < (int)sunAngles.size() - 1; iAngle++) {

            double baseAngle = sunAngles[iAngle];
            double halfAngle = (sunAngles[iAngle+1] + sunAngles[iAngle]) / 2;

            // 区間の中間の角度の様子からsgnを決定する
            vector<int> sgns(n, 0);
            {
                vector<P> v(points);
                for(int i = 0; i < n; i++)
                    v[i] *= polar(1.0, -halfAngle);
                interval_scan(v, sgns);
            }

            // 方程式はcoefSin*sin(θ) + coefCos*cos(θ) = 0
            double coefSin = 0.0, coefCos = 0.0;
            for(int i = 0; i < n; i++) {
                // 影幅への寄与(sgn) * 微分係数
                coefSin += sgns[i] * -points[i].imag();
                coefCos += sgns[i] * points[i].real();
            }
            double checkAngle = -atan2(-coefCos, coefSin);

            // 求まった角度と端角度について影の長さを求める
            {
                double sunAngle = checkAngle;
                vector<P> v(points);
                for(int i = 0; i < n; i++)
                    v[i] *= polar(1.0, -sunAngle);
                double sum = interval_scan(v, sgns);
                results.push_back(make_pair(sum, sunAngle));
            }
            {
                double sunAngle = baseAngle;
                vector<P> v(points);
                for(int i = 0; i < n; i++)
                    v[i] *= polar(1.0, -sunAngle);
                double sum = interval_scan(v, sgns);
                results.push_back(make_pair(sum, sunAngle));
            }
        }

        // おーわりっ
        sort(results.begin(), results.end());

        printf("%.15f\n", normalize_angle(-results.front().second));
        printf("%.15f\n", normalize_angle(-results.back().second));

    }

    return 0;
}

