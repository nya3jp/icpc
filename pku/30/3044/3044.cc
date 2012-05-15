#include <iostream>
#include <algorithm>

using namespace std;

int v[50000+1];

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main() {
    int n, w;
    cin >> n >> w;

    int res = 0;
    int m = 1;
    v[0] = 0;
    REP(i, n) {
        int x, y;
        cin >> x >> y;
        int p = lower_bound(v, v+m, y) - v;
        if (p == m || v[p] != y) {
            //printf("(%d,%d)\n", x, y);
            v[p] = y;
            res++;
        }
        m = p+1;
    }

    cout << res << endl;

    return 0;
}
