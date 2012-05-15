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

#define N 8000
#define L 16001

int n;

struct Line {
    int x, y1, y2;
};

Line lines[N];
bool adj[N][N];

bool by_x(const Line& a, const Line& b) {
    return (a.x < b.x);
}

struct Interval {
    int y1, y2, id;
};

Interval intervals1[N*3];
Interval intervals2[N*3];

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        scanf("%d", &n);

        REP(i, n) {
            Line& l = lines[i];
            scanf("%d%d%d", &l.y1, &l.y2, &l.x);
            l.y1 *= 3;
            l.y1--;
            l.y2 *= 3;
            l.y2++;
        }

        sort(lines, lines+n, by_x);

        memset(adj, 0, sizeof(adj));

        Interval* intervals = intervals1;
        Interval* newintervals = intervals2;
        int nIntervals = 0;
        REP(iLine, n) {
            Line line = lines[iLine];

            bool inserted = false;
            int nNewIntervals = 0;
            //printf("{ ");
            REP(i, nIntervals) {
                Interval& in = intervals[i];
                //printf("([%d,%d], %d) ", in.y1, in.y2, in.id);
                if (in.y2 <= line.y1) {
                    newintervals[nNewIntervals++] = in;
                }
                else if (line.y2 <= in.y1) {
                    if (!inserted) {
                        newintervals[nNewIntervals++] = (Interval){line.y1, line.y2, iLine};
                        inserted = true;
                    }
                    newintervals[nNewIntervals++] = in;
                }
                else if (line.y1 <= in.y1 && in.y2 <= line.y2) {
                    if (!inserted) {
                        newintervals[nNewIntervals++] = (Interval){line.y1, line.y2, iLine};
                        inserted = true;
                    }
                    adj[in.id][iLine] = true;
                    adj[iLine][in.id] = true;
                }
                else if (in.y1 < line.y1 && line.y2 < in.y2) {
                    newintervals[nNewIntervals++] = (Interval){in.y1, line.y1, in.id};
                    newintervals[nNewIntervals++] = (Interval){line.y1, line.y2, iLine};
                    inserted = true;
                    newintervals[nNewIntervals++] = (Interval){line.y2, in.y2, in.id};
                    adj[in.id][iLine] = true;
                    adj[iLine][in.id] = true;
                }
                else if (line.y2 < in.y2) {
                    if (!inserted) {
                        newintervals[nNewIntervals++] = (Interval){line.y1, line.y2, iLine};
                        inserted = true;
                    }
                    newintervals[nNewIntervals++] = (Interval){line.y2, in.y2, in.id};
                    adj[in.id][iLine] = true;
                    adj[iLine][in.id] = true;
                }
                else if (in.y1 < line.y1) {
                    newintervals[nNewIntervals++] = (Interval){in.y1, line.y1, in.id};
                    if (!inserted) {
                        newintervals[nNewIntervals++] = (Interval){line.y1, line.y2, iLine};
                        inserted = true;
                    }
                    adj[in.id][iLine] = true;
                    adj[iLine][in.id] = true;
                }
                else {
                    assert(false);
                }
            }
            //printf("}\n");

            if (!inserted) {
                newintervals[nNewIntervals++] = (Interval){line.y1, line.y2, iLine};
                inserted = true;
            }

            swap(nIntervals, nNewIntervals);
            swap(intervals, newintervals);
        }

        /*
        printf("hoge\n");
        REP(i, n) {
            REP(j, n)
                printf("%d", adj[i][j]);
            printf("\n");
        }
        printf("hoge\n");
        */

        int res = 0;
        /*
        REP(k, n) REP(j, k) if (adj[k][j])
            REP(i, j) if (adj[k][i] && adj[j][i])
                res++;
        /*/
        for(int i = 0; i < n; i++)
            for(int k = i+2; k < n; k++)
                if (adj[i][k])
                    for(int j = i+1; j < k; j++)
                        if (adj[i][j] && adj[k][j])
                            res++;
        //*/

        printf("%d\n", res);

    }

    return 0;
}

