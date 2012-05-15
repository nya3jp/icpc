#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int n;
int table[1001][1001];

inline int count_points(int x, int y, int w, int h) {
    return table[x+w][y+h] - table[x-1][y+h] - table[x+w][y-1] + table[x-1][y-1];
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    while(nCases-- > 0) {

        long long int area;
        scanf("%d", &n);
        cin >> area;

        REP(x, 1001) REP(y, 1001)
            table[x][y] = 0;

        REP(i, n) {
            int x, y;
            scanf("%d%d", &x, &y);
            table[x][y]++;
        }

        for(int x = 1; x <= 1000; x++)
            for(int y = 1; y <= 1000; y++)
                table[x][y] += table[x-1][y] + table[x][y-1] - table[x-1][y-1];

        vector<long long int> divides0;
        for(long long int d = 1; d <= area; d++)
            if (area%d == 0)
                divides0.push_back(d);

        int nDivides = divides0.size();
        long long int* divides = &divides0[0];

        int res = 0;
        REP(i, nDivides) {
            long long int w = divides[i];
            long long int h = area / divides[i];
            for(long long int x = 1; x <= 1000-w; x++) {
                for(long long int y = 1; y <= 1000-h; y++) {
                    res >?= count_points(x, y, w, h);
                }
            }
        }

        printf("%d\n", res);

    }

    return 0;
}

