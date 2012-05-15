#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const double PI = 2*acos(0.0);
const double R = 6378;
const double EP = 1.0e-10;

int main() {

    int nCases;
    cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {

        double n, m;
        cin >> n >> m;

        bool impossible = false;

        if (n >= 1001)
            impossible = true;

        double dth = n/R;
        double tanth = (m*cos(dth) - n) / (m*sin(dth));

        double th = atan(tanth);
        if (-EP < th && th < EP)
            th = 0;

        printf("Case %d: ", iCase+1);

        double deg = th * 180 / PI;
        double min = (deg-floor(deg))*60;
        double sec = (min-floor(min))*60;

        if (!(0 <= deg && deg <= 70+EP))
            impossible = true;

        if (impossible)
            printf("Invalid or impossible.\n");
        else
            printf("%d deg %d min %d sec\n", (int)deg, (int)min, (int)(sec+0.5));

    }

    return 0;
}



