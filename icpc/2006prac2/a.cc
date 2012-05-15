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
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

int main() {
    ifstream cin("A.txt");

    long long int x, y;
    while(cin >> x >> y && !(x == 0 && y == 0)) {

        long long int res = 0x7fffffff;
        for(long long int a1 = 1; a1*a1 <= x; a1++) {
            if (x%a1 == 0) {
                long long int a2 = x/a1;
                for(long long int b1 = 1; b1*b1 <= y; b1++) {
                    if (y%b1 == 0) {
                        long long int b2 = y/b1;
                        long long int ar[4] = {a1, a2, b1, b2};
                        sort(ar, ar+4);
                        long long int s =
                            (ar[1]-ar[0])*(ar[1]-ar[0])+
                            (ar[2]-ar[1])*(ar[2]-ar[1])+
                            (ar[3]-ar[2])*(ar[3]-ar[2]);
                        res <?= s;
                    }
                }
            }
        }

        cout << res << endl;

    }

    return 0;
}


// Powered by Fate Testarossa
