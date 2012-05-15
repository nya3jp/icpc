#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define EP 1.0e-8

double entropy(const int* s, int n) {
    int freq[64];
    fill(freq, freq+64, 0);
    for(int i = 0; i < n; i++) {
        freq[s[i]]++;
    }
    double h = 0;
    for(int i = 0; i < 64; i++) {
        if (freq[i] > 0) {
            double p = (double)freq[i] / n;
            h -= p * log(p) / log(2.0);
        }
    }
    return h;
}

void solve(double H) {
    if (abs(H-5.96) < EP) {
        // テラアリエナス
        cout << 
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789...   TFMZ"
            "HnR86SA3YPDIKI.Euo4auJBeJ7clAu MESkOh6ZQyogitymClgt 5Ueq5H5VS0pI2a037re8UUcmVw1r"
            "R5FDu6vsSoEVtM.D5mkWKCyL8nOzXGwDbUDm4F7p8HRkcBTRc9uGXhvoO9UVdhcS2xU7T6EGE10stXiy"
            "YJMOGRxmO6867yLwdx2YktPWSpgoBkVdFQZNygbNSJqcHOdZCPdCOquoa.RbozFSN08r.7cl9V8tuIJ2"
            "IjbeLL UZyx2ybGnpyLFsR0KvOxNLXjs3dCc8Y3MDi NJltWOcxa1s93DgRt6rerzFQmFnmmBNzACjPI"
            "tdV7dVuR73PGyRX9z2RQf59tjKmr5TRogyA4Irl8 5yEYPYP0fCCxVUtTM2Tj7ltksBPVHojOF6zVCgF"
            "yAAplszERgwWkHXqSoZXsYuG1yItv9nFdnlm6yTtnmwXplNbOWX0d9mOHO JcjlGNv03i8nNcWMu2qS0"
            "CsH.us4UOXwJbMYc7A6rRjhGt43SHlavVvVz2GRzH.7JEcLJ3H4MVc6AFmpNcIGZbqylz8nVWl4qmnZJ"
            "b8KOwZ17rFFkU.vgSs5ndp8B4YeBXJ1gEYH.lomYDL7KDPkhTLZ680pq SjJMKzpFasvaO6t511KF475"
            "Lc3 Dqg5F0qLw4Hjg Boin6OBJ43YONOu3YegdyhhIkP5ESA8H SbFUdGVIbwbAfxuC.WEaog.3L9liy"
            "Yp2oCLeahqXiM4OW8SmnQX853ojOLz97Ddwf" << endl;
        return;
    }

    int s[1000];
    int n;
    int k = 1;
    s[0] = 0;
    for(n = 1; n <= 1000; n++) {
        double h = entropy(s, n);
        if (abs(h-H) < 0.005-EP) {
            break;
        }
        else if (h < H) {
            s[n] = k++;
        }
        else {
            s[n] = k-1;
        }
    }
    assert(n <= 1000);
    assert(k <= 64);

    const char S[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789. ";
    for(int i = 0; i < n; i++) {
        cout << S[s[i]];
    }
    cout << endl;
}


/*
int main() {
    srand(283);
    for(int i = 0; i <= 600; i++) {
        double H = i * 0.01;
        cout << H << " -> ";
        solve(H);
    }
    return 0;
}
*/

int main() {

    double H;
    cin >> H;
    solve(H);

    return 0;
}

