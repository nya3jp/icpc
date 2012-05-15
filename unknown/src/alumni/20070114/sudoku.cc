#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("a.in");
#define cin fin

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define REP0(i,n) for(i = 0; i < (int)(n); i++)

int row_perm[9], col_perm[9];

int perm3[6][3] = {
    {0, 1, 2},
    {0, 2, 1},
    {1, 0, 2},
    {1, 2, 0},
    {2, 0, 1},
    {2, 1, 0},
};

int answer[9][9];
int problem[9][10];

bool check() {
    int m[10];
    REP(i, 10)
        m[i] = -1;

    REP(i, 9) REP(j, 9) {
        int p = problem[row_perm[i]][col_perm[j]];
        if (p > 0) {
            int a = answer[i][j];
            if (m[p] < 0) {
                m[p] = a;
            }
            else if (m[p] != a) {
                return false;
            }
        }
    }
    return true;
}

bool make_perm() {
    int r[3], c[3];
    REP(r0, 6) REP0(r[0], 6) REP0(r[1], 6) REP0(r[2], 6) {
        REP(i, 3) REP(j, 3)
            row_perm[i*3+j] = perm3[r[i]][j] + perm3[r0][i]*3;
        /*
        REP(i, 9)
            cout << row_perm[i] << ' ';
        cout << endl;
        */
        REP(c0, 6) REP0(c[0], 6) {
            REP(i, 1) REP(j, 3)
                col_perm[i*3+j] = perm3[c[i]][j] + perm3[c0][i]*3;
            col_perm[3] = col_perm[4] = col_perm[5] = 9;
            col_perm[6] = col_perm[7] = col_perm[8] = 9;
            if (!check())
                continue;
            REP0(c[1], 6) {
                REP(i, 2) REP(j, 3)
                    col_perm[i*3+j] = perm3[c[i]][j] + perm3[c0][i]*3;
                col_perm[6] = col_perm[7] = col_perm[8] = 9;
                if (!check())
                    continue;
                REP0(c[2], 6) {
                    REP(i, 3) REP(j, 3)
                        col_perm[i*3+j] = perm3[c[i]][j] + perm3[c0][i]*3;
                    if (check())
                        return true;
                }
            }
        }
    }
    return false;
}


void rotate() {
    int tmp[9][9];
    REP(i, 9) REP(j, 9)
        tmp[j][8-i] = problem[i][j];
    REP(i, 9) REP(j, 9)
        problem[i][j] = tmp[i][j];
}


int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        REP(i, 9) {
            int t;
            cin >> t;
            for(int j = 0, p = 1; j < 9; j++, p*=10)
                answer[i][8-j] = t / p % 10;
        }
        REP(i, 9) {
            int t;
            cin >> t;
            for(int j = 0, p = 1; j < 9; j++, p*=10)
                problem[i][8-j] = t / p % 10;
            problem[i][9] = 0;
        }

        int res = false;
        res = res || make_perm();
        rotate();
        res = res || make_perm();
        rotate();
        res = res || make_perm();
        rotate();
        res = res || make_perm();
        cout << (res ? "Yes" : "No") << endl;
    }
    return 0;
}
