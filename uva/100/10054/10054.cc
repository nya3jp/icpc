#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


#define N 50
#define M 1000

int adj[N][N];


void solve(int here, int*& res) {
    REP(next, N) {
        while(adj[here][next] > 0) {
            adj[here][next]--;
            adj[next][here]--;
            solve(next, res);
            *res++ = here;
        }
    }
}


int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        if (iCase > 0)
            cout << endl;
        cout << "Case #" << iCase+1 << endl;

        int m;
        cin >> m;

        REP(i, N) REP(j, N)
            adj[i][j] = 0;

        int degrees[N];
        REP(i, N)
            degrees[i] = 0;

        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            adj[a][b]++;
            adj[b][a]++;
            degrees[a]++;
            degrees[b]++;
        }

        bool ok = true;
        REP(i, N)
            if (degrees[i] % 2 == 1)
                ok = false;

        if (!ok) {
            cout << "some beads may be lost" << endl;
        }
        else {
            int res[M];
            int* p = res;
            solve(max_element(degrees, degrees+N) - degrees, p);
            REP(i, m) {
                int j = (i+1)%m;
                cout << res[i]+1 << " " << res[j]+1 << endl;
            }
        }

    }

    return 0;
}
