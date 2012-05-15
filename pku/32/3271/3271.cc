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

const int ADJ[8][2] = {
    {+2,+1},
    {+1,+2},
    {-1,+2},
    {-2,+1},
    {-2,-1},
    {-1,-2},
    {+1,-2},
    {+2,-1},
};
char field[34][34];
int h, w;
int si, sj, ti, tj;

typedef pair<int,int> P;
typedef pair<int,P> K;
map<P, int> dists;

int dijkstra() {
    priority_queue<K, vector<K>, greater<K> > q;
    q.push(K(0, P(si, sj)));
    while(!q.empty()) {
        K top = q.top();
        q.pop();
        int d = top.first;
        P here = top.second;
        if (dists.insert(make_pair(here, d)).second) {
            REP(dir, 8) {
                P there(here.first+ADJ[dir][0], here.second+ADJ[dir][1]);
                char c = field[there.first][there.second];
                if (c == 'X')
                    continue;
                q.push(K(d+(c == '.' ? 1 : 0), there));
            }
        }
    }
    if (dists.count(P(ti, tj)) == 0)
        return -1;
    return dists[P(ti, tj)];
}

map<P, long long> memo;

long long combi(P start) {
    if (memo.count(start) > 0)
        return memo[start];

    long long res = 0;

    int dstart = dists[start];
    int dnext = dstart+1;
    int dgoal = dists[P(ti, tj)];

    if (dstart == dgoal)
        dnext = -1;

    queue<P> q;
    set<P> visited;
    q.push(start);
    visited.insert(start);

    while(!q.empty()) {
        P here = q.front();
        q.pop();
        if (here == P(ti, tj)) {
            res += 1;
        }
        REP(dir, 8) {
            P there(here.first+ADJ[dir][0], here.second+ADJ[dir][1]);
            char c = field[there.first][there.second];
            if (c == '.') {
                assert(dists.count(there) > 0);
                if (dists[there] == dnext)
                    if (visited.insert(there).second)
                        res += combi(there);
            }
            else if (c == '#') {
                assert(dists.count(there) > 0);
                if (visited.insert(there).second)
                    q.push(there);
            }
        }
    }
    
    return memo[start] = res;
}

long long combi() {
    return combi(P(si, sj));
}

int main() {

    memset(field, 'X', sizeof(field));

    cin >> h >> w;

    REP(i, h) REP(j, w) {
        int t;
        cin >> t;
        field[i+2][j+2] = ".#X##"[t];
        if (t == 3)
            si = i+2, sj = j+2;
        if (t == 4)
            ti = i+2, tj = j+2;
    }

    h += 4; w += 4;

    int d = dijkstra();
    cout << d << endl;
    if (d >= 0)
        cout << combi() << endl;

    /*
    for(int i = 2; i < h-2; i++) {
        for(int j = 2; j < w-2; j++) {
            P p(i, j);
            if (dists.count(p))
                cout << dists[p] << " ";
            else
                cout << "X ";
        }
        cout << endl;
    }
    //*/

    return 0;
}
