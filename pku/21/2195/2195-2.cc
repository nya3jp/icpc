#include <iostream>
#include <algorithm>
#include <map>
#include <memory.h>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <queue>
#include <limits>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef complex<int> P;


#define residue(i,j) (adj[i][j] + ofsleft[i] + ofsright[j])

vector<int> min_cost_match(vector< vector<int> > adj) {
    int n = adj.size();
    int m = adj[0].size();

    vector<int> toright(n, -1), toleft(m, -1);
    vector<int> ofsleft(n, 0), ofsright(m, 0);

    REP(r, n) {
        vector<bool> left(n, false), right(m, false);
        vector<int> trace(m, -1), ptr(m, r);
        left[r] = true;

        for(;;) {
            int d = numeric_limits<int>::max();
            REP(j, m) if (!right[j])
                d <?= residue(ptr[j], j);
            REP(i, n) if (left[i])
                ofsleft[i] -= d;
            REP(j, m) if (right[j])
                ofsright[j] += d;
            int b = -1;
            REP(j, m) if (!right[j] && residue(ptr[j], j) == 0)
                b = j;
            assert(b >= 0);
            trace[b] = ptr[b];
            int c = toleft[b];
            if (c < 0) {
                while(b >= 0) {
                    int a = trace[b];
                    int z = toright[a];
                    toleft[b] = a;
                    toright[a] = b;
                    b = z;
                }
                break;
            }
            right[b] = left[c] = true;
            REP(j, m) if (residue(c, j) < residue(ptr[j], j))
                ptr[j] = c;
        }
    }

    return toright;
}



int main() {

    for(;;) {
        int h, w;
        cin >> h >> w;
        if (h == 0 && w == 0)
            break;

        vector<string> field(h);
        REP(i, h)
            cin >> field[i];

        vector<P> houses, men;
        REP(i, h) REP(j, w) {
            switch(field[i][j]) {
            case 'H': houses.push_back(P(i, j)); break;
            case 'm': men.push_back(P(i, j)); break;
            }
        }

        int n = houses.size();
        vector< vector<int> > adj(n, n);
        REP(i, n) REP(j, n) {
            P d = houses[i] - men[j];
            adj[i][j] = abs(d.real()) + abs(d.imag());
        }

        vector<int> matching = min_cost_match(adj);
        int cost = 0;
        REP(i, n)
            cost += adj[i][matching[i]];
        cout << cost << endl;

    }

    return 0;
}


