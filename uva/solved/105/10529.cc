#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define N 1000

double mem[N];
double p, q;

double f(int n) {

    if (n == 0)
        return 0;

    double& m = mem[n-1];

    if (m >= 0)
        return m;

    double y = 1.0e100;

    for(int k = 0; k < n; k++) {

        double left = f(k);
        double right = f(n-k-1);

        double x = (1+(1-q)*left+(1-p)*right)/(1-p-q);

        y = min(y, x);
    }

    return (m = y);
}


int main() {

    int n;
    cin >> n >> p >> q;

    if (p < q)
        swap(p, q);

    if (n == 0)
        return 0;

    fill(mem, mem+n, -1);

    printf("%.2f\n", f(n));

    return main();
}

