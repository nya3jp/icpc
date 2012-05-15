#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

struct Line {
    double a, b, c;
};
typedef complex<double> P;

inline int sgn(double x) {
    return (x > 0 ? 1 : -1);
}

void solve(int iCase = 0) {
    int nRoads;
    cin >> nRoads;
    if (nRoads == 0)
        return;

    vector<Line> roads(nRoads);
    REP(i, nRoads) {
        Line& x = roads[i];
        cin >> x.a >> x.b >> x.c;
    }

    int nNodes;
    cin >> nNodes;

    vector<P> nodes(nNodes);
    REP(i, nNodes) {
        double x, y;
        cin >> x >> y;
        nodes[i] = P(x, y);
    }

    int res = 0;
    REP(iNode, nNodes) {
        double x = nodes[iNode].real();
        double y = nodes[iNode].imag();
        int pos = 0, neg = 0;
        REP(iRoad, nRoads) {
            Line& r = roads[iRoad];
            int s = sgn(r.a*x + r.b*y + r.c);
            if (s > 0)
                pos++;
            else
                neg++;
        }
        res += pos*(pos-1)/2;
        res += neg*(neg-1)/2;
        
    }

    cout << "Roadmap " << iCase+1 << ":" << endl
         << "Negative Builders Ltd. will build " << res << " New Roads." << endl;

    solve(iCase+1);
}

int main() {
    solve();
    return 0;
}
