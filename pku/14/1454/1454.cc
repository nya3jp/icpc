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

#define N 366
#define DIGITS 800

int num[DIGITS];
int memo[N+1][10];

int main() {

    num[0] = 1;

    for(int f = 1; f <= N; f++) {
        int carry = 0;
        int last = -1;
        REP(i, DIGITS) {
            int t = num[i] * f + carry;
            int s = t % 10;
            carry = t / 10;
            num[i] = s;
            memo[f][s]++;
            if (s > 0)
                last = i;
        }
        memo[f][0] -= DIGITS-last-1;
    }

    for(int q; cin >> q && q > 0; ) {
        printf("%d! --\n", q);
        REP(j, 5) {
            int i = j;
            printf("   (%d)%5d", i, memo[q][i]);
            printf(j < 4 ? " " : "\n");
        }
        REP(j, 5) {
            int i = j + 5;
            printf("   (%d)%5d", i, memo[q][i]);
            printf(j < 4 ? " " : "\n");
        }
    }

    return 0;
}

