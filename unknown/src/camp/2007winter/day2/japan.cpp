#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

using namespace std;

int graph[1001][1001];

void
solve(int nLeft, int nRight)
{
    vector<int> sum(nRight, 0);

    unsigned long long int cnt = 0;
    REP(iLeft, nLeft) {
        REP(iRight, nRight) {
            if (graph[iLeft][iRight]) {
                cnt += sum[iRight] * graph[iLeft][iRight];
            }
        }

        vector<int> partial(nRight + 1, 0);
        for(int iRight = nRight - 1; iRight >= 0; iRight--) {
            partial[iRight] = graph[iLeft][iRight] + partial[iRight + 1];
        }

        REP(iPartial, nRight) {
            sum[iPartial] += partial[iPartial + 1];
        }
    }

    cout << cnt << endl;
}

int main(void)
{
    freopen("japan.in", "r", stdin);

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        cout << "Test case " << iCase + 1 << ": ";

        REP(i, 1001) REP(j, 1001)
            graph[i][j] = 0;

        int nLeft, nRight, nEdges;
        cin >> nLeft >> nRight >> nEdges;
        REP(iEdges, nEdges) {
            int from, to;
            cin >> from >> to;
            from--; to--;
            graph[from][to] += 1;
        }

        solve(nLeft, nRight);
    }

    return 0;
}
