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

typedef complex<int> P;
namespace std {
    bool operator<(const P& a, const P& b) {
        return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
    }
}

bool augment(const vector< vector<bool> >& adj, vector<int>& back, int left, vector<bool>& visited) {
    int n = adj.size(), m = adj[0].size();

    if (left < 0)
        return true;
    if (visited[left])
        return false;
    visited[left] = true;

    REP(right, m) {
        if (adj[left][right] && augment(adj, back, back[right], visited)) {
            back[right] = left;
            return true;
        }
    }

    return false;
}

int max_match(vector< vector<bool> > adj) {
    if (adj.empty())
        return 0;
    int n = adj.size(), m = adj[0].size();

    vector<int> back(m, -1);

    int res = 0;
    REP(i, n) {
        vector<bool> visited(n, false);
        if (augment(adj, back, i, visited))
            res++;
    }

    return res;
}

int main() {

    // May fate be with you!

    int h, w;
    cin >> h >> w;

    set<P> field;
    REP(i, h) {
        string line;
        cin >> line;
        REP(j, w) if (line[j] == '*')
            field.insert(P(i, j));
    }

    map<P, P> toleft, toup;

    REP(i, h) REP(j, w) {
        P here(i, j);
        P left(i-1, j);
        P up(i, j-1);
        if (field.count(here) > 0) {
            if (field.count(left) > 0)
                toleft[here] = toleft[left];
            else
                toleft[here] = here;
            if (field.count(up) > 0)
                toup[here] = toup[up];
            else
                toup[here] = here;
        }
    }

    map<P, int> u, v;
    FOR(it, toleft) {
        P here = it->second;
        if (u.count(here) == 0)
            u.insert(make_pair(here, (int)u.size()));
    }
    FOR(it, toup) {
        P here = it->second;
        if (v.count(here) == 0)
            v.insert(make_pair(here, (int)v.size()));
    }

    /*
    cout << "u:" << endl;
    FOR(it, u)
        cout << it->first << endl;
    cout << "v:" << endl;
    FOR(it, v)
        cout << it->first << endl;
    */

    int n = u.size(), m = v.size();

    vector< vector<bool> > adj(n, m);

    FOR(it, field) {
        P here = *it;
        adj[u[toleft[here]]][v[toup[here]]] = true;
    }

    cout << max_match(adj) << endl;

    return 0;
}



// Powered by fate testarossa
