#include <cstdio>
#include <cmath>

using namespace std;

double choose(int a, int b) {
    double p = 1.0;
    for(int i = 0; i < b; i++)
        p *= a-i;
    for(int i = 1; i <= b; i++)
        p /= i;
    return p;
}

double fact(int n) {
    double p = 1;
    for(int i = 1; i <= n; i++)
        p *= i;
    return p;
}

double solve(int a, int b) {
    int N = 13;
    int n = a+b;
    double p = choose(n, a) * choose(2*N-n, N-a) * fact(N) * fact(N) / fact(2*N);
    // 1/2N! * nCa * (2N-n)C(N-a) * N! * N!
    return (a != b ? 2*p : p);
}

int main() {
    while(true) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a < 0)
            break;
        printf("%d-%d split: %.08f\n", a, b, solve(a, b));
    }
}
