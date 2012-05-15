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

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define N 20000

typedef unsigned long long int integer;
integer dnas[N];
int histgram[N+1];

integer parse_dna(const char* p) {
    integer res = 0;
    while(*p) {
        switch(*p) {
        case 'A':
            res = (res << 2) | 0;
            break;
        case 'T':
            res = (res << 2) | 1;
            break;
        case 'G':
            res = (res << 2) | 2;
            break;
        case 'C':
            res = (res << 2) | 3;
            break;
        default:
            assert(false);
        }
        p++;
    }
    return res;
}

int main() {

    for(;;) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n == 0)
            break;

        REP(i, n) {
            char dna[100];
            scanf("%s", dna);
            dnas[i] = parse_dna(dna);
        }

        sort(dnas, dnas+n);
        memset(histgram, 0, sizeof(histgram));

        int k = 1;
        for(int i = 1; i < n; i++) {
            if (dnas[i] != dnas[i-1]) {
                histgram[k]++;
                k = 0;
            }
            k++;
        }
        histgram[k]++;

        for(int i = 1; i <= n; i++)
            printf("%d\n", histgram[i]);

    }

    return 0;
}

