#include <iostream>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

long long int gcd(long long int n, long long int m) {
    if (m == 0)
        return n;
    return gcd(m, n%m);
}


int solve(long long int p, long long int q, int a, int n, int d0) {
    long long int g = gcd(p, q);
    p /= g; q /= g;

    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    if (q > a)
        return 0;
    if (n == 0)
        return 0;

    int res = 0;
    for(int d = d0; d <= a; d++) {
        // p/q - 1/d = (pd - q)/(dq)
        long long int num = p*d - q;
        long long int denom = d * q;
        res += solve(num, denom, a/d, n-1, d);
    }

    return res;
}


int main() {

    for(;;) {
        int p, q, a, n;
        cin >> p >> q >> a >> n;
        if (p == 0 && q == 0 && a == 0 && n == 0)
            break;

        int res = solve(p, q, a, n, 1);

        cout << res << endl;

    }


    return 0;
}

