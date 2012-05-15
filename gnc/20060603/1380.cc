#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

#define EP 1.0e-8

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        double w1, h1, w2, h2;
        scanf("%lf%lf%lf%lf", &w1, &h1, &w2, &h2);
        //cin >> w1 >> h1 >> w2 >> h2;
        if (w1 > h1)
            swap(w1, h1);
        if (w2 > h2)
            swap(w2, h2);
        if (w2 < w1 && h2 < h1) {
            cout << "Escape is possible." << endl;
        }
        else {
            double W = w1;
            double H = h1;
            double w = w2;
            double h = h2;
            double a = w*w/h/h+1;
            double b = W*w/h;
            double c = W*W-h*h;
            double d = b*b-a*c;
            //cout << d << endl;
            if (d >= 0) {
                double y = (b + sqrt(d)) / a;
                double x = sqrt(h*h-y*y);
                //cout << y << endl;
                if (y+(W-x)*x/y < H-EP) {
                    cout << "Escape is possible." << endl;
                }
                else {
                    cout << "Box cannot be dropped." << endl;
                }
            }
            else {
                cout << "Box cannot be dropped." << endl;
            }
        }
    }
    return 0;
}
