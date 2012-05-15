#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;


double solve(double x) {
    int xn = (int)x;
    int a = 0;
    while((a+1)*(a+1)*(a+1) <= xn)
        a++;
    double d = (x - a*a*a)/a/a/3;
    return a+d;
}

int main() {
    double x;
    while(cin >> x && x != 0) {
        printf("%.4f\n", solve(x));
    }
    return 0;
}
