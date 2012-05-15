#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define N 20

int h, w;
int field[N][N];

#define WRAP(i,h) ( ( (i) + h ) % h )

int floodfill(int i, int j) {
    if (i < 0 || i >= h)
        return 0;
    if (!field[i][j])
        return 0;
    field[i][j] = false;
    return 1 + 
        floodfill(i+1, j) +
        floodfill(i-1, j) +
        floodfill(i, WRAP(j+1, w)) +
        floodfill(i, WRAP(j-1, w));
}

int main() {

    while(cin >> h >> w) {
        cin >> ws;

        REP(i, h) {
            string s;
            getline(cin, s);
            REP(j, w)
                field[i][j] = (s[j] == 'l');
        }

        int sy, sx;
        cin >> sy >> sx;
        floodfill(sy, sx);

        int res = 0;
        REP(i, h) REP(j, w)
            res >?= floodfill(i, j);
        cout << res << endl;

    }
    return 0;
}
