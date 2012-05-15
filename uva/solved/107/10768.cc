/*
 * グラフのデータ表現とヘルパ関数
 * rev.02
 */

#include <vector>
//#include <limits>


typedef double Weight;

struct Edge {
    int src, dest;
    Weight weight;

    Edge() {
    }
    Edge(int src, int dest, Weight weight = 0) :
        src(src), dest(dest), weight(weight) {
    }
    friend bool operator<(const Edge& a, const Edge& b) {
        return (a.weight < b.weight);
    }
    friend bool operator>(const Edge& a, const Edge& b) {
        return (a.weight > b.weight);
    }
};

typedef std::vector<Edge> Edges;
typedef std::vector<Edges> Graph;

template<class T>
struct Matrix : public std::vector< std::vector<T> >
{
    Matrix(int n, int m, const T& value = T()) {
        assign(n, m, value);
    }
    void assign(int n, int m, const T& value = T()) {
        std::vector< std::vector<T> >::assign(n, std::vector<T>(m, value));
    }
};


typedef Matrix<Weight> AdjacencyMatrix;

//const Weight WEIGHT_INFTY = std::numeric_limits<Weight>::max();
const Weight WEIGHT_INFTY = 1.0e8;


inline void insert_edge(Graph& g, int a, int b, Weight w = 0) {
    g[a].push_back(Edge(a, b, w));
}

inline bool has_edge(const Graph& g, int a, int b) {
    const Edges& edges = g[a];
    for(int i = 0; i < (int)edges.size(); i++)
        if (edges[i].dest == b)
            return true;
    return false;
}

void make_adjacency_matrix(AdjacencyMatrix& adj,
                           const Graph& g)
{
    const int n = g.size();

    adj.assign(n, n, WEIGHT_INFTY);
    for(int i = 0; i < n; i++) {
        const Edges& edges = g[i];
        for(int j = 0; j < (int)edges.size(); j++) {
            const Edge& e = edges[j];
            adj[e.src][e.dest] = e.weight;
        }
    }
}





#include <algorithm>
#include <iostream>


/// グラフを相似でかつ最も簡単なグラフに変換する
void homeomorphic_simplify(AdjacencyMatrix& adj) {
    const int n = adj.size();

    while(true) {
        bool cont = false;
        for(int i=0; i<n; i++) {
            int k = 0;

            for(int j = 0; j < n; j++)
                if (adj[i][j])
                    k++;

            if (k == 1) {
                int j;
                for(j=0; j<n; j++)
                    if (adj[i][j])
                        break;
                adj[i][j] = adj[j][i] = false;
                cont = true;
            }
            else if (k == 2) {
                int j = -1, l;
                for(l = 0; l < n; l++) {
                    if (adj[i][l]) {
                        if (j < 0)
                            j = l;
                        else
                            break;
                    }
                }

                adj[i][j] = adj[j][i] = false;
                adj[i][l] = adj[l][i] = false;
                adj[j][l] = adj[l][j] = true;
                cont = true;
            }
        }
        if (!cont)
            break;
    }
}


/// グラフがplanarかどうか判定する
/**
 * \param[in] adj homeomorphic_simplify()を行った隣接行列
 */
bool is_planar(const AdjacencyMatrix& adj) {
    const int n = adj.size();

    for(int i1=0; i1<n; i1++)
        for(int i2=i1+1; i2<n; i2++)
            if (adj[i2][i1])
                for(int i3=i2+1; i3<n; i3++)
                    if (adj[i3][i1] && adj[i3][i2])
                        for(int i4=i3+1; i4<n; i4++)
                            if (adj[i4][i1] && adj[i4][i2] && adj[i4][i3])
                                for(int i5=i4+1; i5<n; i5++)
                                    if (adj[i5][i1] && adj[i5][i2] && adj[i5][i3] && adj[i5][i4])
                                        return false;

    for(int i1=0; i1<n; i1++)
        for(int i2=i1+1; i2<n; i2++)
            if (adj[i2][i1])
                for(int i3=i1+1; i3<n; i3++)
                    if (adj[i3][i2])
                        for(int i4=i2+1; i4<n; i4++)
                            if (adj[i4][i1] && adj[i4][i3])
                                for(int i5=i3+1; i5<n; i5++)
                                    if (adj[i5][i2] && adj[i5][i4])
                                        for(int i6=i4+1; i6<n; i6++)
                                            if (adj[i6][i1] && adj[i6][i3] && adj[i6][i5])
                                                return false;

    return true;
}




int main() {
    int n, m;
    while(std::cin >> n >> m) {
        AdjacencyMatrix adj(n, n, 0);

        for(int i=0; i<m; i++) {
            int a, b;
            std::cin >> a >> b;
            a--; b--;
            adj[a][b] = adj[b][a] = 1;
        }

        homeomorphic_simplify(adj);

        std::cout << (is_planar(adj) ? "YES" : "NO") << std::endl;
    }

    return 0;
}

