#include <iostream>
#include <fstream>
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

#define REP(i,n) for(int i = 0 ; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))


int MOVES[6][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
    {1, -1},
    {-1, 1},
};

int main() {

    typedef pair<int,int> place;
    map<place, int> table;
    table[make_pair(0, 0)] = 1;
    vector<int> res(1, 1);

    REP(k, 14) {
        map<place,int> newtable;
        FOR(it, table) REP(i, 6)
            newtable[make_pair(it->first.first+MOVES[i][0], it->first.second+MOVES[i][1])] += it->second;
        table = newtable;
        res.push_back(table[make_pair(0, 0)]);
    }

    int n;
    cin >> n;
    REP(i, n) {
        int a;
        cin >> a;
        cout << res[a] << endl;
    }

    return 0;
}


