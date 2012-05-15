#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) (c).begin(), (c).end()

typedef pair<int,int> P;

P swap_xy(P p) {
    return P(p.second, p.first);
}
bool contains(vector<int> v, int t) {
    return (count(ALLOF(v), t) > 0);
}

vector< vector<int> > unify(vector< vector<P> >& pieces) {
    int nTypes = pieces.size();

    vector< pair<pair<int,int>, int> > ranges(nTypes);
    REP(iType, nTypes)
        ranges[iType] = make_pair(
            make_pair(min_element(ALLOF(pieces[iType]))->first,
                      max_element(ALLOF(pieces[iType]))->first)
            , iType);

    sort(ALLOF(ranges));

    vector< vector<int> > components;
    int last_x = -1;
    FOR(it, ranges) {
        int from = it->first.first;
        int to = it->first.second;
        if (last_x < from)
            components.push_back(vector<int>());
        last_x >?= to;
        components.back().push_back(it->second);
    }

    return components;
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int nTypes, nPieces;
        cin >> nTypes >> nPieces;

        vector< vector<P> > pieces(nTypes, nPieces);
        REP(i, nTypes) REP(j, nPieces) {
            int x, y;
            cin >> x >> y;
            pieces[i][j] = P(x, y);
        }

        vector< vector<int> > x_set = unify(pieces);
        FOR(it, pieces)
            transform(ALLOF(*it), it->begin(), swap_xy);
        vector< vector<int> > y_set = unify(pieces);

        bool res = true;
        REP(iType, nTypes) {
            vector< vector<int> >::iterator ix = find_if(ALLOF(x_set), bind2nd(ptr_fun(contains), iType));
            vector< vector<int> >::iterator iy = find_if(ALLOF(y_set), bind2nd(ptr_fun(contains), iType));
            FOR(it, *ix) {
                if (*it == iType)
                    continue;
                if (count(ALLOF(*iy), *it) > 0)
                    res = false;
            }
        }

        cout << (res ? "YES" : "NO") << endl;

    }

    return 0;
}
