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

map<string, int> memo;
int uf[100000+10];

int find_root(int a) {
    return (uf[a] < 0 ? a : uf[a] = find_root(uf[a]));
}
int connect(int a, int b) {
    int ra = find_root(a);
    int rb = find_root(b);
    if (ra != rb) {
        if (uf[ra] > uf[rb])
            swap(ra, rb);
        uf[ra] += uf[rb];
        uf[rb] = ra;
    }
    return -uf[ra];
}

inline int id(string s) {
    map<string,int>::iterator it = memo.find(s);
    if (it == memo.end())
        it = memo.insert(make_pair(s, memo.size())).first;
    return it->second;
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        int n;
        scanf("%d", &n);
        memo.clear();
        memset(uf, -1, sizeof(uf));

        REP(i, n) {
            char a[64], b[64];
            scanf("%s%s", a, b);
            printf("%d\n", connect(id(a), id(b)));
        }

    }

    return 0;
}
