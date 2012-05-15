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
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

int gcd(int a, int b) {
    return (b == 0 ? a : gcd(b, a%b));
}

int main() {

    for(;;) {
        int n, x, d;
        if (scanf("%d%d%d", &n, &x, &d) != 3)
            break;
        int g;
        scanf("%d", &g);
        REP(i, n-1) {
            int t;
            scanf("%d", &t);
            g = gcd(g, t);
        }
        for(;;) {
            int k = gcd(g, d);
            if (k == 1)
                break;
            g /= k;
        }
        puts(x % g == 0 ? "Yes" : "No");
    }

    return 0;
}
