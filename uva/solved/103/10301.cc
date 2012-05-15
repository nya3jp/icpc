/*
 * Union-FindƒAƒ‹ƒSƒŠƒYƒ€
 * rev.01
 *
 * [NOT VERIFIED]
 */

#include <vector>
#include <algorithm>


struct UnionFind {
    std::vector<int> data;
    const int n;

    UnionFind(int n) : data(n, -1), n(n) {
    }
    bool link(int a, int b) {
        int ra = find_root(a);
        int rb = find_root(b);
        if (ra != rb) {
            if (data[rb] < data[ra])
                std::swap(ra, rb);
            data[ra] += data[rb];
            data[rb] = ra;
        }
        return (ra != rb);
    }
    bool check(int a, int b) {
        return (find_root(a) == find_root(b));
    }

    int find_root(int a) {
        return ((data[a] < 0) ? a : (data[a] = find_root(data[a])));
    }
};


#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>

using namespace std;

struct C {
    complex<double> p;
    double r;
};


int main() {
    int n;
    while(cin >> n && n >= 0) {
        vector<C> v(n);
        for(int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y >> v[i].r;
            v[i].p = complex<double>(x, y);
        }
        UnionFind uf(n);
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                C& a = v[i];
                C& b = v[j];
                double E=1.0e-8;
                double d = abs(a.p-b.p);
                double ra = min(a.r, b.r);
                double rb = max(a.r, b.r);
                if (d+ra < rb-E) {
                    // contain
                }
                else if (d <= ra+rb+E) {
                    // touch
                    uf.link(i, j);
                }
                else {
                    // outside
                }
            }
        }
        int m = 0;
        for(int i = 0; i < n; i++) {
            m = max(m, -uf.data[uf.find_root(i)]);
        }
        cout << "The largest component contains " << m << " ring" << (m <= 1 ? "" : "s") << "." << endl;
    }
    return 0;
}
