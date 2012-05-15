#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double PI = acos(0.0)*2;

struct V {
    double a, b;
};
struct P {
    double x, y, z;
};

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        vector<V> r(n);
        vector<P> v(n);
        for(int i = 0; i < n; i++) {
            P& p = v[i];
            double a, b;
            scanf("%lf%lf", &a, &b);
            r[i].a = a;
            r[i].b = b;
            a = a*PI/180;
            b = b*PI/180;
            p.x = cos(a)*cos(b);
            p.y = cos(a)*sin(b);
            p.z = sin(a);
        }
        double* dist = new double[n*n];
        for(int i = 0; i < n; i++) {
            const P& p = v[i];
            dist[i*n+i] = 0;
            for(int j = i+1; j < n; j++) {
                const P& q = v[j];
                double ip = p.x*q.x + p.y*q.y + p.z*q.z;
                double d = acos(ip);
                dist[i*n+j] = dist[j*n+i] = d;
            }
        }
        vector<double> maxdist(n);
        for(int i = 0; i < n; i++) {
            maxdist[i] = *max_element(dist+i*n, dist+(i+1)*n);
        }
        delete[] dist;
        int answer = 0;
        for(int i = 1; i < n; i++) {
            if (maxdist[i] <= maxdist[answer] + 1.0e-8) {
                answer = i;
            }
        }
        printf("%.02f %.02f\n", r[answer].a, r[answer].b);
    }
    return 0;
}
