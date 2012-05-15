#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

struct P {
    int x, y, z;
};
P operator-(const P& a, const P& b) {
    return (P){a.x-b.x, a.y-b.y, a.z-b.z};
}
int norm(const P& a) {
    return a.x*a.x + a.y*a.y + a.z*a.z;
}

const int INF = INT_MAX;

typedef vector<int> Edges;
typedef vector<Edges> Graph;

int main() {

    int n;
    while(cin >> n && n > 0) {

        vector<P> points(n);
        vector<int> ids(n);
        REP(i, n) {
            P& p = points[i];
            cin >> ids[i] >> p.x >> p.y >> p.z;
        }

        Graph g(n);

        for(int iConnect = 1; iConnect < n; iConnect++) {

            int iRoot = 0;
            for(int i = 1; i < iConnect; i++) {
                /*
                int di = norm(points[i]-points[iConnect]);
                cout << i << "-" << iConnect << " = " << di << endl;
                */
                if (norm(points[i]-points[iConnect]) < norm(points[iRoot]-points[iConnect]))
                    iRoot = i;
            }

            g[iRoot].push_back(iConnect);
            g[iConnect].push_back(iRoot);

        }

        /*
        REP(i, n) {
            Edges& e = g[i];
            cout << i << ":";
            REP(j, e.size())
                cout << ' ' << e[j];
            cout << endl;
        }
        */

        vector<int> radius(n, 0);
        REP(iStart, n) {
            vector<int> dists(n, INF);
            queue<int> q;
            q.push(iStart);
            dists[iStart] = 0;
            while(!q.empty()) {
                int here = q.front();
                q.pop();
                Edges& edges = g[here];
                REP(i, edges.size()) {
                    int there = edges[i];
                    if (dists[there] == INF) {
                        // not visited
                        dists[there] = dists[here]+1;
                        q.push(there);
                    }
                }
            }
            /*
            cout << "dists(" << iStart << ") = ";
            REP(i, n)
                cout << dists[i] << ',';
            cout << endl;
            */
            REP(i, n)
                radius[i] >?= dists[i];
        }

        int r = *min_element(ALLOF(radius));
        vector<int> res;

        REP(i, n)
            if (radius[i] == r)
                res.push_back(ids[i]);

        sort(ALLOF(res));

        if (res.size() == 1) {
            cout << res[0] << endl;
        }
        else {
            cout << res[0] << ' ' << res[1] << endl;
        }

    }

    return 0;
}
