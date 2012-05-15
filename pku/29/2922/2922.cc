#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <limits>
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

#define N 100
#define H 200

const int INF = numeric_limits<int>::max();

int field[N+2][N+2];
int dp[N+2][N+2][H+1];
bool visited[N+2][N+2][H+1];
const int adj[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

struct P {
    int i, j, h;
};
bool operator<(const P& a, const P& b) {
    return false;
}

template<class T>
struct myvector {
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef int size_type;
    T* data;
    int n;
    int capa;
    myvector() : data(new T[2]), n(0), capa(2) {}
    ~myvector() { delete[] data; }
    myvector(const myvector<T>& rhs) : data(new T[rhs.capa]), n(rhs.n), capa(rhs.capa) {
        copy(rhs.data, rhs.data+n, data);
    }
    myvector& operator=(const myvector<T>& rhs) {
        myvector cp(rhs);
        swap(data, cp.data);
        swap(n, cp.n);
        swap(capa, cp.capa);
    }
    inline bool empty() const { return (n == 0); }
    inline void clear() { n = 0; }
    inline T* begin() { return data; }
    inline T* end() { return data+n; }
    inline T& front() { return *data; }
    inline const T& front() const { return *data; }
    inline void push_back(const T& value) {
        if (n+1 > capa) {
            capa *= 2;
            T* newdata = new T[capa];
            copy(data, data+n, newdata);
            delete[] data;
            data = newdata;
        }
        data[n++] = value;
    }
    inline void pop_back() {
        n--;
    }

};

void solve() {
    int n;
    cin >> n;

    REP(i, n+2) REP(j, n+2)
        field[i][j] = INF;

    REP(i, n) REP(j, n) {
        int h;
        scanf("%d", &h);
        field[i+1][j+1] = h;
    }
    n += 2;

    REP(i, n) REP(j, n) REP(h, H+1)
        dp[i][j][h] = -1;
    REP(i, n) REP(h, H+1)
        dp[i][0][h] = dp[i][n-1][h] = dp[0][i][h] = dp[n-1][i][h] = INF;

    typedef pair<int, P> K;
    priority_queue<K, myvector<K>, greater<K> > q;
    q.push(K(field[1][1], (P){1, 1, field[1][1]}));

    while(!q.empty()) {
        P here = q.top().second;
        int high = q.top().first;
        //printf("(%d,%d) %d-%d\n", here.i, here.j, here.h, high);
        q.pop();
        if (dp[here.i][here.j][here.h] < 0) {
            dp[here.i][here.j][here.h] = high;
            REP(dir, 4) {
                P there = {here.i+adj[dir][0], here.j+adj[dir][1], here.h};
                there.h <?= field[there.i][there.j];
                if (dp[there.i][there.j][there.h] < 0)
                    q.push(K(max(high, field[there.i][there.j]), there));
            }
        }
    }

    int res = INF;
    REP(h, H+1) {
        if (dp[n-2][n-2][h] >= 0) {
            //printf("%d-%d\n", h, dp[n-2][n-2][h]);
            res <?= dp[n-2][n-2][h] - h;
        }
    }

    cout << res << endl;
}

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        cout << "Scenario #" << iCase+1 << ":" << endl;
        solve();
        cout << endl;
    }

    return 0;
}
