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

#define N 100
#define H 200

struct Node {
    int i, j, w;
};
bool operator<(const Node& a, const Node& b) {
    return (a.w < b.w);
}

int n;
int field[N][N];
Node nodes[N*N];

const int ADJ[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

/*
bool visited[N][N];
int go1(int low) {
    //priority_queue<Node, vector<Node>, greater<Node> > q;
    multiset<Node> q;

    if (field[0][0] < low)
        return INT_MAX;

    memset(visited, 0, sizeof(visited));

    //q.push((Node){0, 0, field[0][0]});
    q.insert((Node){0, 0, field[0][0]});
    while(!q.empty()) {
        //Node here = q.top();
        Node here = *q.begin();
        //q.pop();
        q.erase(q.begin());
        if (visited[here.i][here.j])
            continue;
        visited[here.i][here.j] = true;
        if (here.i == n-1 && here.j == n-1)
            return (here.w - low);
        REP(dir, 4) {
            Node there(here);
            there.i += ADJ[dir][0];
            there.j += ADJ[dir][1];
            if (0 <= there.i && there.i < n && 0 <= there.j && there.j < n) {
                if (field[there.i][there.j] >= low && !visited[there.i][there.j]) {
                    there.w >?= field[there.i][there.j];
                    //q.push(there);
                    q.insert(there);
                }
            }
        }
    }

    return INT_MAX;
}
*/

int uf[N*N];
bool visited[N][N];

int find_root(int a) {
    return (uf[a] < 0 ? a : (uf[a] = find_root(uf[a])));
}

void unify(int a, int b) {
    int ra = find_root(a), rb = find_root(b);
    if (ra != rb) {
        if (!(uf[ra] < uf[rb]))
            swap(ra, rb);
        uf[ra] += uf[rb];
        uf[rb] = ra;
    }
}

int go(int low) {
    memset(uf, -1, sizeof(uf));
    memset(visited, 0, sizeof(visited));

    if (field[0][0] < low || field[n-1][n-1] < low)
        return INT_MAX;

    REP(iNode, n*n) {
        Node& node = nodes[iNode];
        if (node.w < low)
            continue;
        visited[node.i][node.j] = true;
        REP(dir, 4) {
            int ni = node.i + ADJ[dir][0], nj = node.j + ADJ[dir][1];
            if (0 <= ni && ni < n && 0 <= nj && nj < n) {
                if (visited[ni][nj]) {
                    unify(node.i*n+node.j, ni*n+nj);
                }
            }
        }
        if (find_root(0) == find_root(n*n-1))
            return (node.w - low);
    }
    return INT_MAX;
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        scanf("%d", &n);
        REP(i, n) REP(j, n)
            scanf("%d", &field[i][j]);

        REP(i, n) REP(j, n)
            nodes[i*n+j] = (Node){i, j, field[i][j]};
        sort(nodes, nodes+n*n);

        int res = INT_MAX;
        REP(low, H+1) {
            int lo = go(low);
            if (lo == INT_MAX)
                break;
            res <?= lo;
        }

        printf("Scenario #%d:\n%d\n\n", iCase+1, res);

    }

    return 0;
}
