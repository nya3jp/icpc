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

struct P {
    int x, y;
};

bool by_x(const P& a, const P& b) {
    return (a.x < b.x);
}

int main() {

    int n, a, b, c;
    scanf("%d%d%d%d", &n, &a, &b, &c);

    vector<P> v(n);
    REP(i, n) {
        P& p = v[i];
        scanf("%d%d", &p.x, &p.y);
    }

    sort(ALLOF(v), by_x);

    int res = 0;
    REP(iy, n) {
        int by = v[iy].y;
        priority_queue<int> q;
        for(int ix = n-1; ix >= 0; ix--) {
            P& p = v[ix];
            if (p.y >= by) {
                int dy = p.y - by;
                int dx = (c - b * dy) / a;
                q.push(p.x - dx);
            }
            while(!q.empty() && q.top() > p.x)
                q.pop();
            res >?= (int)q.size();
        }
    }
    printf("%d\n", res);

    return 0;
}
