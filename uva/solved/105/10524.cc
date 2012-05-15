#include <cstdio>
#include <cmath>

using namespace std;

#define N 1000

const double EP = 1.0e-8;
double m[N][N*2];

int main() {
    int n;
    scanf("%d", &n);
    if (n == 0)
        return 0;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%lf", &m[i][j]);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            m[i][j+n] = (i == j ? 1 : 0);

    bool failed = false;

    for(int j = 0; j < n; j++) {
        double p = m[j][j];
        if (abs(p) < EP)
            failed = true;
        for(int i = 0; i < n; i++) {
            if (i == j)
                continue;
            for(int k = j; k < 2*n; k++)
                m[i][k] -= m[j][k] * p;
        }
        for(int k = j; k < 2*n; k++)
            m[j][k] /= p;
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (abs(m[i][j+n]) < EP)
                m[i][j+n] = 0;

    if (failed) {
        printf("Not possible\n");
    }
    else {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                printf("%.6f%s", m[i][j+n], (j == n-1 ? "\n" : " "));
    }
    printf("\n");

    return main();
}
