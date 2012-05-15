/*
 * UVA 10443 Rock, Scissors, Paper
 * 2005-08-08
 * by nya
 */

#include <cstdio>

#define N 100

int main() {
    int nCases;
    std::scanf("%d", &nCases);
    for(int iCase=0; iCase<nCases; iCase++) {
        int nRows, nCols, n;
        std::scanf("%d%d%d", &nRows, &nCols, &n);
        int table[N+2][N+2];
        for(int y=0; y<=nRows+1; y++) {
            table[y][0] = table[y][nCols+1] = -1;
        }
        for(int x=0; x<=nCols+1; x++) {
            table[0][x] = table[nRows+1][x] = -1;
        }
        for(int y=1; y<=nRows; y++) {
            for(int x=1; x<=nCols; x++) {
                char c;
                std::scanf(" %c", &c);
                table[y][x] = (c == 'R' ? 0 : c == 'S' ? 1 : 2);
            }
        }
        for(int r=0; r<n; r++) {
            int newtable[N+2][N+2];
            for(int y=1; y<=nRows; y++) {
                for(int x=1; x<=nCols; x++) {
                    if (table[y-1][x] == (table[y][x]+2)%3 ||
                        table[y+1][x] == (table[y][x]+2)%3 ||
                        table[y][x-1] == (table[y][x]+2)%3 ||
                        table[y][x+1] == (table[y][x]+2)%3 ) {
                        newtable[y][x] = (table[y][x]+2)%3;
                    }
                    else {
                        newtable[y][x] = table[y][x];
                    }
                }
            }
            for(int y=1; y<=nRows; y++) {
                for(int x=1; x<=nCols; x++) {
                    table[y][x] = newtable[y][x];
                }
            }
        }

        if (iCase > 0)
            std::printf("\n");
        for(int y=1; y<=nRows; y++) {
            for(int x=1; x<=nCols; x++) {
                int k = table[y][x];
                std::printf("%c", (k == 0 ? 'R' : k == 1 ? 'S' : 'P'));
            }
            std::printf("\n");
        }
    }
    return 0;
}
