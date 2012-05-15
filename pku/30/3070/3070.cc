#include <iostream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

struct M {
    int a, b, c, d;
};

void mul(M& x, const M& y, const M& z) {
    x.a = (y.a*z.a + y.b*z.c) % 10000;
    x.b = (y.a*z.b + y.b*z.d) % 10000;
    x.c = (y.c*z.a + y.d*z.c) % 10000;
    x.d = (y.c*z.b + y.d*z.d) % 10000;
}
void pow(M& x, const M& a, int n) {
    if (n%2 == 0) {
        x = (M){1, 0, 0, 1};
    }
    else {
        x = a;
    }

    if (n >= 2) {
        M y, z;
        mul(y, a, a);
        pow(z, y, n/2);
        mul(y, x, z);
        x = y;
    }
}
int fib(int n) {
    M f = {1, 1, 1, 0};
    M r;
    pow(r, f, n);
    return r.b;
}

int main() {
    int n;
    while(cin >> n && n >= 0) {
        cout << fib(n) << endl;
    }
    return 0;
}
