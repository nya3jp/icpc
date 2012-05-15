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

#define N 10000

int main() {

    for(;;) {
        int n;
        if (scanf("%d", &n) != 1)
            break;

        vector< pair<int,int> > v(n);
        REP(i, n) {
            int p, d;
            scanf("%d%d", &p, &d);
            v[i] = make_pair(N-d, p);
        }
        sort(ALLOF(v));

        int res = 0;
        int iv = 0;
        priority_queue<int> q;
        REP(t, N) {
            while(iv < n) {
                if (v[iv].first == t)
                    q.push(v[iv++].second);
                else
                    break;
            }
            if (!q.empty()) {
                res += q.top();
                q.pop();
            }
        }

        printf("%d\n", res);

    }

    return 0;
}
