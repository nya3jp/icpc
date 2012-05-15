#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

using namespace std;

enum Logic {
    True  = 0,
    False = 1,
    Yet,
};

typedef pair<int, int> interval;

typedef vector<int> Edges;
typedef vector<Edges> Graph;

vector<enum Logic> logics;
vector<bool> visited;
vector<pair<interval, interval> > sched;
Graph g;

int read_time()
{
    char wod[4];
    int hour, minutes;
    scanf(" %[^:]:%d:%d", wod, &hour, &minutes);

    int ret = 0;
    string wods = wod;
    if (wods == "MON") {
        ret += 1 * 24 * 60;
    } else if (wods == "TUE") {
        ret += 2 * 24 * 60;
    } else if (wods == "WED") {
        ret += 3 * 24 * 60;
    } else if (wods == "THU") {
        ret += 4 * 24 * 60;
    } else if (wods == "FRI") {
        ret += 5 * 24 * 60;
    } else if (wods == "SAT") {
        ret += 6 * 24 * 60;
    }

    ret += hour * 60;
    ret += minutes;
    return ret;
}

pair<int, int> read_interval()
{
    int from = read_time();
    int to = read_time();
    return make_pair(from, to);
}

bool dfs(int cur, enum Logic curLogic)
{
    if (logics[cur] == Yet) {
        visited[cur] = true;
        logics[cur] = curLogic;

        int curID = cur * 2 + curLogic;
        REP(iEdge, g[curID].size()) {
            int dst = g[curID][iEdge];
            bool ret = dfs(dst / 2, (enum Logic)((dst & 0x1U) ^ 1));
            if (!ret) {
                return false;
            }
        }
        return true;
    } else if (logics[cur] == curLogic) {
        return true;
    }

    return false;
}

bool dfs2(int cur, enum Logic curLogic)
{
    visited.clear();
    visited.assign(sched.size(), false);

    bool ret = dfs(cur, curLogic);
    if (!ret) {
        REP(i, sched.size()) {
            if (visited[i])
                logics[i] = Yet;
        }
        return false;
    }
    return true;
}

bool is_intersect(interval i1, interval i2)
{
    if (i1.second <= i2.first)
        return false;

    if (i1.first >= i2.second)
        return false;

    return true;
}

void
solve()
{
    // construct graph
    REP(iSched, sched.size()) {
        for(int targetSched = iSched + 1; targetSched < sched.size(); targetSched++) {
            if (is_intersect(sched[iSched].first, sched[targetSched].first)) {
                g[iSched * 2].push_back(targetSched * 2);
                g[targetSched * 2].push_back(iSched * 2);
            }

            if (is_intersect(sched[iSched].second, sched[targetSched].second)) {
                g[iSched * 2 + 1].push_back(targetSched * 2 + 1);
                g[targetSched * 2 + 1].push_back(iSched * 2 + 1);
            }

            if (is_intersect(sched[iSched].first, sched[targetSched].second)) {
                g[iSched * 2].push_back(targetSched * 2 + 1);
                g[targetSched * 2 + 1].push_back(iSched * 2);
            }

            if (is_intersect(sched[iSched].second, sched[targetSched].first)) {
                g[iSched * 2 + 1].push_back(targetSched * 2);
                g[targetSched * 2].push_back(iSched * 2 + 1);
            }
        }
    }

    // solve!
    REP(iSched, sched.size()) {
        if (logics[iSched] == Yet) {
            if (dfs2(iSched, True) == false) {
                if (dfs2(iSched, False) == false) {
                    cout << "NO" << endl;
                    return;
                }
            }
        }
    }
    cout << "YES" << endl;
}

int main(void)
{
    freopen("seminar.in", "r", stdin);
    
    int nCases;
    cin >> nCases;
    while (nCases--) {
        int nPeople;
        cin >> nPeople;

        sched.clear();
        logics.clear();
        REP(iPeople, nPeople) {
            interval i1 = read_interval();
            interval i2 = read_interval();
            sched.push_back(make_pair(i1, i2));
        }
        logics.assign(nPeople, Yet);
        g.clear();
        g.resize(nPeople * 2);

        solve();
    }
}
