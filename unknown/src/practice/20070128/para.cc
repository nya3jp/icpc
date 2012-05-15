#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()


typedef pair<int,int> P;

#define INF 0x7fffffff

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int res = 0;

        int n;
        cin >> n;

        vector<P> points;
        REP(i, n) {
            int x, y;
            cin >> x >> y;
            points.push_back(P(x, y));
        }
        sort(ALLOF(points));

        int m = n*(n-1)/2;

        vector<P> vectors;
        vectors.reserve(m);
        REP(i, n) REP(j, n) if (i < j) {
            P d = P(points[i].first-points[j].first, points[i].second-points[j].second);
            P ops = P(2*points[i].first-points[j].first, 2*points[i].second-points[j].second);
            if (binary_search(ALLOF(points), ops))
                res--;
            vectors.push_back(d);
        }
        assert(vectors.size() == m);

        sort(ALLOF(vectors));

        vectors.push_back(P(INF,INF));
        for(int from = 0; from < m; ) {
            int to = from+1;
            while(vectors[to] == vectors[from])
                to++;
            res += (to-from)*(to-from-1)/2;
            from = to;
        }

        cout << res/2 << endl;

    }

    return 0;
}

