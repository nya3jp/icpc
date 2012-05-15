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

#define N 5000

int n;
int v[N];
int res[N+1];
int q[N+10];

const int INF = 10000;

int solve(int k) {
    int qfirst = 0, qlast = 0;
    REP(i, n) {
        int x = v[i];
        while(qfirst < qlast && q[qfirst] == i)
            qfirst++;
        if ((qlast-qfirst+x)%2 == 1)
            q[qlast++] = i + k;
    }
    while(qfirst < qlast && q[qfirst] == n)
        qfirst++;
    if (qfirst < qlast)
        return INF;
    return qlast;
}

int main() {

    scanf("%d", &n);

    REP(i, n) {
        char c;
        scanf(" %c", &c);
        v[i] = (c == 'F' ? 0 : 1);
    }

    for(int k = 1; k <= n; k++)
        res[k] = solve(k);

    int k = min_element(res+1, res+n+1) - res;

    cout << k << " " << res[k] << endl;

    return 0;
}
