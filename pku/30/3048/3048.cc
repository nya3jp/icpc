#include <iostream>
#include <fstream>
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

#define REP(i,n) for(int i = 0 ; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

#define N 20000

int maxfactor[N+1];
bool isprime[N+1];

int main() {

    fill(maxfactor, maxfactor+N+1, 1);
    fill(isprime, isprime+N+1, true);
    isprime[0] = isprime[1] = false;

    for(int i = 2; i <= N; i++) {
        if (isprime[i]) {
            maxfactor[i] = i;
            for(int j = i*2; j <= N; j += i) {
                isprime[j] = false;
                maxfactor[j] = i;
            }
        }
    }

    int n;
    cin >> n;
    vector<int> v(n);
    REP(i, n) cin >> v[i];
    vector<int> u(n);
    REP(i, n) u[i] = maxfactor[v[i]];
    int res = v[max_element(ALLOF(u))-u.begin()];

    cout << res << endl;

    return 0;
}

// Powered by Fate Testarossa
