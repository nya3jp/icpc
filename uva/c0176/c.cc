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

int lis(vector<int>& v) {

    int n = v.size();
    vector<int> u(n, n);

    REP(i, n)
        *lower_bound(ALLOF(u), v[i]) = v[i];

    return lower_bound(ALLOF(u), n) - u.begin();
}

int solve(int n) {
    vector<int> v(n);
    REP(i, n)
        v[i] = i;

    int res = 0;
    do {
        res += lis(v);
    } while(next_permutation(ALLOF(v)));

    return res;
}


int main() {

    for(int n = 1; n < 10; n++) {

        cout << n << ": " << solve(n) << endl;

    }

    return 0;
}

