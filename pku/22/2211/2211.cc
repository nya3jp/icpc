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

int perm(int n, int k) {
    int res = 1;
    for(int t = n; t > n-k; t--)
        res *= t;
    return res;
}

int solve(int n, vector<int> res) {
    if (res.empty())
        return 0;

    int k = res.size();
    int front = res.front();
    int p = front * perm(n-1, k-1);

    vector<int> next(res.begin()+1, res.end());
    REP(i, next.size())
        if (next[i] > front)
            next[i]--;

    return (p + solve(n-1, next));
}

int main() {

    // May fate be with you!

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n, k;
        cin >> n >> k;

        vector<int> res(k);
        REP(i, k) {
            cin >> res[i];
            res[i]--;
        }

        cout << "Variace cislo " << iCase+1 << " ma poradove cislo " << solve(n, res)+1 << "."  << endl;

    }

    return 0;
}



// Powered by fate testarossa
