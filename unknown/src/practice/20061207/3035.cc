#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

#define TOSSES 100
#define N 10

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

double g_table1[1<<N];
double g_table2[1<<N];

bool solve() {
    int nTosses, n, m;
    cin >> nTosses >> n >> m;
    if (nTosses == 0 && n == 0 && m == 0)
        return false;

    vector< vector<int> > g(1<<n);
    REP(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    double *t1 = g_table1;
    double *t2 = g_table2;

    bool ok = true;

    REP(i, 1<<n)
        t1[i] = 1.0 / (1<<n);

    for(int r = 1; r < nTosses; r++) {
        REP(i, 1<<n)
            t2[i] = 0;
        REP(i, 1<<n) {
            int k = g[i].size();
            REP(j, k)
                t2[g[i][j]] += t1[i] / k;
        }

        double res[N];
        REP(j, n)
            res[j] = 0;
        REP(i, 1<<n) REP(j, n)
            if ((i&(1<<j)) != 0)
                res[j] += t2[i];
        REP(j, n) {
            if (abs(res[j]-0.5) >= 0.25-1.0e-8)
                ok = false;
        }
        
        swap(t1, t2);
    }

    cout << (ok ? "Yes" : "No") << endl;

    return true;
}

int main() {

    while(solve())
        ;

    return 0;
}
