/*
 * ìÒïîÉOÉâÉtÇÃï”ç êF
 */

#include <vector>
#include <algorithm>
#include <string>

#include <iostream>

using namespace std;


struct BGEC {
    int n, m;                 // number of nodes of {left,right}
    vector< vector<int> > g;  // graph
    vector< vector<int> > cl; // coloring

    BGEC(int n, int m) : n(n), m(m), g(n+m) {
    }

    void add_edge(int a, int b) {
        g[a].push_back(n+b);
        g[n+b].push_back(a);
    }

    int color() {
        int d = 0;
        for(int i = 0; i < n+m; i++)
            d = max<int>(d, g[i].size());
        cl.assign(n+m, vector<int>(d, -1));
        for(int a = 0; a < n; a++) {
            for(int i = 0; i < (int)g[a].size(); i++) {
                int b = g[a][i];
                int ca = min_element(cl[a].begin(), cl[a].end()) - cl[a].begin();
                int cb = min_element(cl[b].begin(), cl[b].end()) - cl[b].begin();
                if (ca != cb) {
                    augment(b, ca, cb);
                    cb = ca;
                }
                cl[a][ca] = b;
                cl[b][cb] = a;
            }
        }
        return d;
    }

    void augment(int a, int c1, int c2) {
        int b = cl[a][c1];
        if (b >= 0) {
            augment(b, c2, c1);
            cl[b][c2] = a;
            cl[a][c1] = -1;
        }
        cl[a][c2] = b;
    }
};


void solve() {
    int n;
    cin >> n;

    BGEC g(n, n);
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < n; j++) {
            if (s[j] == '*')
                g.add_edge(i, j);
        }
    }

    int d = g.color();
    cout << d << endl;
    vector< vector<int> > field(n, vector<int>(n, 0));
    for(int a = 0; a < n; a++) {
        for(int c = 0; c < d; c++) {
            int b = g.cl[a][c] - n;
            if (b >= 0)
                field[a][b] = c+1;
        }
    }

    for(int i = 0; i < n; i++) {
        cout << field[i][0];
        for(int j = 1; j < n; j++) {
            cout << ' ' << field[i][j];
        }
        cout << endl;
    }
}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}
