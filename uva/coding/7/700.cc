/*
 * ユークリッドの互除法など
 */

#include <iostream>
#include <algorithm>

#include <utility>
#include <cassert>

using namespace std;


typedef long long int integer;

// 拡張ユークリッド互除法
// a*x + b*y = gcd(a, b)
// となるx, yを求める
void xgcd(integer a, integer b, integer& x, integer& y) {
    if (b == 0) {
        x = 1;
        y = 0;
    }
    else {
        xgcd(b, a%b, y, x);
        y -= a/b*x;
    }
}

// 最大公約数
integer gcd(integer a, integer b) {
    while(b != 0) {
        integer r = a%b;
        a = b;
        b = r;
    }
    return a;
}

integer lcm(integer a, integer b) {
    integer g = gcd(a, b);
    return a/g*b;
}



struct no_solution {};

// a*n = b (mod m) となる、非負でかつ最小のnを求める
// 解がない場合はno_solutionをthrowする
integer divide(integer a, integer b, integer m) {
    integer g = gcd(a, m);
    if (b%g != 0)
        throw no_solution();
    integer x, y;
    xgcd(a, m, x, y);
    assert(a*x+m*y == gcd(a,m));
    integer n = x*b/g;
    integer dn = m/g;
    n -= n/dn*dn;
    if (n < 0)
        n += dn;
    return n;
}


int main() {
    int iCase = 0;
    int n;
    while(cin >> n && n > 0) {
        integer start0, cycle0;
        {
            integer a, b, y;
            cin >> y >> a >> b;
            start0 = y;
            cycle0 = b - a;
        }

        bool impossible = false;
        for(int i = 1; i < n; i++) {
            integer a, b, y;
            cin >> y >> a >> b;
            integer start1 = y;
            integer cycle1 = b - a;

            if (start1-start0 < 0) {
                swap(start0, start1);
                swap(cycle0, cycle1);
            }
            if (!impossible) {
                try {
                    integer n = divide(cycle0, start1-start0, cycle1);
                    integer th = (start1-start0+cycle0-1)/cycle0;
                    if (n < th) {
                        integer dn = cycle1 / gcd(cycle0, cycle1);
                        n += dn * ( (th-n + dn-1) / dn );
                    }
                    start0 += cycle0 * n;
                    cycle0 = lcm(cycle0, cycle1);
                    if (start0 >= 10000)
                        impossible = true;
                }
                catch(no_solution) {
                    impossible = true;
                }
            }
        }

        cout << "Case #" << ++iCase << ":" << endl;
        if (impossible) {
            cout << "Unknown bugs detected." << endl;
        }
        else {
            cout << "The actual year is " << start0 << "." << endl;
        }
        cout << endl;

    }
    return 0;
}
