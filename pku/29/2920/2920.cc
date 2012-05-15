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

#define N 300

char field[N+4][N+4];
const int adj[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};

void solve() {

    int n, m;
    cin >> n >> m;

    n += 4;
    REP(i, n) REP(j, n)
        field[i][j] = '?';
    REP(i, n)
        field[i][0] = field[i][n-1] = field[0][i] = field[n-1][i] = '*';

    REP(i, m) {
        int x, y;
        scanf("%d%d", &y, &x);
        x++; y++;
        field[y][x] = '*';
    }

    queue<pair<int,int> > q;
    q.push(make_pair(n/2, n/2));
    field[n/2][n/2] = '@';
    while(!q.empty()) {
        int ci = q.front().first;
        int cj = q.front().second;
        q.pop();
        bool mine = false;
        REP(dir, 8) {
            int di = ci+adj[dir][0];
            int dj = cj+adj[dir][1];
            if (field[di][dj] == '*')
                mine = true;
        }
        if (mine) {
            field[ci][cj] = '#';
        }
        else {
            field[ci][cj] = '.';
            REP(dir, 8) {
                int di = ci+adj[dir][0];
                int dj = cj+adj[dir][1];
                if (field[di][dj] == '?') {
                    field[di][dj] = '@';
                    q.push(make_pair(di, dj));
                }
            }
        }
    }

    for(int i = 2; i < n-2; i++) {
        for(int j = 2; j < n-2; j++)
            printf("%c", field[i][j]);
        printf("\n");
    }
}

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        cout << "Scenario #" << iCase+1 << ":" << endl;
        solve();
        cout << endl;
    }

    return 0;
}
