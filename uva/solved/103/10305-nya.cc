/*
 * UVA 10305 Ordering Tasks
 * 2005-07-27
 * by nya
 */

#include <cstdio>
#include <vector>
#include <list>

void print(int i, const std::vector< std::list<int> >& adj, std::vector<bool>& v) {
    v[i] = true;
    const std::list<int>& ls = adj[i];
    for(std::list<int>::const_iterator it = ls.begin(); it != ls.end(); ++it) {
        if (! v[*it])
            print(*it, adj, v);
    }
    std::printf("%d ", i+1);
}

int main() {
    int n, m;
    while(std::scanf("%d%d", &n, &m), !(n == 0 && m == 0)) {
        std::vector< std::list<int> > adj(n);
        for(int i=0; i<m; i++) {
            int a, b;
            std::scanf("%d%d", &a, &b);
            a--; b--;
            adj[b].push_back(a);
        }
        std::vector<bool> v(n, false);
        for(int i=0; i<n; i++) {
            if (! v[i]) {
                print(i, adj, v);
            }
        }
        std::printf("\n");
    }
    return 0;
}
