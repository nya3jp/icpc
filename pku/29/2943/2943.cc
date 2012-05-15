#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <bitset>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define N 200
#define M 300

bitset<M> materials[N];

bool by_popcount(const bitset<M>& a, const bitset<M>& b) {
    return (a.count() < b.count());
}


int main() {

    for(;;) {
        int m, n;
        scanf("%d%d", &m, &n);
        if (m == 0)
            break;

        REP(i, n) {
            bitset<M>& b = materials[i];
            b.reset();
            int k;
            scanf("%d", &k);
            REP(j, k) {
                int x;
                scanf("%d", &x);
                x--;
                b.set(x, true);
            }
        }

        sort(materials, materials+n, by_popcount);

        int res = 0;
        REP(i, n) {
            bitset<M> support;
            REP(j, i) {
                bitset<M> b = materials[i];
                b.flip();
                b &= materials[j];
                if (b.none()) {
                    support |= materials[j];
                }
            }
            if (support == materials[i]) {
                res++;
            }
        }

        printf("%d\n", res);

    }

    return 0;
}

