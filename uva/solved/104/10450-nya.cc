/*
 * UVA 10450 World Cup Noise
 * 2005-08-20
 * by nya
 */

#include <cstdio>

#define N 50

int main() {

    unsigned long long int a0[N+1];
    unsigned long long int a1[N+1];

    a0[0] = 1;
    a1[0] = 0;

    for(int i=1; i<=N; i++) {
        a0[i] = a0[i-1] + a1[i-1];
        a1[i] = a0[i-1];
    }

    int n;
    std::scanf("%d", &n);
    for(int c=0; c<n; c++) {
        int m;
        std::scanf("%d", &m);
        std::printf("Scenario #%d:\n%llu\n\n", c+1, a0[m]+a1[m]);
    }

    return 0;
}
