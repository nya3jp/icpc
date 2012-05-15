#include <iostream>
#include <vector>
#include <complex>
#include <map>
#include <set>
#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "balls"


int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    int n, m, k;

    vector<int> v(m);
    REP(i, n) {
        int x;
        scanf("%d", &x);
        x--;
        v[x]++;
    }

    sort(ALLOF(v));

    cout << go(v, k) << endl;

    return 0;
}

