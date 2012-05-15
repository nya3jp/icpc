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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

#define N 200

char colors[N];
int lengths[N];
int n;
int threshold;

int dp[N][N+1];

const int INF = numeric_limits<int>::max();

inline int cost(int k) {
    return max(threshold-k, 0);
}

int main() {
    string s;
    while(cin >> threshold >> s) {
        n = 0;
        s.push_back('!');
        while(s.size() > 1) {
            char c = s[0];
            int len = s.find_first_not_of(c);
            colors[n] = c;
            lengths[n] = len;
            n++;
            s = s.substr(len);
        }

        REP(i, n) REP(j, n+1)
            dp[i][j] = -12345;
        REP(i, n)
            dp[i][0] = 0;
        REP(i, n)
            dp[i][1] = max(threshold-lengths[i], 0);
        for(int len = 2; len <= n; len++) {
            for(int from = 0; from+len <= n; from++) {
                int to = from+len;
                int& res = dp[from][len];
                res = cost(lengths[from]) + dp[from+1][len-1];
                if (colors[from] == colors[to-1] && lengths[from]+lengths[to-1] >= threshold)
                    res <?= dp[from+1][len-2];
                int band
                for(int mid = from+2; mid < to; mid++) {
                    res <?= dp[from][mid-from] + dp[mid][to-mid];
                }
            }
        }
        REP(i, n) REP(j, n+1-i)
            printf("(%d,%d) = %d\n", i, j, dp[i][j]);
        cout << dp[0][n] << endl;
    }
    return 0;
}
