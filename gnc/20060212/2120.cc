#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<int> Edges;
typedef vector<Edges> Graph;

inline bool exists_edge(const Graph& g, int a, int b) {
    return binary_search(g[a].begin(), g[a].end(), b);
}

void insert_edge_uni(Graph& g, int a, int b) {
    if (!exists_edge(g, a, b)) {
        g[a].push_back(0);
        Edges::iterator it = lower_bound(g[a].begin(), g[a].end()-1, b);
        rotate(it, g[a].end()-1, g[a].end());
        assert(*it == 0);
        *it = b;
    }
}
void insert_edge(Graph& g, int a, int b) {
    insert_edge_uni(g, a, b);
    insert_edge_uni(g, b, a);
}
void remove_edge_uni(Graph& g, int a, int b) {
    g[a].erase(remove(g[a].begin(), g[a].end(), b), g[a].end());
}
void remove_edge(Graph& g, int a, int b) {
    if (exists_edge(g, a, b)) {
        remove_edge_uni(g, a, b);
        remove_edge_uni(g, b, a);
    }
}

void simplify(Graph& g) {
    const int n = g.size();

    bool cont;
    do {
        cont = false;
        for(int i = 0; i < n; i++) {
            if (g[i].size() == 1) {
                int j = g[i][0];
                remove_edge(g, i, j);
                remove_edge(g, j, i);
                cont = true;
            }
            else if (g[i].size() == 2) {
                int j = g[i][0];
                int k = g[i][1];
                remove_edge(g, i, j);
                remove_edge(g, i, k);
                insert_edge(g, j, k);
                cont = true;
            }
        }
    } while(cont);
}


bool check(const Graph& g) {
    const int n = g.size();

    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if (exists_edge(g, j, i))
                for(int k = j+1; k < n; k++)
                    if (exists_edge(g, k, i) && exists_edge(g, k, j))
                        for(int l = k+1; l < n; l++)
                            if (exists_edge(g, l, i) && exists_edge(g, l, j) && exists_edge(g, l, k))
                                return false;

    return true;
}

int main() {
    int n, e;
    while(scanf("%d%d", &n, &e), !(n == 0 && e == 0)) {
        Graph g(n);
        for(int i = 0; i < e; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            insert_edge(g, a, b);
        }
        /*
        printf("ok\n{\n");
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < (int)g[i].size(); j++) {
                printf("%d ", g[i][j]);
            }
            printf("\n");
        }
        printf("}\n");
        */
        simplify(g);
        /*
        printf("simple\n{\n");
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < (int)g[i].size(); j++) {
                printf("%d ", g[i][j]);
            }
            printf("\n");
        }
        printf("}\n");
        */
        if (check(g)) {
            printf("Yes, village can be built\n");
        }
        else {
            printf("No, village cannot be built\n");
        }
    }
    return 0;
}

