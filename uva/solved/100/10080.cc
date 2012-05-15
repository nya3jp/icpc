#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> P;

#include <vector>


struct BGM {
    int n, m;                 // number of nodes of {left,right}
    vector< vector<int> > g;  // graph
    vector<int> z;            // matching
    vector<bool> v;           // visited-flag

    BGM(int n, int m) : n(n), m(m), g(n) {
    }

    void add_edge(int a, int b) {
        g[a].push_back(b);
    }

    bool augment(int a) {
        if (a < 0)
            return true;
        vector<int>& e = g[a];
        for(int i = 0; i < (int)e.size(); i++) {
            int b = e[i];
            if (!v[b]) {
                v[b] = true;
                if (augment(z[b])) {
                    z[b] = a;
                    return true;
                }
            }
        }
        return false;
    }

    int match() {
        z.assign(m, -1);
        int matches = 0;
        for(int a = 0; a < n; a++) {
            v.assign(m, false);
            if (augment(a))
                matches++;
        }
        return matches;
    }
};

int main() {

    int n, m, s, v;
    while(cin >> n >> m >> s >> v) {

        vector<P> g;
        for(int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            g.push_back(P(x, y));
        }
        vector<P> h;
        for(int i = 0; i < m; i++) {
            double x, y;
            cin >> x >> y;
            h.push_back(P(x, y));
        }
        BGM bgm(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (abs(g[i]-h[j]) <= s*v + 1.0e-8) {
                    bgm.add_edge(i, j);
                }
            }
        }
        cout << (n - bgm.match()) << endl;
    }
    return 0;
}
