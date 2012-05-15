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

typedef complex<int> P;

bool xy_less(const P& a, const P& b) {
    if (a.imag() == b.imag())
        return (a.real() < b.real());
    return (a.imag() < b.imag());
}
int ccw(P a, P b, P c) {
    return (conj(b-a)*(c-a)).imag();
}
template<class IN>
void walk_rightside(IN begin, IN end, vector<P>& v) {
    IN cur = begin;
    v.push_back(*cur++);
    vector<P>::size_type s = v.size();
    v.push_back(*cur++);
    while(cur != end) {
        if (v.size() == s || ccw(v[v.size()-2], v.back(), *cur) > 0)
            v.push_back(*cur++);
        else
            v.pop_back();
    }
    v.pop_back();
}
vector<P> convex_hull(vector<P> v) {
    if (v.size() <= 1)
        return v;
    sort(ALLOF(v), xy_less);
    vector<P> cv;
    walk_rightside(v.begin(), v.end(), cv);
    walk_rightside(v.rbegin(), v.rend(), cv);
    return cv;
}

// BE CAREFUL OF PRECONDITIONS!!!
int farthest(const vector<P>& v) {
    int n = v.size();

    int si = 0, sj = 0;
    REP(t, n) {
        if (v[t].imag() < v[si].imag())
            si = t;
        if (v[t].imag() > v[sj].imag())
            sj = t;
    }

    int res = 0;
    int i = si, j = sj;
    do {
        res >?= norm(v[i]-v[j]);
        P di = v[(i+1)%n] - v[i];
        P dj = v[(j+1)%n] - v[j];
        if ((conj(di)*dj).imag() >= 0)
            j = (j+1)%n;
        else
            i = (i+1)%n;
    } while(!(i == si && j == sj));

    return res;
}


int main() {

    int n;
    cin >> n;

    vector<P> v(n);
    REP(i, n) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[i] = P(x, y);
    }

    v = convex_hull(v);
    reverse(ALLOF(v));

    int res = farthest(v);
    cout << res << endl;

    return 0;
}
