#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

char field[1100][1100];
int connection[512][512];

int DIR[8][2] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};

int main(int argc, char** argv) {

    FILE* fpInput;
    FILE* fpOutput;
    fpInput = fopen("king.in", "r");
    fpOutput = fopen("king.out", "r");

    if (!(fpInput && fpOutput)) {
        puts("failed to open file");
        return 1;
    }

    int h, w;
    fscanf(fpInput, "%d%d", &h, &w);

    char res[16];
    fgets(res, sizeof(res), fpOutput);

    if (strncmp(res, "Yes", 3) != 0) {
        puts("No: no verification");
        return 0;
    }
    else {
        REP(i, h*2-1) {
            fgets(field[i], sizeof(field[0]), fpOutput);
        }
        REP(i, h*2-1) REP(j, w*2-1) {
            if (i%2 == 0 && j%2 == 0) {
                if (field[i][j] != 'o') {
                    printf("no 'o' at (%d,%d)\n", i, j);
                    return 1;
                }
            }
            else if (field[i][j] == '-') {
                if (i%2 != 0 || j%2 != 1) {
                    printf("illegal '-' at (%d,%d)\n", i, j);
                    return 1;
                }
                connection[i/2][j/2] |= 1<<2;
                connection[i/2][j/2+1] |= 1<<6;
            }
            else if (field[i][j] == '|') {
                if (j%2 != 0 || i%2 != 1) {
                    printf("illegal '-' at (%d,%d)\n", i, j);
                    return 1;
                }
                connection[i/2][j/2] |= 1<<0;
                connection[i/2+1][j/2] |= 1<<4;
            }
            else if (field[i][j] == '/') {
                if (i%2 != 1 || j%2 != 1) {
                    printf("illegal '/' at (%d,%d)\n", i, j);
                    return 1;
                }
                connection[i/2+1][j/2] |= 1<<3;
                connection[i/2][j/2+1] |= 1<<7;
            }
            else if (field[i][j] == '\\') {
                if (i%2 != 1 || j%2 != 1) {
                    printf("illegal '\\' at (%d,%d)\n", i, j);
                    return 1;
                }
                connection[i/2][j/2] |= 1<<1;
                connection[i/2+1][j/2+1] |= 1<<5;
            }
            else if (field[i][j] != ' ') {
                printf("illegal '%c' at (%d,%d)\n", field[i][j], i, j);
                return 1;
            }
        }

        REP(i, h) REP(j, w) {
            if (__builtin_popcount(connection[i][j]) != 2) {
                printf("illegal connection at (%d,%d)\n", i, j);
                return 1;
            }
        }

        {
            int dir = connection[0][0];
            dir &= -dir;
            dir = __builtin_ctz(dir);
            int i = 0, j = 0;
            do {
                int di = DIR[dir][0], dj = DIR[dir][1];
                connection[i][j] &= ~(1<<dir);
                i += di;
                j += dj;
                connection[i][j] &= ~(1<<(dir^4));
                int nextdir = __builtin_ctz(connection[i][j]);
                if (dir == nextdir) {
                    printf("not drunken at (%d,%d)\n", i, j);
                    return 1;
                }
                dir = nextdir;
            } while(!(i == 0 && j == 0));
        }

        REP(i, h) REP(j, w) {
            if (connection[i][j]) {
                printf("disconnected component at (%d,%d)\n", i, j);
                return 1;
            }
        }

        puts("Accepted!");

    }

    return 0;
}
