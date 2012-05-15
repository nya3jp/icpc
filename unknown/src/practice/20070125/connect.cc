#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cstdio>
#include <cmath>
#include <complex>
#include <cctype>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

#define EPS 1.0e-8

typedef complex<double> P;

struct L {
    P pos, dir;
};

const P ADJS[8] = {P(+2,+1),
                   P(+1,+2),
                   P(-1,+2),
                   P(-2,+1),
                   P(-2,-1),
                   P(-1,-2),
                   P(+1,-2),
                   P(+2,-1),};

namespace std {
    bool operator<(const P& a, const P& b) {
        return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
    }
}

map<P, int> colors;
vector<L> links;
map<P, vector<P> > g;

int ccw(const P& a, const P& b, const P& c) {
    P p = b - a;
    P q = c - a;
    double outp = (conj(p)*q).imag();
    if (abs(outp) > EPS)
        return (outp > 0 ? 1 : -1);
    return 0;
}

bool ss_not_intersects(const L& a, const L& b) {
    P p = a.pos, q = a.pos+a.dir, r = b.pos, s = b.pos+b.dir;
    return (ccw(p, q, r)*ccw(p, q, s) >= 0 || ccw(r, s, p)*ccw(r, s, q) >= 0);
}

bool accept(const L& link) {
    REP(i, links.size())
        if (!ss_not_intersects(links[i], link))
            return false;
    return true;
}


int main() {

    int n, nMoves;
    while(cin >> n >> nMoves && !(n == 0 && nMoves == 0)) {

        colors.clear();
        links.clear();
        g.clear();

        REP(iMove, nMoves) {
            int color = iMove%2;
            double x, y;
            cin >> x >> y;

            P here(x, y);
            colors[here] = color;

            REP(dir, 8) {
                P there = here+ADJS[dir];

                if (colors.count(there) > 0 && colors[there] == color) {
                    L link = {here, there-here};
                    if (accept(link)) {
                        links.push_back(link);
                        g[here].push_back(there);
                        g[there].push_back(here);
                    }
                }
            }
        }

        queue<P> q;
        set<P> visited;
        FOR(it, colors) {
            const P& here = it->first;
            if (here.real() == 0 && colors[here] == 0) {
                q.push(here);
                visited.insert(here);
            }
        }

        while(!q.empty()) {
            P here = q.front();
            q.pop();
            vector<P>& adj = g[here];
            REP(i, adj.size()) {
                P there = adj[i];
                if (visited.count(there) == 0) {
                    q.push(there);
                    visited.insert(there);
                }
            }
        }

        bool ok = false;
        FOR(it, visited) {
            const P& here = *it;
            if (here.real() == n)
                ok = true;
        }

        cout << (ok ? "yes" : "no") << endl;
    }


    return 0;
}
