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


struct Cow {
    int score, aid;
};

bool by_score(const Cow& a, const Cow& b) {
    return (a.score < b.score);
}

template<typename I1, typename I2>
void go(I1 cows, I2 aids, int nHalf, int nCows) {
    priority_queue<int> q;
    int sum = 0;
    REP(i, nHalf) {
        q.push(cows[i].aid);
        sum += cows[i].aid;
    }
    for(int i = nHalf; i < nCows; i++) {
        aids[i] = sum;
        q.push(cows[i].aid);
        sum += cows[i].aid;
        sum -= q.top();
        q.pop();
    }
}

int main() {

    int nAdmits, nCows, fund;
    scanf("%d%d%d", &nAdmits, &nCows, &fund);

    int nHalf = nAdmits / 2;

    vector<Cow> cows(nCows);
    REP(i, nCows) {
        Cow& c = cows[i];
        scanf("%d%d", &c.score, &c.aid);
    }

    sort(ALLOF(cows), by_score);

    vector<int> formerAids(nCows), latterAids(nCows);
    go(cows.begin(), formerAids.begin(), nHalf, nCows);
    go(cows.rbegin(), latterAids.rbegin(), nHalf, nCows);

    int res = -1;
    for(int i = nHalf; i+nHalf < nCows; i++)
        if (cows[i].aid + formerAids[i] + latterAids[i] <= fund)
            res >?= cows[i].score;

    printf("%d\n", res);

    return 0;
}
