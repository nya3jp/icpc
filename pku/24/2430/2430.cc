#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

#define UPPER  0
#define LOWER  1
#define BOTH   2
#define DOUBLE 3

using namespace std;

#define N 1000
#define INF 100000000

int costs[N][N+1][4];

int main() {

    int nCows, nCoversAll;
    scanf("%d%d%*d", &nCows, &nCoversAll);

    vector< pair<int,int> > v;
    {
        map<int,int> x;
        for(int i = 0; i < nCows; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            x[b] |= 1 << (a-1);
        }
        v.assign(x.begin(), x.end());
    }

    int nLines = (int)v.size();

    for(int iLine = 0; iLine < nLines; iLine++) {
        for(int nCovers = 0; nCovers <= nCoversAll; nCovers++) {
            costs[iLine][nCovers][UPPER] = INF;
            costs[iLine][nCovers][LOWER] = INF;
            costs[iLine][nCovers][BOTH] = INF;
            costs[iLine][nCovers][DOUBLE] = INF;
        }
    }

    costs[0][1][UPPER] = 1;
    costs[0][1][LOWER] = 1;
    costs[0][2][BOTH] = 2;
    costs[0][1][DOUBLE] = 2;
    if ((v[0].second & 1) != 0)
        costs[0][1][LOWER] = INF;
    if ((v[0].second & 2) != 0)
        costs[0][1][UPPER] = INF;


    for(int iLine = 1; iLine < nLines; iLine++) {
        for(int nCovers = 1; nCovers <= nCoversAll; nCovers++) {
            int len = v[iLine].first - v[iLine-1].first;

            costs[iLine][nCovers][DOUBLE] = costs[iLine-1][nCovers][DOUBLE] + len*2;
            for(int t = 0; t < 4; t++)
                costs[iLine][nCovers][DOUBLE] = min(costs[iLine][nCovers][DOUBLE],
                                                    costs[iLine-1][nCovers-1][t] + 2);

            costs[iLine][nCovers][BOTH] = costs[iLine-1][nCovers][BOTH] + len*2;
            if (nCovers >= 2)
                for(int t = 0; t < 4; t++)
                    costs[iLine][nCovers][BOTH] = min(costs[iLine][nCovers][BOTH],
                                                      costs[iLine-1][nCovers-2][t] + 2);

            if ((v[iLine].second & 1) != 0) {
                costs[iLine][nCovers][LOWER] = INF;
            }
            else {
                costs[iLine][nCovers][LOWER] = costs[iLine-1][nCovers][LOWER] + len*1;
                for(int t = 0; t < 4; t++)
                    costs[iLine][nCovers][LOWER] = min(costs[iLine][nCovers][LOWER],
                                                       costs[iLine-1][nCovers-1][t] + 1);
            }

            if ((v[iLine].second & 2) != 0) {
                costs[iLine][nCovers][UPPER] = INF;
            }
            else {
                costs[iLine][nCovers][UPPER] = costs[iLine-1][nCovers][UPPER] + len*1;
                for(int t = 0; t < 4; t++)
                    costs[iLine][nCovers][UPPER] = min(costs[iLine][nCovers][UPPER],
                                                       costs[iLine-1][nCovers-1][t] + 1);
            }

            for(int t = 0; t < 4; t++)
                costs[iLine][nCovers][t] = min(costs[iLine][nCovers][t], INF);
        }
    }


    for(int i = 0; i < nLines; i++) {
        for(int j = 0; j <= nCoversAll; j++) {
            printf("pos=%2d, covers=%2d : %10d %10d %10d %10d\n",
                   i, j, costs[i][j][0], costs[i][j][1], costs[i][j][2], costs[i][j][3]);
        }
    }


    printf("%d\n", min(costs[nLines-1][nCoversAll][0],
                       min(costs[nLines-1][nCoversAll][1],
                           min(costs[nLines-1][nCoversAll][2],
                               costs[nLines-1][nCoversAll][3]))));

    return 0;
}
