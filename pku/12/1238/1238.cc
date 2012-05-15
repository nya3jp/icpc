#include <iostream>
#include <queue>
#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) (c).begin(), (c).end()


int main() {

    for(;;) {

        int n;
        cin >> n;

        if (!cin)
            break;

        vector< vector<double> > g(n, vector<double>(n, 1.0));

        REP(i, n) REP(j, n) {
            if (i == j)
                continue;
            double x;
            cin >> x;
            g[i][j] = x;
        }

        vector< vector< vector<double> > > gain(n+1, vector< vector<double> >(n, vector<double>(n, 0.0)));
        vector< vector< vector<int> > > trace(n+1, vector< vector<int> >(n, vector<int>(n, -1)));

        REP(i, n)
            gain[0][i][i] = 1.0;

        REP(t, n) REP(s, n) REP(a, n) REP(b, n) {
            double x = gain[t][s][a] * g[a][b];
            if (x > gain[t+1][s][b]) {
                gain[t+1][s][b] = x;
                trace[t+1][s][b] = a;
            }
        }

        int min_t = -1, min_s;
        REP(t, n+1) REP(s, n) {
            if (gain[t][s][s] > 1.01) {
                min_t = t;
                min_s = s;
                goto FOUND;
            }
        }
    FOUND:
        if (min_t < 0) {
            cout << "no arbitrage sequence exists" << endl;
        }
        else {
            int here = min_s;
            vector<int> res(1, here);
            for(int t = min_t; t > 0; t--) {
                here = trace[t][min_s][here];
                res.push_back(here);
            }
            reverse(ALLOF(res));
            REP(i, res.size())
                cout << " " << res[i]+1;
            cout << endl;
        }
        

    }

    return 0;
}
