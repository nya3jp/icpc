#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cstdio>
#include <cmath>
#include <complex>
#include <cctype>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 12

inline bool at(int bits, int k) {
    return ((bits & (1<<k)) != 0);
}

#define FOR_SUBSET(i,s) for(int i = s&-s; i != 0; i = (((i|~s)+1)&s))

int main() {

    int n, m;
    while(cin >> n >> m && !(n < 0 && m < 0)) {

        vector<string> classes(n);
        map<string,int> ids;
        REP(i, n) {
            cin >> classes[i];
            ids[classes[i]] = i;
        }

        vector<int> opens(n, 0);
        vector<int> depends(n, 0);

        REP(i, n) {
            string name, open;
            cin >> name >> open;
            int id = ids[name];
            if (open == "F") opens[id] = 1;
            else if (open == "S") opens[id] = 2;
            else if (open == "B") opens[id] = 3;
            int nDepends;
            cin >> nDepends;
            REP(j, nDepends) {
                string depend;
                cin >> depend;
                depends[id] |= 1 << ids[depend];
            }
        }

        REP(j, n) REP(i, n) REP(k, n)
            if (at(depends[i], j) && at(depends[j], k))
                depends[i] |= 1<<k;

        bool dp[2][1<<N];

        REP(i, 1<<n)
            dp[0][i] = false;
        dp[0][0] = true;

        int season;
        int semester = 0;
        for(season = 0; !dp[season][(1<<n)-1]; season^=1, semester++) {
            REP(i, 1<<n)
                dp[season^1][i] = dp[season][i];

            REP(i, 1<<n) FOR_SUBSET(j, i) if (__builtin_popcount(j) <= m) {
                int dep = 0;
                REP(k, n) if (at(j, k)) {
                    dep |= depends[k];
                    if ((opens[k] & (season+1)) == 0)
                        dep |= 0x1000000;
                }
                if (((i^j)&dep) == dep && dp[season][i^j])
                    dp[season^1][i] = true;
            }

        }

        /*
        REP(i, 1<<n) {
            if (dp[season][i]) {
                REP(j, n)
                    if (at(i, j))
                        cout << classes[j] << ' ';
                cout << "can be done" << endl;
            }
        }
        */

        printf("The minimum number of semesters required to graduate is %d.\n", semester);

    }

    return 0;
}
