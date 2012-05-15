#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "balloons"


int bitquery(int* bit, int n, int to) {
    int res = 0;
    for(int k = to-1; k >= 0; k = (k & (k+1)) - 1)
        res += bit[k];
    return res;
}

void bitupdate(int* bit, int n, int pos, int delta) {
    while(pos < n) {
        bit[pos] += delta;
        pos |= pos+1;
    }
}

int bitbinsearch_left(int* bit, int n, int a) {
    int lo = 0, hi = n;
    while(lo < hi) {
        int mid = (lo+hi)/2;
        if (bitquery(bit, n, mid+1) > a)
            lo = mid+1;
        else
            hi = mid;
    }
    return lo;
}

pair<int,int> bitbinsearch(int* bit, int n, int a) {
    return make_pair(bitbinsearch_left(bit, n, a), bitbinsearch_left(bit, n, a-1));
}


int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    int n, m;
    scanf("%d%d", &n, &m);

    int w[n];
    REP(i, n)
        scanf("%d", &w[i]);
    sort(w, w+n, greater<int>());

    int bit[n];
    memset(bit, 0, sizeof(int)*n);

    bitupdate(bit, n, 0, w[0]);
    for(int i = 1; i < n; i++)
        bitupdate(bit, n, i, w[i]-w[i-1]);

    REP(j, m) {
        /*
        REP(i, n)
            cerr << bitquery(bit, n, i+1) << " ";
        cerr << endl;
        */
        int k;
        scanf("%d", &k);
        if (k > n) {
            puts("NO");
            return 0;
        }
        int last = bitquery(bit, n, k);
        if (last == 0) {
            puts("NO");
            return 0;
        }
        pair<int,int> range = bitbinsearch(bit, n, last);
        bitupdate(bit, n, 0, -1);
        bitupdate(bit, n, range.first, 1);
        bitupdate(bit, n, range.second-(k-range.first), -1);
        bitupdate(bit, n, range.second, 1);
    }
    puts("YES");

    return 0;
}



