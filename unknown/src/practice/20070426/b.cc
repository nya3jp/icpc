#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

typedef vector<int> Edges;
typedef map<int, Edges> Graph;

/*
void solve(pair<int,int>* v, int n, int total) {
    int res = numeric_limits<int>::max();
    int left = 0, right = 1;
    for(;;) {
#define value (v[right].first - v[left].first)
        while(value <= total && right < n) {
            right++;
        }
        while(value >= total) {
            left++;
        }
    }
}
*/

void solve(pair<int,int>* v, int n, int total) {
    int min_delta = numeric_limits<int>::max();
    int min_sum;
    int left, right;

    /*
    REP(i, n) {
        cout << v[i].first << "\t" << v[i].second << endl;
    }
    */

    REP(i, n) {
        int value = abs(v[i].first);
        if (abs(total-value) < min_delta) {
            min_sum = value;
            min_delta = abs(total-value);
            left = 0;
            right = v[i].second;
        }
    }

    REP(i, n) {
        int here = v[i].first;
        int there = here + total;
        int pos = lower_bound(v+i+1, v+n, make_pair(there, -1)) - v;
        if (i < pos && pos < n) {
            int value = v[pos].first - here;
            if (abs(total-value) < min_delta) {
                min_sum = value;
                min_delta = abs(total-value);
                left = (v[i].second<?v[pos].second)+1;
                right = (v[i].second>?v[pos].second);
            }
        }
        pos++;
        if (i < pos && pos < n) {
            int value = v[pos].first - here;
            if (abs(total-value) < min_delta) {
                min_sum = value;
                min_delta = abs(total-value);
                left = (v[i].second<?v[pos].second)+1;
                right = (v[i].second>?v[pos].second);
            }
        }
        pos--; pos--;
        if (i < pos && pos < n) {
            int value = v[pos].first - here;
            if (abs(total-value) < min_delta) {
                min_sum = value;
                min_delta = abs(total-value);
                left = (v[i].second<?v[pos].second)+1;
                right = (v[i].second>?v[pos].second);
            }
        }
    }

    cout << min_sum << " " << (left<?right)+1 << " " << (left>?right)+1 << endl;
}

int main() {

    for(;;) {
        int n, nQueries;
        scanf("%d%d", &n, &nQueries);
        if (n == 0 && nQueries == 0)
            break;

        pair<int,int>* v = new pair<int,int>[n];
        REP(i, n) {
            scanf("%d", &v[i].first);
            v[i].second = i;
        }

        for(int i = 1; i < n; i++) {
            v[i].first += v[i-1].first;
        }

        sort(v, v+n);

        REP(iQuery, nQueries) {

            int total;
            scanf("%d", &total);
            solve(v, n, total);

        }

        delete[] v;
    }

    return 0;
}
