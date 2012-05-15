#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define EP 1.0e-5
#define N 20

typedef double Mat[4];


inline void multiply(const Mat& x, const Mat& y, Mat& z) {
    z[0] = x[0]*y[0] + x[1]*y[2];
    z[1] = x[0]*y[1] + x[1]*y[3];
    z[2] = x[2]*y[0] + x[3]*y[2];
    z[3] = x[2]*y[1] + x[3]*y[3];
}


int solve(double b, double w, double c) {
    const Mat m =
        {
        (b-c)/b + c*c/(b*(c+w)),
        c*w/(b*(c+w)),
        c/(c+w),
        w/(c+w)
        };

    Mat v[N-1];
    copy(m, m+4, v[0]);
    for(int i = 1; i < N-1; i++) {
        multiply(v[i-1], v[i-1], v[i]);
    }

    const double r = b / w;

    int from = 0, to = (1<<N)-1;

    Mat x, t;
    int cnt = 0;
    while(from < to) {
        int mid = (from+to)/2;
        if (cnt == 0) {
            mid = 100;
        }
        else if (cnt == 1) {
            if (from > 0)
                mid = 10000;
        }
        x[0] = x[3] = 1;
        x[1] = x[2] = 0;
        for(int i = 0; i < N; i++) {
            if ((mid&(1<<i)) != 0) {
                multiply(x, v[i], t);
                x[0] = t[0];
                x[1] = t[1];
                x[2] = t[2];
                x[3] = t[3];
                //copy(t, t+4, x);
            }
        }
        if (abs((x[0]/x[1])-r) < EP && abs((x[2]/x[3])-r) < EP) {
            to = mid;
        }
        else {
            from = mid+1;
        }
        if (++cnt >= 2*N)
            throw 0;
    }
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




