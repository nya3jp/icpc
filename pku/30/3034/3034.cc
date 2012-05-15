//#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <utility>

using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

int gcd(int a, int b) {
    return (b == 0 ? a : gcd(b, a%b));
}
int iabs(int a) {
    return (a < 0 ? -a : a);
}

int D, N, M;

int mem[10][120][120];
bool moles[10][120][120];
//vector< map< pair<int,int> , int> > mem;
//vector< set< pair<int,int> > > moles;

int f(int cx, int cy, int t) {
    if (t == 10)
        return 0;
    /*
    int lower = D*10 - (10-t)*D;
    int upper = N-D*10 + (10-t)*D;
    if (!(lower <= cx && cx < upper) || !(lower <= cy && cy < upper))
        return 0;
    */
    //mem[t].insert(make_pair(make_pair(cx, cy), -1));
    //int& res = mem[t][make_pair(cx, cy)];
    int res = mem[t][cx][cy];
    if (res < 0) {
        for(int dx = -D; dx <= D; dx++) {
            for(int dy = -D; dy <= D; dy++) {
                if (dx*dx + dy*dy <= D*D) {
                    int ex = cx + dx;
                    int ey = cy + dy;
                    if (0 <= ex && ex < N && 0 <= ey && ey < N) {
                        int g = gcd(iabs(dx), iabs(dy));
                        int c = 0;
                        if (g == 0) {
                            //if (moles[t].count(make_pair(cx, cy)) > 0)
                            if (moles[t][cx][cy])
                                c++;
                        }
                        else {
                            int sx = dx / g;
                            int sy = dy / g;
                            for(int i = 0; i <= g; i++)
                                //if (moles[t].count(make_pair(cx+sx*i, cy+sy*i)) > 0)
                                if (moles[t][cx+sx*i][cy+sy*i])
                                    c++;
                        }
                        res >?= c + f(ex, ey, t+1);
                    }
                }
            }
        }
    }
    mem[t][cx][cy] = res;
    return res;
}

int main() {

    //while(cin >> N >> D >> M && N > 0) {
    while(scanf("%d%d%d", &N, &D, &M) > 0 && N > 0) {

        N += D*2;

        //mem.clear();
        //moles.clear();
        //mem.resize(10);
        //moles.resize(10);
        REP(t, 10) REP(x, N) REP(y, N)
            mem[t][x][y] = -1,
            moles[t][x][y] = false;

        REP(i, M) {
            int x, y, t;
            //cin >> x >> y >> t;
            scanf("%d%d%d", &x, &y, &t);
            t--;
            x += D;
            y += D;
            moles[t][x][y] = true;
            //moles[t].insert(make_pair(x, y));
        }

        int res = 0;
        //for(int x = -D; x < N+D; x++)
            //for(int y = -D; y < N+D; y++)
        REP(x, N) REP(y, N)
            res >?= f(x, y, 0);

        //cout << res << endl;
        printf("%d\n", res);

    }

    return 0;
}
