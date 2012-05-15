#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

struct Interval {
    int from, to;
    int upper;
};

bool upper_less(const Interval& a, const Interval& b) {
    return (a.upper < b.upper);
}
bool better_less(const Interval& a, const Interval& b) {
    if (a.from != b.from || a.to != b.to)
        return make_pair(a.from, a.to) < make_pair(b.from, b.to);
    return (a.upper > b.upper);
}

struct P {
    int x, y;
};

void myunique(vector<Interval>& v) {
    int n = v.size();
    if (n == 0)
        return;
    int i = 0;
    for(int j = 1; j < n; j++) {
        if (v[i].from == v[j].from && v[i].to == v[j].to) {
            // do nothing;
        }
        else {
            v[++i] = v[j];
        }
    }
    v.erase(v.begin()+i+1, v.end());
}

int solve(const vector<P> v) {
    int n = v.size();

    vector<Interval> events;

    REP(i, n) {
        int j = (i+1) % n;
        P from = v[i];
        P to = v[j];

        if (from.y == to.y) {
            // horizontal
            events.push_back((Interval){from.x, to.x, from.y});
        }
    }

    sort(ALLOF(events), upper_less);
    reverse(ALLOF(events));

    vector<Interval> intervals;

    int res = 0;

    REP(iEvent, events.size()) {

        /*
        printf("at %d: \n", events[iEvent].upper);
        REP(i, intervals.size()) {
            printf("(%d,%d) upper=%d\n", intervals[i].from, intervals[i].to, intervals[i].upper);
        }
        */

        const Interval& ev = events[iEvent];

        if (ev.from < ev.to) {
            // lower
            vector<Interval> newIntervals;
            REP(i, intervals.size()) {
                const Interval& here = intervals[i];
                res >?= min(here.to-here.from, here.upper-ev.upper);
                if (here.to <= ev.from || ev.to <= here.from) {
                    newIntervals.push_back(here);
                }
                else if (ev.from <= here.from && here.to <= ev.to) {
                    // do nothing
                }
                else if (here.to <= ev.to) {
                    newIntervals.push_back((Interval){here.from, ev.from, here.upper});
                }
                else if (ev.from <= here.from) {
                    newIntervals.push_back((Interval){ev.to, here.to, here.upper});
                }
                else if (here.from < ev.from && ev.to < here.to) {
                    newIntervals.push_back((Interval){here.from, ev.from, here.upper});
                    newIntervals.push_back((Interval){ev.to, here.to, here.upper});
                }
                else {
                    //printf("ev=(%d,%d) here=(%d,%d)\n", ev.from, ev.to, here.from, here.to);
                    assert(false);
                }
            }
            sort(ALLOF(newIntervals), better_less);
            myunique(newIntervals);
            // unique
            intervals = newIntervals;
        }
        else {
            // upper
            int left = ev.to, right = ev.from;
            REP(i, intervals.size()) {
                if (intervals[i].to == ev.to)
                    left <?= intervals[i].from;
                if (intervals[i].from == ev.from)
                    right >?= intervals[i].to;
            }
            intervals.push_back((Interval){left, right, ev.upper});
        }

    }

    return res;
}


int main() {

    freopen("roof.in", "r", stdin);

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n;
        cin >> n;

        vector<P> v(n);
        REP(i, n)
            cin >> v[i].x >> v[i].y;

        int res = solve(v);
        if (res%2 == 0) {
            printf("%d.0\n", res/2);
        }
        else {
            printf("%d.5\n", res/2);
        }

    }

    return 0;
}



