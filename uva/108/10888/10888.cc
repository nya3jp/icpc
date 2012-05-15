#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <complex>
#include <set>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

const int INF = 2000;

vector<int> min_cost_match(vector< vector<int> > adj) {
    int n = adj.size();
    int m = adj[0].size();

    vector<int> toright(n, -1), toleft(m, -1);

    REP(r, n) {
        vector<bool> left(n, false), right(m, false);
        vector<int> trace(m, -1);
        left[r] = true;

        for(;;) {
            int a = -1, b;
            REP(i, n) REP(j, m) if (left[i] && !right[j] && adj[i][j] == 0)
                a = i, b = j;
            if (a < 0) {
                int d = 0x7fffffff;//numeric_limits<int>::max();
                REP(i, n) REP(j, m) if (left[i] && !right[j])
                    d <?= adj[i][j];
                REP(i, n) REP(j, m) {
                    if (left[i])
                        adj[i][j] -= d;
                    if (right[j])
                        adj[i][j] += d;
                }
            }
            else {
                trace[b] = a;
                int c = toleft[b];
                if (c < 0) {
                    while(b >= 0) {
                        a = trace[b];
                        int z = toright[a];
                        toleft[b] = a;
                        toright[a] = b;
                        b = z;
                    }
                    break;
                }
                right[b] = left[c] = true;
            }
        }
    }

    return toright;
}

vector<int> min_cost_match2(vector< vector<int> > adj) {
    int n = adj.size();
    int m = adj[0].size();

    vector<int> toright(n, -1), toleft(m, -1);

    REP(r, n) {
        vector<bool> left(n, false), right(m, false);
        vector<int> trace(m, -1);
        left[r] = true;

        for(;;) {
            int d = 0x7fffffff;
            REP(i, n) REP(j, m) if (left[i] && !right[j])
                d <?= adj[i][j];
            int a, b;
            REP(i, n) REP(j, m) {
                if (left[i])
                    adj[i][j] -= d;
                if (right[j])
                    adj[i][j] += d;
                if (left[i] && !right[j] && adj[i][j] == 0)
                    a = i, b = j;
            }
            trace[b] = a;
            int c = toleft[b];
            if (c < 0) {
                while(b >= 0) {
                    a = trace[b];
                    int z = toright[a];
                    toleft[b] = a;
                    toright[a] = b;
                    b = z;
                }
                break;
            }
            right[b] = left[c] = true;
        }
    }

    return toright;
}

#define residue(i,j) (adj[i][j] + ofsleft[i] + ofsright[j])

vector<int> min_cost_match_improved(vector< vector<int> > adj) {
    int n = adj.size();
    int m = adj[0].size();

    vector<int> toright(n, -1), toleft(m, -1);
    vector<int> ofsleft(n, 0), ofsright(m, 0);

    REP(r, n) {
        vector<bool> left(n, false), right(m, false);
        vector<int> trace(m, -1), ptr(m, r);
        left[r] = true;

        for(;;) {
            int d = 0x7fffffff;
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



typedef complex<int> P;
namespace std {
    bool operator<(const P& a, const P& b) {
        return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
    }
}

int main() {

    //freopen("10888.in", "r", stdin);

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int h, w;
        cin >> h >> w;

        vector<string> field(h);
        REP(i, h)
            cin >> field[i];

        set<P> fl;
        REP(i, h) REP(j, w)
            if (field[i][j] != '#')
                fl.insert(P(i, j));

        vector<P> boxes;
        vector<P> holes;
        REP(i, h) REP(j, w) {
            if (field[i][j] == 'B')
                boxes.push_back(P(i, j));
            if (field[i][j] == 'X')
                holes.push_back(P(i, j));
        }

        int n = boxes.size();
        int m = holes.size();
        vector< vector<int> > adj(n, m);
        REP(i, n) {
            P origin = boxes[i];
            map<P, int> dists;
            queue<P> q;
            dists[origin] = 0;
            q.push(origin);
            while(!q.empty()) {
                P here = q.front();
                q.pop();
                const P ADJS[4] = {P(0,1),P(0,-1),P(1,0),P(-1,0)};
                REP(j, 4) {
                    P there = here + ADJS[j];
                    if (fl.count(there) > 0 && dists.count(there) == 0) {
                        dists[there] = dists[here] + 1;
                        q.push(there);
                    }
                }
            }
            REP(j, m) {
                if (dists.count(holes[j]) == 0)
                    adj[i][j] = INF;
                else
                    adj[i][j] = dists[holes[j]];
            }
        }

        /*
        REP(i, n) {
            REP(j, n)
                cout << adj[i][j] << " ";
            cout << endl;
        }
        */

        vector<int> matching = min_cost_match_improved(adj);

        int res = 0;
        REP(i, n)
            res += adj[i][matching[i]];

        cout << res << endl;

    }

    return 0;
}
