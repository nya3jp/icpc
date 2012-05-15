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

#define PROBLEM_NAME "segments"
#define COORD_MAX 2000010

long long res = 0;


int bitquery(int* bit, int n, int from, int to) {
    if (from > 0)
        return bitquery(bit, n, 0, to) - bitquery(bit, n, 0, from);
    int res = 0;
    for(int k = to-1; k >= 0; k = (k & (k+1)) - 1)
        res += bit[k];
    return res;
}

void bitupdate(int* bit, int n, int pos, int delta) {
    while(pos < n) {
        bit[pos] += delta;
        pos |= pos+1;
    }
}

struct S {
    bool horz;
    int t, from, to;
};

struct EL {
    int t, u;
    bool out;
    friend bool operator<(const EL& a, const EL& b) {
        if (a.t != b.t)
            return (a.t < b.t);
        if (a.u != b.u)
            return (a.u < b.u);
        return (a.out < b.out);
    }
};

struct ES {
    int y;
    int type;
    int from, to;
    friend bool operator<(const ES& a, const ES& b) {
        if (a.y != b.y)
            return (a.y < b.y);
        return (a.type < b.type);
    }
};


int n;
S segs[100000+10];


void check_overlaps(S* segs, int n) {
    EL* q = new EL[n*2];
    REP(i, n) {
        S& s = segs[i];
        q[i*2+0] = (EL){s.t, s.from, false};
        q[i*2+1] = (EL){s.t, s.to, true};
    }
    sort(q, q+n*2);
    int cnt = 0;
    REP(i, n*2) {
        EL& e = q[i];
        if (!e.out) {
            res += cnt;
            cnt++;
        }
        else {
            cnt--;
        }
    }
    delete[] q;
}

void sweep(S* segh, int nHorz, S* segv, int nVert) {
    int m = nHorz + nVert*2;

    ES* q = new ES[m];
    {
        ES* p = q;
        REP(i, nHorz) {
            S& s = segh[i];
            *p++ = (ES){s.t, 1, s.from, s.to};
        }
        REP(i, nVert) {
            S& s = segv[i];
            *p++ = (ES){s.from, 0, s.t, s.t};
            *p++ = (ES){s.to, 2, s.t, s.t};
        }
    }
    sort(q, q+m);

    int* v = new int[COORD_MAX];
    memset(v, 0, sizeof(int)*COORD_MAX);

    REP(i, m) {
        ES& e = q[i];
        switch(e.type) {
        case 0: {
            bitupdate(v, COORD_MAX, e.from, 1);
        } break;
        case 1: {
            res += bitquery(v, COORD_MAX, e.from, e.to+1);
        } break;
        case 2: {
            bitupdate(v, COORD_MAX, e.from, -1);
        } break;
        default:
            abort();
        }
    }

    delete[] q;
}


int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    scanf("%d", &n);

    REP(i, n) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 += 1000000;
        y1 += 1000000;
        x2 += 1000000;
        y2 += 1000000;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        if (x1 == x2)
            segs[i] = (S){false, x1, y1, y2};
        else
            segs[i] = (S){true, y1, x1, x2};
    }

    int nHorz = 0;
    REP(i, n) if (segs[i].horz)
        swap(segs[nHorz++], segs[i]);

    check_overlaps(segs, nHorz);
    check_overlaps(segs+nHorz, n-nHorz);
    sweep(segs, nHorz, segs+nHorz, n-nHorz);

    cout << res << endl;

    return 0;
}

