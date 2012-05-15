#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

double solve(double ha, double hb, double hc) {
    double x0 = (ha*hb*hc)/(+ha*hb+hb*hc+hc*ha);
    double x1 = (ha*hb*hc)/(-ha*hb+hb*hc+hc*ha);
    double x2 = (ha*hb*hc)/(+ha*hb-hb*hc+hc*ha);
    double x3 = (ha*hb*hc)/(+ha*hb+hb*hc-hc*ha);
    double s = sqrt(x0*x1*x2*x3);
    double a = 2*s/ha, b = 2*s/hb, c = 2*s/hc;
    if (a > 0 && b > 0 && c > 0 && a+b > c && b+c > a && c+a > b)
        return s;
    return -1;
}


int main() {
    int n;
    cin >> n;
    while(n > 0) {
        double ha, hb, hc;
        cin >> ha >> hb >> hc;
        if (!cin)
            break;
        double s = solve(ha, hb, hc);
        if (s < 0) {
            cout << "These are invalid inputs!" << endl;
            n--;
        }
        else {
            printf("%.3f\n", s);
        }
    }
    return 0;
}
