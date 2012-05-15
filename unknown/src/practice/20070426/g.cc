#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

#define EARTH 6378.

const double PI = acos(0.0)*2;

struct P {
    double x, y, z;
};

double operator*(const P& a, const P& b) {
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

P operator-(const P& a, const P& b) {
    return (P){a.x - b.x, a.y - b.y, a.z - b.z};
}

int main() {

    int iCase = 0;
    for(;;) {
        int n;
        double lat, lng, sky;
        cin >> n >> lat >> lng >> sky;

        lat *= PI / 180;
        lng *= PI / 180;

        if (n == 0)
            break;

        P target = {(EARTH+sky)*sin(lat), (EARTH+sky)*cos(lat)*cos(lng), (EARTH+sky)*cos(lat)*sin(lng)};
        cout << "Test case " << ++iCase << ":" << endl;

        REP(i, n) {
            string name;
            double clat, clng;
            cin >> name >> clat >> clng;

            clat *= PI / 180;
            clng *= PI / 180;

            P city = {EARTH*sin(clat), EARTH*cos(clat)*cos(clng), EARTH*cos(clat)*sin(clng)};
            P delta = target - city;

            if (city*delta > -1.0e-8) {
                cout << name << endl;
            }
            
        }

        cout << endl;

    }

    return 0;
}

