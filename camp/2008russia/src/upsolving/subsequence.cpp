#include <iostream>
#include <vector>
#include <complex>
#include <map>
#include <set>
#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "subsequence"

int n;
int seq[64];

long long memo[64];

long long go(int pos) {
    long long& res = memo[pos];
    if (res == 0) {
        res = 1;
        set<int> s;
        for(int next = pos+1; next < n; next++) {
            if (seq[next] > seq[pos] && s.insert(seq[next]).second)
                res += go(next);
        }
    }
    return res;
}

int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    long long index;
    cin >> n >> index;
    index--;

    REP(i, n)
        cin >> seq[i];

    vector< pair<int, int> > order;
    REP(i, n)
        order.push_back(make_pair(seq[i], i));
    sort(ALLOF(order));

    vector<int> res;
    set<int> used;
    int pos = -1;
    REP(i, n) {
        if (order[i].second <= pos)
            continue;
        if (!used.insert(order[i].first).second)
            continue;
        long long lo = go(order[i].second);
        //fprintf(stderr, "index=%lld, go(%d) = %lld\n", index, order[i].second, lo);
        if (index >= lo) {
            index -= lo;
        }
        else {
            res.push_back(order[i].first);
            if (index == 0)
                break;
            index--;
            pos = order[i].second;
        }
    }

    assert(index == 0);

    cout << res.size() << endl;
    REP(i, res.size()) {
        if (i > 0)
            cout << " ";
        cout << res[i];
    }
    cout << endl;

    return 0;
}

