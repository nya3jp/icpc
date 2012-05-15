#include <cstdio>

#define N 1025

int v[N][N];
int u[N][N];

int main() {

    int nCases;
    scanf("%d", &nCases);

    for(int iCase = 0; iCase < nCases; iCase++) {

        for(int y = 0; y < N; y++)
            for(int x = 0; x < N; x++)
                v[y][x] = 0;

        int nSize;
        scanf("%d", &nSize);
        nSize = nSize*2 + 1;

        int nLocations;
        scanf("%d", &nLocations);

        for(int iLocation = 0; iLocation < nLocations; iLocation++) {

            int x, y, r;
            scanf("%d%d%d", &x, &y, &r);

            v[y][x] = r;

        }

        for(int x = 0; x < N; x++) {
            u[nSize-1][x] = 0;
            for(int y = 0; y < nSize; y++) {
                u[nSize-1][x] += v[y][x];
            }
            for(int y = nSize; y < N; y++) {
                u[y][x] = u[y-1][x] + v[y][x] - v[y-nSize][x];
            }
        }

    }

    return 0;
}

