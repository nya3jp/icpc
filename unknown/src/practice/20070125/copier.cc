#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <deque>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main() {

    double w, h, W, H;
    while(cin >> w >> h >> W >> H && !(w == 0 && h == 0 && W == 0 && H == 0)) {

        if (w < h)
            swap(w, h);
        if (W < H)
            swap(W, H);

        int r = (int)floor(100*min(1.0, min(W/w, H/h)));
        printf("%d%%\n", r);

    }

    return 0;
}
