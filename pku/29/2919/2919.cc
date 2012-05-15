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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

char field[8][8];
int visits[8][8];

const int adj[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};

struct State {
    int i, j, k;
};
int dp[8][8][1<<14];
State trace[8][8][1<<14];
bool reaches[8][8][8][8];
int goes[8][8][64+1][2];
bool goals[8][8];

inline bool valid(int i, int j) {
    return (0 <= i && i < 8 && 0 <= j && j < 8);
}

string solve() {

    int si, sj, ti, tj;
    REP(i, 8) REP(j, 8)
        if (field[i][j] == 'Q')
            si = i, sj = j;
    REP(i, 8) REP(j, 8)
        if (field[i][j] == 'B')
            ti = i, tj = j;

    REP(i, 8) REP(j, 8)
        visits[i][j] = 0;
    REP(i, 8) REP(j, 8)
        goals[i][j] = false;

    int n = 0;
    REP(i, 8) REP(j, 8) {
        char cell = field[i][j];
        if (cell == 'N') {
            REP(dir, 8) {
                int ii = i+adj[dir][0];
                int jj = j+adj[dir][1];
                if (valid(ii, jj))
                    visits[ii][jj] |= 1<<n;
            }
            n++;
            visits[i][j] = -1;
        }
        else if (cell == 'P') {
            visits[i][j] = -1;
        }
        else if (cell == 'B') {
            REP(dir, 8) {
                int ii = i+adj[dir][0];
                int jj = j+adj[dir][1];
                if (valid(ii, jj))
                    goals[ii][jj] = true;
            }
            visits[i][j] = -1;
        }
    }

    REP(i, 8) REP(j, 8) REP(ii, 8) REP(jj, 8)
        reaches[i][j][ii][jj] = false;
    REP(i, 8) REP(j, 8) {
        REP(dir, 8) {
            int di = adj[dir][0], dj = adj[dir][1];
            REP(l, 8) {
                int ii = i+di*l, jj = j+dj*l;
                if (!valid(ii, jj))
                    break;
                char cell = field[ii][jj];
                if (cell == 'P' || cell == 'B' || cell == 'N')
                    break;
                reaches[i][j][ii][jj] = true;
            }
        }
    }
    REP(i, 8) REP(j, 8) {
        int c = 0;
        REP(jj, 8) REP(ii, 8)
            if (reaches[i][j][ii][jj])
                goes[i][j][c][0] = ii, goes[i][j][c][1] = jj, c++;
        goes[i][j][c][0] = goes[i][j][c][1] = -1;
    }

    if (0) {
        REP(ix, 8) {
            int i = 7-ix;
            REP(j, 8) {
                if (i == si && j == sj)
                    printf("Q");
                else
                    printf("%c", (reaches[si][sj][i][j] ? 'x' : '.'));
            }
            printf("\n");
        }
    }
    
    REP(i, 8) REP(j, 8) REP(k, 1<<n)
        dp[i][j][k] = -1;

    queue<State> q;
    q.push((State){si, sj, visits[si][sj]});
    dp[si][sj][visits[si][sj]] = 0;
    trace[si][sj][visits[si][sj]] = (State){-1, -1, 0};

    if (visits[si][sj] == (1<<n)-1 && goals[si][sj]) {
        ti = si;
        tj = sj;
        goto END;
    }

    while(!q.empty()) {
        int ci = q.front().i;
        int cj = q.front().j;
        int ck = q.front().k;
        //printf("(%d,%d) %08x\n", ci, cj, ck);
        q.pop();
        REP(p, 64) {
            if (goes[ci][cj][p][0] < 0)
                break;
            int di = goes[ci][cj][p][0];
            int dj = goes[ci][cj][p][1];
            //printf("-> (%d,%d)\n", di, dj);
            int v = visits[di][dj];
            if (dp[di][dj][ck|v] < 0) {
                dp[di][dj][ck|v] = dp[ci][cj][ck] + 1;
                trace[di][dj][ck|v] = (State){ci, cj, ck};
                q.push((State){di, dj, ck|v});
                if ((ck|v) == (1<<n)-1 && goals[di][dj]) {
                    ti = di;
                    tj = dj;
                    goto END;
                }
            }
        }
    }
    return "impossible";

END:
    string res;
    State cur = {ti, tj, (1<<n)-1};
    while(cur.i >= 0) {
        res = string(1, (char)('a'+cur.j)) + string(1, (char)('1'+cur.i)) + res;
        cur = trace[cur.i][cur.j][cur.k];
    }
    return res;
}

int main() {

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {

        string s;
        REP(i, 8) {
            cin >> s;
            REP(j, 8)
                field[7-i][j] = s[j];
        }

        cout << "Scenario #" << iCase+1 << ":" << endl;
        cout << solve() << endl;
        cout << endl;

    }

    return 0;
}


// Powered by Fate Testarossa
