#include <iostream>
#include <cmath>

using namespace std;

const int PI = acos(0.0) * 2;

int main() {
    double a, b, th;
    while(cin >> a >> b >> th && !(a == 0 && b == 0 && th == 0)) {
        cout << (a*a + b*b - 2*a*b*cos(th*PI/180)) << endl;
    }
    return 0;
}
