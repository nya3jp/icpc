#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 100

bool ls[N][N];
bool gr[N][N];

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n, m;
        cin >> n >> m;

        REP(i, n) REP(j, n)
            ls[i][j] = gr[i][j] = false;

        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            ls[a][b] = gr[b][a] = true;
        }

        REP(j, n) REP(i, n)
            if (ls[i][j])
                REP(k, n)
                    if (ls[j][k])
                        ls[i][k] = true;
        REP(j, n) REP(i, n)
            if (gr[i][j])
                REP(k, n)
                    if (gr[j][k])
                        gr[i][k] = true;

        int res = 0;
        REP(i, n)
            if (count(ls[i], ls[i]+n, true) > n/2 || count(gr[i], gr[i]+n, true) > n/2)
                res++;

        cout << res << endl;

    }

    return 0;
}
