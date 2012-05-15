#include <iostream>
#include <cmath>
using namespace std;

typedef long long int integer;

integer myabs(integer x) {
    return (x < 0 ? -x : x);
}

integer gcd(integer a, integer b) {
    return (b == 0 ? a : gcd(b, a%b));
}

#define IN(a,l,h) (l <= a && a < h)

integer N, D;
integer diffN, diffD;
integer bestN, bestD;

void test(integer n, integer d) {
    if (!IN(n, 1, 32768) || !IN(d, 1, 32768))
        return;
    integer dN = myabs(N*d - D*n);
    integer dD = D*d;
    if (dN*diffD - dD*diffN < 0 && dN != 0) {
        integer g = gcd(myabs(n), myabs(d));
        bestN = n / g;
        bestD = d / g;
        diffN = dN;
        diffD = dD;
    }
}

int main() {

    cin >> N >> D;

    diffN = 65536;
    diffD = 1;

    for(integer d = 1; d < 32768; d++) {

        // N/D - n/d = (Nd - Dn)/Dd

        integer n = N*d/D;

        test(n, d);
        test(n+1, d);
        test(n-1, d);

    }

    cout << bestN << ' ' << bestD << endl;

    return 0;
}
