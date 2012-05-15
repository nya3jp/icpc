/*
 * UVA 10890 Maze
 * 2006-05-03
 * by nya
 *
 * A* search.
 *
 */

#include <iostream>
#include <vector>
#include <complex>
#include <utility>
#include <set>
#include <queue>

using namespace std;

typedef complex<int> P;

inline int abs(int n) { return (n < 0 ? -n : n); }

#define CB0(a, b) i = (i & b) + ((i >> a) & b)
inline int bitcount(unsigned int i) {
    CB0(1,  0x55555555);
    CB0(2,  0x33333333);
    CB0(4,  0x0f0f0f0f);
    CB0(8,  0x00ff00ff);
    CB0(16, 0x0000ffff);
    return i;
}

struct Node {
    int k, vis, len, rem;
    Node() {
    }
    Node(int k, int vis, int len, int rem) : k(k), vis(vis), len(len), rem(rem) {
    }
};
bool operator>(const Node& a, const Node& b) {
    return (a.len+a.rem > b.len+b.rem);
}

int solve(const vector< vector<int> >& adj, int s) {
    const int n = adj.size();

    set<long long int> m;

    priority_queue<Node, vector<Node>, greater<Node> > q;
    q.push(Node(0, 1, 0, 0));

    while(!q.empty()) {
        Node node = q.top();
        q.pop();

        long long int id = (long long int)node.vis | (long long int)node.k << 32;
        if (m.count(id) == 0) {
            //printf("visiting %d (ptn=%08x) len=%d, rem=%d\n", node.k, node.vis, node.len, node.rem);
            m.insert(id);
            int c = bitcount(node.vis);
            if (c == s+2)
                return node.len;
            else if (c == s+1) {
                Node next(1, node.vis | 2, node.len+adj[node.k][1], 0);
                long long int id2 = (long long int)next.vis | (long long int)next.k << 32;
                if (m.count(id2) == 0)
                    q.push(next);
            }
            else {
                for(int i = 2; i < n; i++) {
                    if ((node.vis & (1 << i)) == 0) {
                        Node next(i, node.vis | (1 << i), node.len+adj[node.k][i], adj[i][1]);
                        long long int id2 = (long long int)next.vis | (long long int)next.k << 32;
                        if (m.count(id2) == 0)
                            q.push(next);
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    for(int iCase = 0; ; iCase++) {
        int n, t, s;
        cin >> n >> t >> s;
        if (n == 0 && t == 0 && s == 0)
            break;

        vector<P> v;
        v.push_back(P(0, 0));
        v.push_back(P(n-1, n-1));
        for(int i = 0; i < t; i++) {
            int x, y;
            cin >> x >> y;
            v.push_back(P(x, y));
        }
        vector< vector<int> > adj(t+2, vector<int>(t+2));
        for(int i = 0; i < t+2; i++) {
            for(int j = 0; j < t+2; j++) {
                P d = v[i] - v[j];
                adj[i][j] = abs(d.real()) + abs(d.imag());
            }
        }
        cout << "Case " << iCase+1 << ": " << solve(adj, s) << endl;
    }
    return 0;
}
