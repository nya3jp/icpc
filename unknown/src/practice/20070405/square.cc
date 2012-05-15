#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

typedef long long int integer;

struct rect_t {
    int x1, x2, y1, y2;
};


integer f1(integer w, integer h) {
    int n = min(w, h);
    int m = max(w, h);
    return n*(n+1)*(2*n+1)/6-(n+m+2)*n*(n+1)/2+n*(n*m+n+m+1);
}

integer f2(integer l, integer m, integer M) {
    if (m > M)
        swap(m, M);
    if (l-1 < m) {
        m = l-1;
        return -m*(m+1)*(2*m+1)/6+m*(m+1)*l/2;
    }
    return -m*(m+1)*(2*m+1)/6+m*(m+1)*l/2 + l*m*M - m*M*(M+1)/2 - l*m*m + m*m*(m+1)/2;
}

int main() {

    int iCase = 0;
    for(;;) {

        int n;
        cin >> n;
        if (n == 0)
            break;

        vector<rect_t> v(n);
        REP(i, n) {
            rect_t& r = v[i];
            cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;
            if (r.x1 > r.x2)
                swap(r.x1, r.x2);
            if (r.y1 > r.y2)
                swap(r.y1, r.y2);
        }

        integer res = 0;
        REP(i, n)
            res += f1(v[i].x2-v[i].x1, v[i].y2-v[i].y1);

        REP(i, n) REP(j, n) if (i < j) {
            rect_t a = v[i];
            rect_t b = v[j];
            if (a.y1 > b.y1)
                swap(a, b);
            if (a.y2 == b.y1) {
                int left = max(a.x1, b.x1);
                int right = min(a.x2, b.x2);
                if (right-left > 2) {
                    res += f2(right-left-2, a.y2-a.y1, b.y2-b.y1);
                }
            }
            if (a.x1 > b.x1)
                swap(a, b);
            if (a.x2 == b.x1) {
                int left = max(a.y1, b.y1);
                int right = min(a.y2, b.y2);
                if (right-left > 2) {
                    res += f2(right-left-2, a.x2-a.x1, b.x2-b.x1);
                }
            }
        }

        cout << "Case " << ++iCase << ": " << res << endl;

    }

    return 0;
}
