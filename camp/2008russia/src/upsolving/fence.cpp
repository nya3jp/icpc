#include <iostream>
#include <vector>
#include <complex>
#include <map>
#include <set>
#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "fence"

int n, m;

struct P { int x, y; };
struct L { int a, b; long long c; };

bool operator<(const L& a, const L& b) {
    if (a.a != b.a)
        return (a.a < b.a);
    if (a.b != b.b)
        return (a.b < b.b);
    return (a.c < b.c);
}

int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    scanf("%d", &n);
    P* ps = new P[n];
    REP(i, n) {
        P& p = ps[i];
        scanf("%d%d", &p.x, &p.y);
    }

    L* ls = new L[n*(n-1)/2];
    m = 0;
    REP(i, n) REP(j, i) {
        P& p = ps[i];
        P& q = ps[j];
        L l = {p.y-q.y, q.x-p.x, (long long)p.x*q.y-(long long)p.y*q.x};
        if (l.a < 0 || (l.a == 0 && l.b < 0)) {
            l.a *= -1;
            l.b *= -1;
            l.c *= -1;
        }
        ls[m++] = l;
    }

    sort(ls, ls+m);

    /*
    REP(i, m) {
        L& l = ls[i];
        cerr << l.a << "," << l.b << "," << l.c << endl;
    }
    */

    long long res = 0;
    {
        int i = 0;
        while(i < m) {
            int j = i+1;
            long long lo = 0;
            long long gr = 1;
            //cerr << "at " << i << endl;
            int k = i;
            while(j < m && ls[i].a == ls[j].a && ls[i].b == ls[j].b) {
                if (ls[k].c != ls[j].c) {
                    k = j;
                    lo += gr;
                    gr = 0;
                }
                gr++;
                res += lo;
                //cerr << "+" << lo << endl;
                j++;
            }
            
            i = j;
        }
    }

    cout << res/2 << endl;

    return 0;
}

