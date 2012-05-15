/*
 * UVA 10496 Collecting Beepers
 * 2005-08-02
 * by nya
 */

#include <iostream>

#define MAX_NODES 21

typedef int Graph[MAX_NODES][MAX_NODES];

const int INF = 0x7fffffff; // std::numeric_limits<int>::max();

struct Point2D {
    int x, y;
};

inline int abs(int a) {
    return (a < 0 ? -a : a);
}
inline int distance(const Point2D& a, const Point2D& b) {
    return ( abs(a.x-b.x) + abs(a.y-b.y) );
}

class TSPX {
private:
    const int nNodes;
    const Graph& g;

public:
    TSPX(int nNodes, const Graph& g) : nNodes(nNodes), g(g) {
    }

    int search() {
        shortest_len = INF;
        for(int i=0; i<nNodes; i++) {
            visited[i] = (i == 0);
        }
        dfs(0, 0);
        return shortest_len;
    }

private:
    int shortest_len;
    bool visited[MAX_NODES];

    void dfs(int pos, int len) {
        if (len > shortest_len)
            return;
        bool last = true;
        for(int i=0; i<nNodes; i++) {
            if (! visited[i]) {
                visited[i] = true;
                dfs(i, len+g[pos][i]);
                visited[i] = false;
                last = false;
            }
        }
        if (last) {
            int lastlen = len+g[pos][0];
            if (lastlen < shortest_len) {
                shortest_len = lastlen;
            }
        }
    }
};



int main() {
    int nCases;
    std::cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {
        {
            int tmp;
            std::cin >> tmp >> tmp;
        }

        Point2D points[MAX_NODES];
        int nNodes;
        std::cin >> points[0].x >> points[0].y;
        std::cin >> nNodes;
        nNodes++;
        for(int i=1; i<nNodes; i++) {
            std::cin >> points[i].x >> points[i].y;
        }

        Graph g;
        for(int i=0; i<nNodes; i++) {
            g[i][i] = 0;
            for(int j=i+1; j<nNodes; j++) {
                g[i][j] = g[j][i] = distance(points[i], points[j]);
            }
        }

        TSPX tspx(nNodes, g);
        std::cout << "The shortest path has length " << tspx.search() << std::endl;
    }
    return 0;
}



