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

#define N 500

typedef int Weight;
Weight adj[N][N];
int n;

int min_cut() {
    Weight res = numeric_limits<Weight>::max();

    vector<int> v;
    REP(i, n)
        v.push_back(i);

    for(int m = n; m > 1; m--) {
        vector<Weight> ws(m, 0);
        int s, t;
        Weight w;
        REP(k, m) {
            s = t;
            t = max_element(ws.begin(), ws.end()) - ws.begin();
            w = ws[t];
            ws[t] = -1;
            REP(i, m)
                if (ws[i] >= 0)
                    ws[i] += adj[v[t]][v[i]];
        }
        REP(i, m) {
            adj[v[i]][v[s]] += adj[v[i]][v[t]];
            adj[v[s]][v[i]] += adj[v[t]][v[i]];
        }
        v.erase(v.begin()+t);
        res <?= w;
    }
    return res;
}

int main() {
    int m;
    while(scanf("%d%d", &n, &m) == 2) {

        REP(i, n) REP(j, n)
            adj[i][j] = 0;

        REP(i, m) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            adj[a][b] = (adj[b][a] += c);
        }

        printf("%d\n", min_cut());
    }
    
    return 0;
}



// Powered by Fate Testarossa
