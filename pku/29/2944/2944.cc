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

struct P {
    int x, y, z;
};
bool by_z(const P& a, const P& b) {
    return (a.z < b.z);
}

P v[100000];
int n, m;

typedef long long int integer;

integer solve() {

    sort(v, v+n, by_z);
    reverse(v, v+n);

    typedef map<int,int> Z;
    Z z;
    z[0] = INT_MAX;
    z[INT_MAX] = 0;

    integer res = 0;

    int zp = INT_MAX;
    integer area = 0;
    REP(i, n) {
        P p = v[i];

        res += (zp-p.z)*area;
        zp = p.z;

        for(;;) {
            Z::iterator next = z.upper_bound(p.x);
            Z::iterator prev = next;
            --prev;
            if (prev->second > p.y) {
                if (prev->first < p.x && p.y > next->second) {
                    area += (integer)(p.x-prev->first)*(p.y-next->second);
                    z[p.x] = p.y;
                }
                break;
            }
            Z::iterator preprev = prev;
            --preprev;
            area -= (integer)(prev->first-preprev->first)*(prev->second-next->second);
            z.erase(prev);
        }

        /*
        FOR(it, z) {
            cout << "(" << it->first << ", " << it->second << ") ";
        }
        cout << endl;
        */

    }
    res += area * zp;

    return res;
}

int main() {

    for(;;) {
        scanf("%d%d", &n, &m);
        if (n == 0)
            break;

        REP(i, n) {
            P& p = v[i];
            scanf("%d%d%d", &p.x, &p.y, &p.z);
        }

        integer res = solve();
        cout << ((integer)m*m*m - res) << endl;

    }

    return 0;
}
