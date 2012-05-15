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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

#define MAX_PRIME 40000
bool isprime[MAX_PRIME+1];
vector<int> primes;

void init_primes() {
    REP(i, MAX_PRIME+1)
        isprime[i] = true;
    isprime[0] = isprime[1] = false;
    for(int i = 2; i <= MAX_PRIME; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            for(int j = 2*i; j <= MAX_PRIME; j+=i)
                isprime[j] = false;
        }
    }
}

vector<int> decompose(int n) {
    vector<int> factors(primes.size(), 0);
    REP(i, primes.size()) {
        int p = primes[i];
        while(n%p == 0) {
            n /= p;
            factors[i]++;
        }
    }
    factors.push_back((n > 1 ? 1 : 0));
    return factors;
}

int solve(int n) {
    vector<int> factors = decompose(n);
    int res = 1;
    REP(i, factors.size())
        res *= factors[i]*2+1;
    return (res+1)/2;
}

int main() {
    init_primes();

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        int n;
        cin >> n;
        cout << "Scenario #" << iCase+1 << ":" << endl;
        cout << solve(n) << endl;
        if (iCase < nCases-1)
            cout << endl;
    }

    return 0;
}
