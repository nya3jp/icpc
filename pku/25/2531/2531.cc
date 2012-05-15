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

int main() {

    // May fate be with you!

    int n;
    int adj[20][20];

    cin >> n;
    REP(i, n) REP(j, n)
        cin >> adj[i][j];

    int res = 0;
    REP(s, 1<<(n-1)) {
        int local = 0;
        REP(i, n-1) REP(j, n) {
            if (AT(s, i) && !AT(s, j))
                local += adj[i][j];
        }
        res >?= local;
    }
    cout << res << endl;

    return 0;
}



// Powered by fate testarossa
