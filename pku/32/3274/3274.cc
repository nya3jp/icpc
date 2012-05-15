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

#define N 100000
#define M 30

int n, m;

int cows[N+1][M];
int ofs[N+1];
int ind[N+1];

bool cmp(int a, int b) {
    REP(i, m)
        if (cows[a][i] != cows[b][i])
            return cows[a][i] < cows[b][i];
    return (ofs[a] < ofs[b]);
}

int main() {

    scanf("%d%d", &n, &m);

    REP(i, n) {
        int x;
        scanf("%d", &x);
        REP(j, m) {
            cows[i+1][j] += cows[i][j];
            if (x&1)
                cows[i+1][j]++;
            x >>= 1;
        }
    }
    n++;
    REP(i, n) {
        ofs[i] = *min_element(cows[i], cows[i]+m);
        REP(j, m)
            cows[i][j] -= ofs[i];
    }

    REP(i, n)
        ind[i] = i;
    sort(ind, ind+n, cmp);

    /*
    REP(i, n) {
        printf("%d: ", ind[i]);
        REP(j, m)
            printf("%d,", cows[ind[i]][j]);
        printf("\n");
    }
    */

    int res = 0;
    {
        int first = 0;
        while(first < n) {
            int last = first+1;
            while(last < n && equal(cows[ind[first]], cows[ind[first]]+m, cows[ind[last]]))
                last++;
            res >?= ind[last-1] - ind[first];
            first = last;
        }
    }

    printf("%d\n", res);

    return 0;
}
