#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "art"

int main() {

    /*
    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();
    */

    // let x = p1^e1 p2^e2 p3^e3 ...
    // phi(x) = (1+e1)(1+e2)(1+e3)...

    int n, m;
    cin >> n >> m;
    if (n < m)
        swap(n, m);

    int a[n+1], phi[n+1];
    REP(i, n+1)
        a[i] = i, phi[i] = 1;

    for(int i = 2; i <= n; i++) {
        if (a[i] > 1) {
            for(int j = i*2; j <= n; j+=i) {
                int lo = 0;
                do {
                    lo++;
                    a[j] /= i;
                } while(a[j] % i == 0);
                phi[j] *= lo+1;
            }
        }
    }

    return 0;
}
