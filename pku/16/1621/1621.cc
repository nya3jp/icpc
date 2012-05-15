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

int digits(int x) {
    return (int)ceil(log10((double)x)+1.0e-8);
}

int main() {

    // May fate be with you!

    int iCase = 0;

    for(;;) {

        int n;
        cin >> n;

        if (n == 0)
            break;

        vector<int> coefs(n+1);
        REP(i, n+1)
            cin >> coefs[i];

        int x;
        cin >> x;

        int res = 0;
        {
            res = -1;
            //cout << "xinv";
            for(int i = 1; i <= n; i++) {
                int c = coefs[i];
                res += 2;
                //cout << "*x";
                if (c > 0) {
                    res += 1 + digits(c); // '+' c
                    //cout << "+" << c;
                }
            }
            res++;
            //cout << "=" << endl;
        }

        int y = 0;
        REP(i, n+1)
            y += coefs[i] * ((x == 1 || (n-i)%2 == 0) ? 1 : -1);

        printf("Polynomial %d: %d %d\n", ++iCase, y, res);

    }

    return 0;
}



// Powered by fate testarossa
