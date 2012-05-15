#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

typedef unsigned long long int integer;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define EPS 1.0e-8

#define N 100

map<vector<int>, double> mem;
int n;

double solve(const vector<int>& v) {
    if (v.size() == 1)
        return 0;
    if (mem.count(v) > 0)
        return mem[v];

    double res = 1.0;

    int m = v.size();
    int p = n*(n-1)/2;
    int d = p;

    REP(i, m) REP(j, m) if (i < j) {
        vector<int> u;
        for(int k = 0; k < i; k++)
            u.push_back(v[k]);
        for(int k = i+1; k < j; k++)
            u.push_back(v[k]);
        for(int k = j+1; k < m; k++)
            u.push_back(v[k]);
        u.push_back(v[i]+v[j]);
        sort(u.begin(), u.end());
        res += solve(u) * v[i]*v[j] / p;
        d -= v[i]*v[j];
    }
    //printf("%d %d\n", d, p);
    res = res*p/(p-d);

    /*
    REP(i, m) {
        printf("%d ", v[i]);
    }
    printf("= %.6f\n", res);
    */

    mem[v] = res;
    return res;
}


bool g[30][30];

int dfs(int here, vector<bool>& visited) {
    if (visited[here])
        return 0;
    visited[here] = true;
    int res = 1;
    REP(there, n)
        if (g[here][there])
            res += dfs(there, visited);
    return res;
}

int main() {

    freopen("interconnect.in", "r", stdin);

    //vector<int> v(30, 1);
    //solve(v);

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        int m;
        cin >> n >> m;

        REP(i, n) REP(j, n)
            g[i][j] = false;

        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            g[a][b] = true;
            g[b][a] = true;
        }

        vector<bool> visited(n, false);
        vector<int> v;
        REP(i, n)
            if (!visited[i])
                v.push_back(dfs(i, visited));

        sort(v.begin(), v.end());
        printf("%.6f\n", solve(v));
    }

    return 0;
}
