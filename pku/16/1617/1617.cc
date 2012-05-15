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

    for(;;) {
        string keyword, cipher;
        getline(cin, keyword);
        getline(cin, cipher);

        if (keyword == "THEEND")
            break;

        int m = keyword.size();
        int n = cipher.size();

        vector<int> order(m);
        REP(i, m) {
            int next = min_element(ALLOF(keyword)) - keyword.begin();
            order[i] = next;
            keyword[next] = 'x';
        }

        assert(keyword == string(m, 'x'));

        string res(n, '.');
        REP(i, m) {
            REP(j, n/m) {
                res[j*m + order[i]] = cipher[i*(n/m)+j];
            }
        }

        cout << res << endl;

    }

    return 0;
}



// Powered by fate testarossa
