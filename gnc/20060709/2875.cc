#include <iostream>
#include <algorithm>

using namespace std;


#define N ((100+1)*2+1)

enum State {
    Filled,
    Free,
    Visited,
};

int field[N][N];

int floodfill(int x, int y) {
    if (!(0 <= x && x < N && 0 <= y && y < N))
        return -1;
    if (field[y][x] != Free)
        return 0;
    field[y][x] = Visited;
    int a = (y%2 == 1 && x%2 == 1 ? 1 : 0);
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            int b = floodfill(x+dx, y+dy);
            if (b < 0)
                a = -1;
            if (a >= 0)
                a += b;
        }
    }
    return a;
}

int solve() {
    for(int i = 0; i < N; i++)
        fill(field[i], field[i]+N, Free);

    int cx, cy, m;
    cin >> cx >> cy >> m;
    cx = cx*2;
    cy = cy*2;
    field[cy][cx] = Filled;

    for(int i = 0; i < m; i++) {
        char cmd;
        int len;
        cin >> cmd >> len;
        int dx = 0, dy = 0;
        switch(cmd) {
        case 'N': dy++; break;
        case 'S': dy--; break;
        case 'E': dx++; break;
        case 'W': dx--; break;
        default: assert(false);
        }
        for(int i = 0; i < len*2; i++) {
            cx += dx; cy += dy;
            field[cy][cx] = Filled;
        }
    }

    /*
    for(int y = 0; y < N; y++) {
        for(int x = 0; x < N; x++) {
            cout << (field[y][x] == Filled ? 'x' : '.');
        }
        cout << endl;
    }
    */

    int area = 0;
    for(int y = 0; y < N; y++) {
        for(int x = 0; x < N; x++) {
            if (field[y][x] == Free) {
                int a = floodfill(x, y);
                if (a >= 0)
                    area += a;
            }
        }
    }

    return area;
}


int main() {
    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        cout << "Data Set " << iCase+1 << ": ";
        cout << solve();
        cout << " square feet." << endl;
    }
    cout << "End of Output" << endl;
    return 0;
}
