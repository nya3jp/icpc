/*
 * UVA 315 - Network
 * 2006-01-17
 * by nya
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>



struct Edge {
    int src, dest;
    double weight;

    Edge() {
    }
    Edge(int src, int dest, double weight) :
        src(src), dest(dest), weight(weight) {1
    }
    friend bool operator>(const Edge& a, const Edge& b) {
        return (a.weight > b.weight);
    }
};

typedef std::vector<Edge> Edges;
typedef std::vector<Edges> Graph;

inline void insert_edge(Graph& g, int a, int b, double w = 0.0) {
    g[a].push_back(Edge(a, b, w));
}

inline bool has_edge(const Graph& g, int a, int b) {
    const Edges& edges = g[a];
    for(int i = 0; i < (int)edges.size(); i++)
        if (edges[i].dest == b)
            return true;
    return false;
}


enum ArticulationPointsConst { UNSEEN = -1 };

int articulation_points_traverse(const Graph& g,
                                 int iNode,
                                 int depth,
                                 std::vector<int>& depths,
                                 std::vector<int>& articulationCounts)
{
    assert(depths[iNode] == UNSEEN);
    depths[iNode] = depth;

    const Edges& edges = g[iNode];

    int minDepth = depth;
    for(int i = 0; i < (int)edges.size(); i++) {
        int adepth = depths[edges[i].dest];
        if (adepth == UNSEEN) {
            adepth = articulation_points_traverse(g,
                                                  edges[i].dest,
                                                  depth+1,
                                                  depths,
                                                  articulationCounts);
            if (adepth >= depth)
                articulationCounts[iNode]++;
        }
        minDepth = std::min(minDepth, adepth);
    }

    return minDepth;
}

/*
 * 関節点かどうか判定する
 * return[i]はノードiが取り除かれたときにできる分裂の数を表す
 * gは無向グラフであること
 */
std::vector<int> articulation_points(const Graph& g)
{
    const int n = g.size();

    std::vector<int> depths(n, UNSEEN);
    std::vector<int> articulationCounts(n, 0);

    for(int iRoot = 0; iRoot < n; iRoot++) {
        if (depths[iRoot] != UNSEEN)
            continue;

        depths[iRoot] = 0;

        const Edges& edges = g[iRoot];
        int nChildren = 0;
        for(int i = 0; i < (int)edges.size(); i++) {
            if (depths[edges[i].dest] == UNSEEN) {
                articulation_points_traverse(g,
                                             edges[i].dest,
                                             1,
                                             depths,
                                             articulationCounts);
                nChildren++;
            }
        }
        articulationCounts[iRoot] = (nChildren >= 2 ? nChildren-1 : 0);
    }
    
    return articulationCounts;
}



int main() {
    std::string line;

    while(true) {
        int n;
        {
            std::getline(std::cin, line);
            std::istringstream is(line);
            is >> n;
        }

        if (n == 0)
            break;

        Graph g(n);

        while(true) {
            std::getline(std::cin, line);
            std::istringstream is(line);
            int a;
            is >> a;
            if (a == 0)
                break;
            a--;

            while(true) {
                int b;
                is >> b;
                b--;
                if (!is)
                    break;

                if (!has_edge(g, a, b)) {
                    insert_edge(g, a, b);
                    insert_edge(g, b, a);
                }
            }
        }

        std::vector<int> articulationCounts = articulation_points(g);

        int result = 0;
        for(int i = 0; i < n; i++) {
            if (articulationCounts[i] > 0)
                result++;
        }

        std::cout << result << std::endl;
    }

    return 0;
}


