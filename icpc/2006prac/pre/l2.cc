#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const double PI = acos(0.0) * 2;

int main() {
    double a, b, th;
    while(cin >> a >> b >> th && !(a == 0 && b == 0 && th == 0)) {
        printf("%.3f\n", sqrt(a*a + b*b - 2*a*b*cos(th*PI/180)));
    }
    return 0;
}
