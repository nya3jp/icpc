#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <complex>
#include <limits>
#include <cstdio>

using namespace std;

#define REP(i, n) for(int i = 0; i <(int)(n); i++)

typedef complex<double> P;

const double INF = numeric_limits<double>::max();

#define EPS 1.0e-8

inline int SGN(double a) {
    return (a > EPS ? 1 : a < -EPS ? -1 : 0);
}
#define LE(a,b) (SGN((a)-(b)) <= 0)

const double PI = acos(0.0)*2;

double myarg(const P& p) {
    double a = arg(p);
    if (a < 0)
        a += 2*PI;
    return a;
}

struct Solver {
    double width;
    int n;
    vector<double> radius;
    vector<P> positions;

    pair<P, bool> bridge(int iCircle, int jCircle, double r) {

        P p1 = positions[iCircle];
        P p2 = positions[jCircle];
        double r1 = radius[iCircle] + r;
        double r2 = radius[jCircle] + r;

        if (!(p1.real() < p2.real())) {
            swap(p1, p2);
            swap(r1, r2);
        }

        double d = abs(p1-p2);

        if (LE(d, r1 + r2)) {

            double e = (r1*r1 - r2*r2 + d*d) / (2*d);
            double f = sqrt(r1 * r1 - e*e);
            P diff = p2 - p1;
            // buggggggyyyyy
            return make_pair(p1 + diff * P(e, f) / d, true);
        }
        else {
            return make_pair(P(), false);
        }
    }

    pair<P, bool> leftwall(int jCircle, double r) {
        if (LE(positions[jCircle].real(), r+r+radius[jCircle])) {
            P wallPosition = P(r,
                               positions[jCircle].imag() +
                               sqrt( pow(radius[jCircle]+r, 2) - pow(positions[jCircle].real()-r, 2)));
            return make_pair(wallPosition, true);
        }
        else {
            return make_pair(P(), false);
        }
    }

    pair<P, bool> rightwall(int jCircle, double r) {
        if (LE(width-positions[jCircle].real(), r+r+radius[jCircle])) {
            P wallPosition = P(width-r,
                               positions[jCircle].imag() +
                               sqrt( pow(radius[jCircle]+r, 2) - pow(width-positions[jCircle].real()-r, 2)));
            return make_pair(wallPosition, true);
        }
        else {
            return make_pair(P(), false);
        }
    }

    pair<P, bool> floorwall(int jCircle, double r) {
        if (LE(positions[jCircle].imag(), r+r+radius[jCircle])) {
            P wallPosition = P(positions[jCircle].real() +
                               sqrt( pow(radius[jCircle]+r, 2) - pow(positions[jCircle].imag()-r, 2)),
                               r);
            /*
            if (!LE(wallPosition.real()+r, width))
                return make_pair(P(), false);
            */
            return make_pair(wallPosition, true);
        }
        else {
            return make_pair(P(), false);
        }
    }

    void main() {

        for(int iCircle = 0; iCircle < n; iCircle++) {

            //cout << "Placing circle " << iCircle << endl;

            double r = radius[iCircle];

            P minPosition;
            P currentPosition;
            int iWallCircle = -1;

            // かべ(初期点) さがす
            {
                P maxPosition = P(r, r);

                REP(jCircle, iCircle) {
                    pair<P, bool> res = leftwall(jCircle, r);
                    if (res.second) {
                        P wallPosition = res.first;
                        if (wallPosition.imag() > maxPosition.imag()) {
                            maxPosition = wallPosition;
                            iWallCircle = jCircle;
                        }
                    }
                }

                //cout << "iWallCircle: " << iWallCircle << endl;
                //cout << "maxPosition: " << maxPosition << endl;

                minPosition = maxPosition;
                currentPosition = maxPosition;
            }

            int iLastCircle = -1, iCurrentCircle = iWallCircle;
            while(iCurrentCircle >= 0) {

                P nextPosition;
                double nextAngle;
                int iNextCircle = -2;

                REP(jCircle, iCircle) {
                    if (jCircle == iLastCircle || jCircle == iCurrentCircle)
                        continue;
                    pair<P, bool> res = bridge(iCurrentCircle, jCircle, r);
                    if (res.second) {
                        P pos = res.first;
                        double angle = myarg((currentPosition-positions[iCurrentCircle])/(pos-positions[iCurrentCircle]));
                        if (iNextCircle == -2 || //pos.imag() > nextPosition.imag()) {
                            angle < nextAngle) {
                            iNextCircle = jCircle;
                            nextPosition = pos;
                            nextAngle = angle;
                        }
                    }
                }

                {
                    pair<P, bool> res = rightwall(iCurrentCircle, r);
                    if (res.second) {
                        P pos = res.first;
                        double angle = myarg((currentPosition-positions[iCurrentCircle])/(pos-positions[iCurrentCircle]));
                        if (iNextCircle == -2 || //pos.imag() > nextPosition.imag()) {
                            angle < nextAngle) {
                            iNextCircle = -1;
                            nextPosition = pos;
                            nextAngle = angle;
                        }
                        //cout << "right: " << pos << " angle=" << angle << endl;
                        //cout << "current " << currentPosition << ", center " << positions[iCurrentCircle] << ", wall " << pos << endl;
                    }
                }

                {
                    pair<P, bool> res = floorwall(iCurrentCircle, r);
                    if (res.second) {
                        P pos = res.first;
                        double angle = myarg((currentPosition-positions[iCurrentCircle])/(pos-positions[iCurrentCircle]));
                        if (iNextCircle == -2 || //pos.imag() > nextPosition.imag()) {
                            angle < nextAngle) {
                            iNextCircle = -1;
                            nextPosition = pos;
                            nextAngle = angle;
                        }
                        /*
                        cout << "floor: " << pos << " angle=" << angle << endl;
                        cout << "current " << currentPosition << ", center " << positions[iCurrentCircle] << ", wall " << pos << endl;
                        */
                    }
                }

                currentPosition = nextPosition;

                if (iNextCircle != -2 && minPosition.imag() > nextPosition.imag())
                    minPosition = nextPosition;

                //cout << "move from " << iCurrentCircle << " to " << iNextCircle << " " << nextPosition << endl;
                iLastCircle = iCurrentCircle;
                iCurrentCircle = iNextCircle;

            }

            //cout << "placed " << iCircle << " to " << minPosition << endl;

            // かべになったらしゅうりょう

            positions[iCircle] = minPosition;

            //cout << endl;

        }

        double result = 0.0;
        REP(i, n)
            result >?= positions[i].imag() + radius[i];

        printf("%.2f\n", result);

    }

    bool solve() {

        cin >> width;
        if (width == 0)
            return false;

        cin >> n;
        radius.resize(n);
        positions.resize(n);
        REP(i, n) {
            cin >> radius[i];
            radius[i] /= 2;
        }

        main();

        return true;
    }

};




int main() {

    for(;;) {
        Solver x;
        if (!x.solve())
            break;
    }

    return 0;
}
