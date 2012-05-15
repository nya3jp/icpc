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
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

char f[(1<<18)+64];

bool bits[1<<18];
int n;

int solve(int p, int k) {
    if (k > n-p)
        return 0;
    if (p == n)
        return bits[0];
    int s = 1<<(n-1-p);
    int res = 0;
    if (k > 0) {
        REP(i, s)
            bits[i] ^= bits[i|s];
        res += solve(p+1, k-1);
        REP(i, s)
            bits[i] ^= bits[i|s];
    }
    res += solve(p+1, k);
    return res;
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        int k;
        scanf("%d%d ", &n, &k);
        gets(f);

        REP(i, 1<<n)
            bits[i] = (f[i] == '1');

        int res = solve(0, k);
        printf("%d\n", res);

    }

    return 0;
}
