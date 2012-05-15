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

int digits[5000], trace[5000];

int main() {

    for(;;) {
        int n, m;
        if (scanf("%d%d", &n, &m) != 2)
            break;

        bool ok[10] = {};
        REP(i, m) {
            int x;
            scanf("%d", &x);
            ok[x] = true;
        }

        vector<int> res;
        if (n == 0) {
            res.push_back(0);
        }
        else {
            memset(trace, -1, sizeof(trace));
            memset(digits, -1, sizeof(digits));
            queue<int> q;
            REP(d, 10) if (d > 0 && ok[d]) {
                int here = d % n;
                if (trace[here] < 0) {
                    trace[here] = -2;
                    digits[here] = d;
                    q.push(here);
                }
            }
            while(!q.empty()) {
                int here = q.front();
                q.pop();
                if (here == 0)
                    break;
                REP(d, 10) if (ok[d]) {
                    int there = (here * 10 + d) % n;
                    if (trace[there] == -1) {
                        trace[there] = here;
                        digits[there] = d;
                        q.push(there);
                    }
                }
            }
            if (trace[0] < 0) {
                res.push_back(0);
            }
            else {
                for(int i = 0; i >= 0; i = trace[i])
                    res.push_back(digits[i]);
            }
        }
        reverse(ALLOF(res));
        REP(i, res.size())
            printf("%d", res[i]);
        printf("\n");
    }

    return 0;
}
