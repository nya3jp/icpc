#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

inline bool IN(int a, int b, int c) {
    return (b <= a && a < c);
}
typedef long long int integer;

int main() {

    int initSpeed, H, W;
    cin >> initSpeed >> H >> W;

    int field[100][100];

    REP(i, H) REP(j, W) {
        int& r = field[i][j];
        cin >> r;
        r = 25 + r;
    }

    typedef pair<int,int> point;
    typedef pair<integer, point> node;
    priority_queue<node, vector<node>, greater<node> > q;
    q.push(make_pair(0, make_pair(0, 0)));

    vector< vector<bool> > visited(H, vector<bool>(W, false));

    integer res;

    while(!q.empty()) {

        integer currentTime = q.top().first;
        point here = q.top().second;
        q.pop();

        if (visited[here.first][here.second])
            continue;
        visited[here.first][here.second] = true;

        if (here == make_pair(H-1, W-1)) {
            res = currentTime;
            break;
        }

        //printf("(%d,%d): %16llx\n", here.first, here.second, currentTime);

        for(int di = -1; di <= 1; di++) {
            for(int dj = -1; dj <= 1; dj++) {
                if (abs(di)+abs(dj) == 1) {
                    point there(here.first+di, here.second+dj);
                    if (IN(there.first, 0, H) && IN(there.second, 0, W)) {
                        q.push(make_pair(currentTime+(1ll<<field[here.first][here.second]), there));
                    }
                }
            }
        }
    }

    double ans = (double)res / initSpeed / (1ll << field[0][0]);

    printf("%.2f\n", ans);


    return 0;
}




