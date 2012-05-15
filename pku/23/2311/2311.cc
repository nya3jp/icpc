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

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define N 200

int nimber[N+1][N+1];

int main() {

    for(int i = 2; i <= N; i++) {
        for(int j = 2; j <= N; j++) {
            if (i <= 3 && j <= 3) {
                nimber[i][j] = 0;
            }
            else {
                bool u[10] = {};
                for(int di = 2; i-di >= 2; di++) {
                    int x = nimber[di][j] ^ nimber[i-di][j];
                    //s.insert(x);
                    u[x] = true;
                }
                for(int dj = 2; j-dj >= 2; dj++) {
                    int x = nimber[i][dj] ^ nimber[i][j-dj];
                    //s.insert(x);
                    u[x] = true;
                }
                /*
                vector<int> nexts(ALLOF(s));
                int nim = 0;
                while(nim < (int)nexts.size() && nexts[nim] == nim)
                    nim++;
                */
                int nim = 0;
                while(u[nim])
                    nim++;
                nimber[i][j] = nim;
            }
        }
    }

    for(;;) {
        int w, h;
        cin >> w >> h;
        if (!cin)
            break;

        cout << (nimber[w][h] ? "WIN" : "LOSE") << endl;
    }

    return 0;
}

