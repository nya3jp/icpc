#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

struct P {
    int x, y;
};

struct L {
    int a, b, c;
};

bool operator==(const L& a, const L& b) {
    return (a.a == b.a && a.b == b.b && a.c == b.c);
}
bool operator<(const L& a, const L& b) {
    if (a.a != b.a)
        return (a.a < b.a);
    if (a.b != b.b)
        return (a.b < b.b);
    return (a.c < b.c);
}

int gcd(int a, int b) {
    return (b == 0 ? a : gcd(b, a%b));
}

// check OVERFLOW




int main() {

    int iCase = 0;
    for(;;) {

        int n;
        cin >> n;
        if (n == 0)
            break;

        vector<P> v(n);
        REP(i, n) {
            P& p = v[i];
            cin >> p.x >> p.y;
        }

        vector<L> lines;
        REP(i, n) REP(j, n) if (i < j) {
            int dx = v[j].x - v[i].x;
            int dy = v[j].y - v[i].y;
            int x0 = v[i].x;
            int y0 = v[i].y;

            // dy(x-x0) = dx(y-y0)
            // dy x - dx y + dx y0 - dy x0 = 0
            int a = dy;
            int b = -dx;
            int c = dx*y0 - dy*x0;

            int g = gcd(abs(a), gcd(abs(b), abs(c)));

            a /= g;
            b /= g;
            c /= g;

            if (a < 0 || (a == 0 && b < 0)) {
                a *= -1;
                b *= -1;
                c *= -1;
            }

            lines.push_back((L){a, b, c});
        }

        sort(ALLOF(lines));

        int m = 1;
        int k = 1;
        for(int i = 1; i < (int)lines.size(); i++) {
            if (lines[i] == lines[i-1]) {
                k++;
                m >?= k;
            }
            else {
                k = 1;
            }
        }

        int res = 0;
        REP(i, n+1)
            if (i*(i-1)/2 == m)
                res = i;

        if (res < 4)
            res = 0;

        cout << "Photo " << ++iCase << ": " << res << " points eliminated" << endl;
    }

    return 0;
}

