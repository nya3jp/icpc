#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <deque>
#include <cctype>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

int main() {

    int n;
    while(cin >> n && n > 0) {

        vector<int> needs(n+1);
        REP(i, n+1)
            cin >> needs[i];

        int th = 0;
        REP(i, n)
            th >?= needs[i];

        int res = (th+50-1)/50;

        for(;;) {
            vector<int> v(n);
            REP(i, n)
                v[i] = 50*res-needs[i];

            int gray = 0;
            while(sort(ALLOF(v), greater<int>()), v[2] > 0) {
                REP(i, 3)
                    v[i]--;
                gray++;
            }

            //printf("%d makes %d\n", res, gray);

            if (gray >= needs[n])
                break;
            res++;
        }

        cout << res << endl;

    }



    return 0;
}
