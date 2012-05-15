#include <cstdio>
#include <vector>
#include <map>

using namespace std;

struct Edge {
    int dest, arrival;
};

typedef map<int, map<int, Edge> > Edges;
typedef vector<Edges> Graph;

int main() {
    int n;
    scanf("%d", &n);
    Graph g(n);
    for(int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        for(int j = 0; j < m; j++) {
            int h1, m1, h2, m2, dest;
            scanf("%d:%d %d:%d %d", &h1, &m1, &h2, &m2, &dest);
            int depart = h1*60+m1;
            int arrival = h2*60+m2;
            Edge e;
            e.dest = dest;
            e.arrival = h2*60+m2;
            if (g[i].find(depart) != g[i].second.end()) {
                if (g[i][depart]
            }
            else {
                g[i][depart].insert(make_pair(arrival, e));
            }
        }
    }
    return 0;
}



