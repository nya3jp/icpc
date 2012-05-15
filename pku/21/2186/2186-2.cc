#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define N 10000

typedef vector<int> Edges;
typedef vector<Edges> Graph;

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph g(n), r(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g[a].push_back(b);
        r[b].push_back(a);
    }


    return 0;
}
