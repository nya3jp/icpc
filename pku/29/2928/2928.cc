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

#define N 100000

int horz[N], vert[N];
int h, w, lower, upper;

int solve_min() {
    int res = 0;
    int i = 0, j = 0;
    while(i < h && j < w) {
        if (horz[i] == vert[j] && i+1 < h && j+1 < w) {
            res += horz[i];
            i++;
            j++;
        }
        else if (horz[i] <= vert[j] && i+1 < h) {
            res += horz[i];
            i++;
        }
        else if (horz[i] >= vert[j] && j+1 < w) {
            res += vert[j];
            j++;
        }
        else if (horz[i] == vert[j] && i+1 == h && j+1 == w) {
            res += horz[i];
            break;
        }
        else {
            return -1;
        }
    }
    return res;
}

int solve_max() {
    int res = 0;

    int i = 0, j = 0;
    while(i < h && j < w) {
        if (horz[i] == vert[j]) {
            res += horz[i]*((h-i)+(w-j)-1);
            i++;
            j++;
        }
        else if (horz[i] < vert[j]) {
            res += horz[i]*(w-j);
            i++;
        }
        else if (horz[i] > vert[j]) {
            res += vert[j]*(h-i);
            j++;
        }
    }
    return res;
}

int main() {
    scanf("%d%d%d%d", &h, &w, &lower, &upper);

    REP(i, h)
        scanf("%d", &horz[i]);
    REP(i, w)
        scanf("%d", &vert[i]);

    sort(horz, horz+h);
    sort(vert, vert+w);

    int minimum = solve_min();
    int maximum = solve_max();

    if (minimum < 0 || maximum < 0)
        printf("Impossible\n");
    else
        printf("Minimum: %d, maximum: %d\n", lower*minimum, upper*maximum);

    return 0;
}

