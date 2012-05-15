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

#define PROBLEMS 300

int n;
int money;

int problems[PROBLEMS][2];
int owes[PROBLEMS+1];
int memo[PROBLEMS+1][PROBLEMS+1];
const int INF = 12345;

int search(int finished, int owed) {
    int& res = memo[finished][owed];
    if (res < 0) {
        res = INF;
        int after = owes[finished] - owes[owed];
        int rest = money - after;
        if (rest >= 0) {
            if (finished == n) {
                res = 2;
            }
            else {
                if (finished != owed)
                    res <?= 1 + search(finished, finished);
                int before = 0;
                for(int next = finished+1; next <= n; next++) {
                    before += problems[next-1][0];
                    if (before <= rest)
                        res = min(res, 1 + search(next, finished));
                }
            }
        }
    }
    return res;
}

int main() {

    cin >> money >> n;

    REP(i, n)
        cin >> problems[i][0] >> problems[i][1];

    owes[0] = 0;
    REP(i, n)
        owes[i+1] = owes[i] + problems[i][1];

    memset(memo, -1, sizeof(memo));
    cout << search(0, 0) << endl;

    return 0;
}
