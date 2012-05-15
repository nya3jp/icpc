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

typedef complex<double> P;

struct L {
    P pos, dir;
};

struct C {
    P c;
    double r;
};


L belt(const C& a, const C& b, bool ccwa, bool ccwb) {
    if (ccwa == ccwb) {
        double th = acos((a.r-b.r)/abs(a.c-b.c));
        P d = (b.c-a.c)*polar(1.0, th * (ccwa ? -th : th));
        d /= abs(d);
        return (L){a.c + d*a.r, d*P(0, 1)};
    }
    else {
        double th = acos((
    }
}
