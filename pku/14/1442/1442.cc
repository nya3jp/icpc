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

#define N 30000

int v[N], u[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    REP(i, n)
        scanf("%d", &v[i]);
    REP(j, m)
        scanf("%d", &u[j]);

    multiset< pair<int, int> > s;
    s.insert(make_pair(-numeric_limits<int>::max(), -1));
    multiset< pair<int, int> >::iterator it = s.begin();

    int c = 0;
    REP(j, m) {
        while(c < u[j]) {
            int t = v[c];
            s.insert(make_pair(t, c));
            if (t < it->first)
                --it;
            c++;
        }
        ++it;
        printf("%d\n", it->first);
    }

    return 0;
}
