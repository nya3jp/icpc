#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define N 1000

int n;
bool g[N][N];

int bcc_decompose(int a, int depth, vector<int>& labels, vector<int>& comp, vector<int>& arts, vector< vector<int> >& bccs) {
    int children = 0, upward = labels[a] = depth;
    REP(b, n) if (g[a][b]) {
        int u = labels[b];
        if (u < 0) {
            int k = comp.size();
            u = bcc_decompose(b, depth+1, labels, comp, arts, bccs);
            if (u >= depth) {
                comp.push_back(a);
                bccs.push_back(vector<int>(comp.begin()+k, comp.end()));
                comp.erase(comp.begin()+k, comp.end());
                if (depth > 0 || children > 0)
                    arts.push_back(a);
            }
        }
        upward <?= u;
        children++;
    }
    comp.push_back(a);
    if (depth == 0 && children == 0)
        bccs.push_back(comp);
    return upward;
}

void bcc_decompose(vector<int>& arts, vector< vector<int> >& bccs) {
    vector<int> comp, labels(n, -1);
    REP(r, n) if (labels[r] < 0) {
        comp.clear();
        bcc_decompose(r, 0, labels, comp, arts, bccs);
    }
}

int colors[N];
bool odds[N];

bool bipartite(vector<int>& bcc) {
    memset(colors, -1, sizeof(colors));
    int s = bcc[0];
    queue<int> q;
    q.push(s);
    colors[s] = 0;
    while(!q.empty()) {
        int a = q.front();
        q.pop();
        REP(i, bcc.size()) {
            int b = bcc[i];
            if (g[a][b]) {
                if (colors[b] == colors[a])
                    return false;
                if (colors[b] < 0) {
                    colors[b] = colors[a] ^ 1;
                    q.push(b);
                }
            }
        }
    }
    return true;
}

int main() {

    for(;;) {
        int m;
        scanf("%d%d", &n, &m);
        if (n == 0)
            break;

        REP(i, n) REP(j, n)
            g[i][j] = !(i == j);

        REP(i, m) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--; b--;
            g[a][b] = g[b][a] = false;
        }

        vector<int> arts;
        vector< vector<int> > bccs;
        bcc_decompose(arts, bccs);

        {
            REP(a, n) {
                int k = count(ALLOF(arts), a) + 1;
                int kk = 0;
                REP(i, bccs.size())
                    if (count(ALLOF(bccs[i]), a) > 0)
                        kk++;
                assert(k == kk);
            }
        }

        memset(odds, 0, sizeof(odds));
        REP(iComp, bccs.size()) {
            vector<int>& bcc = bccs[iComp];
            /*
            printf("comp");
            REP(i, bcc.size())
                printf(" %d", bcc[i]);
            */
            if (!bipartite(bcc))
                REP(i, bcc.size())
                    odds[bcc[i]] = true;
            //printf(" is %sbipartite\n", bipartite(bcc)?"":"NOT ");
        }

        printf("%d\n", count(odds, odds+n, false));

    }

    return 0;
}
