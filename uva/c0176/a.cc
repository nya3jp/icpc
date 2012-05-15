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


#define N 10

int n, m;

typedef long long int integer;

integer memo[N*N][N][1<<N];

integer cache[N*N][N];

integer search(int i, int j, int last) {

    if (j == m)
        return search(i+1, 0, last);
    if (i == n)
        return (last == 0 ? 1 : 0);

    integer& res = memo[i][j][last];
    if (res >= 0)
        return res;

    res = 0;
    if ((last&1) == 1) {
        res += search(i, j+1, last>>1);
    }
    if ((last&1) == 0) {
        res += search(i, j+1, (last>>1)|(1<<(m-1)));
    }
    if ((last&3) == 0 && j < m-1) {
        res += search(i, j+2, last>>2);
    }

    return res;
}

integer solve() {
    //memset(memo, -1, sizeof(memo));
    //return search(0, 0, 0);
    return cache[n][m];
}

void precalc() {

    for(m = 1; m <= N; m++) {
        n = N*N/m;
        memset(memo, -1, sizeof(memo));
        for(int nn = 1; nn <= n; nn++)
            cache[nn][m] = search(n-nn, 0, 0);
    }

}



int main() {

    precalc();

    for(;;) {

        cin >> n >> m;
        if (!cin)
            break;

        if (m > n)
            swap(n, m);

        cout << solve() << endl;

    }

    return 0;
}

