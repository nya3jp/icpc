#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef double Weight;

struct Edge {
    int src, dest;
    Weight weight;

    Edge() {
    }

    Edge(int src, int dest, Weight weight = 0) :
        src(src), dest(dest), weight(weight) {
    }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

enum Const {
    UNSEEN = -1
};

inline void insert_edge(Graph& g, int a, int b, Weight w = 0) {
    g[a].push_back(Edge(a, b, w));
}



int articulation_points_traverse(const Graph& g,
                                 int iNode,
                                 int depth,
                                 vector<int>& depths,
                                 vector<int>& articulation_counts)
{
    assert(depths[iNode] = UNSEEN);
    depths[iNode] = depth;
    const Edges& edges = g[iNode];
    int min_depth = depth;
    for(int i = 0; i < (int)edges.size(); i++) {
        int adepth = depths[edges[i].dest];
        if (adepth == UNSEEN) {
            adepth = articulation_points_traverse(g,
                                                  edges[i].dest,
                                                  depth+1,
                                                  depths,
                                                  articulation_counts);
            if (adepth >= depth)
                articulation_counts[iNode]++;
        }
        min_depth = min(min_depth, adepth);
    }

    return min_depth;
}

vector<int> articulation_points(const Graph& g)
{
    const int n = g.size();

    vector<int> depths(n, UNSEEN);
    vector<int> articulation_counts(n, 0);

    int roots = 0;
    for(int iRoot = 0; iRoot < n; iRoot++) {
        if (depths[iRoot] != UNSEEN)
            continue;

        depths[iRoot] = 0;
        roots++;

        const Edges& edges = g[iRoot];
        int nChildren = 0;
        for(int i = 0; i < (int)edges.size(); i++) {
            if (depths[edges[i].dest] == UNSEEN) {
                articulation_points_traverse(g,
                                             edges[i].dest,
                                             1,
                                             depths,
                                             articulation_counts);
                nChildren++;
            }
        }
        articulation_counts[iRoot] = nChildren - 1;
    }
    for(int i = 0; i < n; i++) {
        articulation_counts[i] += roots;
    }
    return articulation_counts;
}



int main() {
    int p, c;
    //while(cin >> p >> c && !(p == 0 && c == 0)) {
    while(scanf("%d%d", &p, &c), !(p == 0 && c == 0)) {
        Graph g(p);
        for(int i = 0; i < c; i++) {
            int a, b;
            //cin >> a >> b;
            scanf("%d%d", &a, &b);
            insert_edge(g, a, b);
            insert_edge(g, b, a);
        }
        vector<int> articulation_counts = articulation_points(g);
        int answer = *max_element(articulation_counts.begin(), articulation_counts.end());
        //cout << answer << endl;
        printf("%d\n", answer);
    }
    return 0;
}

