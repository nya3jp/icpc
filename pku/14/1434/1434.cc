#include <cstdio>
#include <map>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

struct Interval {
    int height;
    int width;
    int bottom;
};

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        int nCells;
        scanf("%d", &nCells);

        map<int, int> levelMap;

        REP(iCell, nCells) {
            int b, h, w, d;
            scanf("%d%d%d%d", &b, &h, &w, &d);
            int f = w * d;
            levelMap[b] += f;
            levelMap[b+h] -= f;
        }
        int flood;
        scanf("%d", &flood);

        int nIntervals = (int)levelMap.size() - 1;

        vector<Interval> intervals;
        intervals.reserve(nIntervals);
        {
            map<int, int>::iterator first = levelMap.begin();
            map<int, int>::iterator second = levelMap.begin(); ++second;
            map<int, int>::iterator last = levelMap.end();
            int current = 0;
            while(second != last) {
                current += first->second;
                intervals.push_back((Interval){second->first - first->first, current, first->first});
                ++first;
                ++second;
            }
        }
        assert((int)intervals.size() == nIntervals);

        /*
        REP(i, nIntervals) {
            Interval& v = intervals[i];
            printf("%d: %d x %d\n", v.bottom, v.height, v.width);
        }
        printf("\n");
        */

        double res = -1;
        int restFlood = flood;
        REP(iInterval, nIntervals) {
            Interval& iv = intervals[iInterval];
            int consume = iv.height * iv.width;
            if (consume >= restFlood) {
                res = iv.bottom + (double)restFlood / iv.width;
                break;
            }
            else {
                restFlood -= consume;
            }
        }

        if (res < -0.5) {
            printf("OVERFLOW\n");
        }
        else {
            printf("%.2f\n", res+1.0e-10);
        }

    }

    return 0;
}

