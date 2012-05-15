/*
 * UVA 10462 Is There A Second Way Left?
 * 2005-08-02
 * by nya
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
//#include <limits>
#include <cassert>

typedef std::pair< std::pair<int, int>, int > Edge;
typedef std::vector< std::list< std::pair<int, int> > > Graph;

class UFR {
private:
    mutable std::vector<int> v;
public:
    UFR(int n) : v(n, -1) {
    }
    bool unite(int a, int b) {
        a = find_root(a);
        b = find_root(b);
        if (a != b) {
            if (v[b] < v[a])
                std::swap(a, b);
            v[a] += v[b];
            v[b] = a;
            return true;
        }
        return false;
    }
    bool check(int a, int b) {
        return (find_root(a) == find_root(b));
    }
    bool one() {
        return (std::count_if(v.begin(), v.end(), std::bind2nd(std::less<int>(), 0)) == 1);
    }
private:
    int find_root(int a) {
        if (v[a] < 0)
            return a;
        return (v[a] = find_root(v[a]));
    }
};

bool longest_edge_in_loop(const Graph& g, int pos, int prev, int goal, int& len) {
    if (pos == goal)
        return true;
    for(Graph::value_type::const_iterator it = g[pos].begin();
        it != g[pos].end();
        ++it) {
        if (it->first != prev && longest_edge_in_loop(g, it->first, pos, goal, len)) {
            len = std::max(len, it->second);
            return true;
        }
    }
    return false;
}

bool edge_less(const Edge& a, const Edge& b) {
    return (a.second < b.second);
}

int main() {

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        std::cout << "Case #" << (iCase+1) << " : ";

        int nVertices, nEdges;
        std::cin >> nVertices >> nEdges;
        std::vector<Edge> edges(nEdges);
        for(int i=0; i<nEdges; i++) {
            Edge& edge = edges[i];
            std::cin >> edge.first.first >> edge.first.second >> edge.second;
            edge.first.first--;
            edge.first.second--;
        }

        std::sort(edges.begin(), edges.end(), edge_less);

        std::vector<bool> edge_in_tree(nEdges, false);
        std::vector<Edge> tree;
        int tree_cost = 0;

        UFR u(nVertices);
        for(int i=0; i<nEdges && !u.one(); i++) {
            const Edge& edge = edges[i];
            if (u.unite(edge.first.first, edge.first.second)) {
                //std::cerr << "(" << edge.first.first << "-" << edge.first.second << ") ";
                tree.push_back(edge);
                tree_cost += edge.second;
                edge_in_tree[i] = true;
            }
        }

        if (! u.one()) {
            std::cout << "No way" << std::endl;
        }
        else {

            assert(nEdges >= nVertices-1);

            if (nEdges == nVertices-1) {
                std::cout << "No second way" << std::endl;
            }
            else {
                Graph g(nVertices);
                for(int i=0; i<nEdges; i++) {
                    if (edge_in_tree[i]) {
                        const Edge& edge = edges[i];
                        g[edge.first.first].push_back( std::make_pair(edge.first.second, edge.second) );
                        g[edge.first.second].push_back( std::make_pair(edge.first.first, edge.second) );
                    }
                }
                int tree_delta_cost = 0x7fffffff; //std::numeric_limits<int>::max();
                for(int iNewEdge=0; iNewEdge<nEdges; iNewEdge++) {
                    if (! edge_in_tree[iNewEdge]) {
                        const Edge& edge = edges[iNewEdge];
                        int len = 0;
                        longest_edge_in_loop(g, edge.first.first, -1, edge.first.second, len);
                        tree_delta_cost = std::min(tree_delta_cost, edge.second - len);
                    }
                }
                assert(tree_delta_cost >= 0);
                std::cout << (tree_cost + tree_delta_cost) << std::endl;
            }

        }

    }

    return 0;
}
