#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

#define EP 1.0e-5
#define N 20

struct Mat {
    double a, b, c, d;
    Mat() {
    }
    Mat(double a, double b, double c, double d)
        : a(a), b(b), c(c), d(d) {
    }
    inline Mat& operator+=(const Mat& rhs) {
        a += rhs.a;
        b += rhs.b;
        c += rhs.c;
        d += rhs.d;
        return *this;
    }
    inline Mat& operator*=(const Mat& rhs) {
        double aa = a*rhs.a+b*rhs.c;
        double bb = a*rhs.b+b*rhs.d;
        double cc = c*rhs.a+d*rhs.c;
        double dd = c*rhs.b+d*rhs.d;
        a = aa; b = bb; c = cc; d = dd;
        return *this;
    }
    void pow(int n) {
        Mat v[N];
        v[0] = *this;
        for(int i = 1; i < N; i++) {
            v[i] = v[i-1];
            v[i] *= v[i];
        }
        *this = Mat(1, 0, 0, 1);
        for(int i = 0; i < N; i++) {
            if ((n&(1<<i)) != 0)
                *this *= v[i];
        }
    }

};

Mat powv[N];
void prepare_pow(const Mat& m) {
    powv[0] = m;
    for(int i = 1; i < N; i++) {
        powv[i] = powv[i-1];
        powv[i] *= powv[i];
    }
}
void fast_pow(int n, Mat& rhs) {
    rhs.a = rhs.d = 1;
    rhs.b = rhs.c = 0;
    for(int i = 0; i < N; i++) {
        if ((n&(1<<i)) != 0)
            rhs *= powv[i];
    }
}

int solve(double b, double w, double c) {

    double a11 = (b-c)/b + c*c/(b*(c+w));
    double a12 = c*w/(b*(c+w));
    double a21 = c/(c+w);
    double a22 = w/(c+w);

    Mat m(a11, a12, a21, a22);
    prepare_pow(m);

/*
    for(int i = 0; i < 10; i++) {
        Mat x(m);
        x.pow(i);
        printf("{%.4f %.4f\n %.4f %.4f}\n", x.a, x.b, x.c, x.d);
    }
    return 0;
*/

    double r = b / w;

    int from = 0, to = (1<<N)-1;

    Mat x;
    while(from < to) {
        int mid = (from+to)/2;
        fast_pow(mid, x);
        //printf("%d: %.4f %.4f (%.4f)\n", mid, x.a, x.b, r);
        if (abs((x.a/x.b)-r) < EP && abs((x.c/x.d)-r) < EP) {
            to = mid;
        }
        else {
            from = mid+1;
        }
    }
    assert(from == to);

    return from;
}

int main() {

    while(true) {
        int B, W, C;
        scanf("%d%d%d", &B, &W, &C);
        if (B == 0 && W == 0 && C == 0)
            break;

        double b, w, c;
        b = B; w = W; c = C / 16.0;

        printf("%d\n", solve(b, w, c));

    }

    return 0;
}

