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

#define N 1000
#define INF 100000000

bool field[2*N-1][2*N-1];
int h, w;

void draw(int x, int y, int dx, int dy) {
    int ox = x, oy = y;

    for(;;) {
        field[y][x] = true;

        x += dx; y += dy;

        bool horz = (x == 0 || x == w-1);
        bool vert = (y == 0 || y == h-1);

        if (horz&&vert) {
            field[y][x] = true;
            break;
        }

        if (horz)
            dx = -dx;
        if (vert)
            dy = -dy;

        if (x == ox && y == oy)
            break;
    }
}

int* q = new int[2*N*2*N*2];

int search(int ox, int oy) {
    bool out = false;
    int res = 0;

    //vector< pair<int,int> > q;
    //q.push_back(make_pair(ox, oy));
    int qn = 0;
    q[qn++] = ox;
    q[qn++] = oy;

    field[oy][ox] = true;
    //while(!q.empty()) {
    while(qn > 0) {
        //int x = q.back().first;
        //int y = q.back().second;
        //q.pop_back();
        int y = q[--qn];
        int x = q[--qn];
        res++;
        const int DIRS[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        REP(dir, 4) {
            int dx = DIRS[dir][0];
            int dy = DIRS[dir][1];
            int xx = x+dx;
            int yy = y+dy;
            if (!IN(xx, 0, w) || !IN(yy, 0, h)) {
                out = true;
            }
            else if (!field[yy][xx]) {
                field[yy][xx] = true;
                //q.push_back(make_pair(xx, yy));
                q[qn++] = xx;
                q[qn++] = yy;
            }
        }
    }

    return (out ? 0 : res);
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        cin >> h >> w;
        h = h*2-1;
        w = w*2-1;

        int y, x;
        cin >> y >> x;
        y = 2*(y-1);
        x = 2*(x-1);

        string dir;
        cin >> dir;
        int dx, dy;
        dy = (dir[0] == 'D' ? 1 : -1);
        dx = (dir[1] == 'R' ? 1 : -1);

        REP(i, h) REP(j, w)
            field[i][j] = false;
        //cerr << "draw:" << endl;
        draw(x, y, dx, dy);

        //cerr << "search:" << endl;
        int res = 0;
        REP(i, h) REP(j, w) {
            if (!field[i][j]) {
                int size = search(j, i);
                if (size > 0)
                    res++;

            }
        }

        cout << res << endl;
    }

    return 0;
}



// Powered by fate testarossa
