#include <cstdio>
#include <algorithm>

using namespace std;

template<class T>
struct Matrix {
    const int n, m;
    T* data;
    Matrix(int n, int m) : n(n), m(m) {
        data = new T[n*m];
    }
    virtual ~Matrix() {
        delete[] data;
    }
    void clear(const T& value) {
        fill(data, data+n*m, value);
    }
    inline T* operator[](int i) {
        return data+m*i;
    }
    inline const T* operator[](int i) const {
        return data+m*i;
    }
};

void search(int j,
            int* const * g,
            const Matrix<bool>& adj,
            const int pivot,
            const int* matchings,
            Matrix<bool>& visited,
            Matrix<bool>& result)
{
    visited[matchings[j]][j] = true;
    if (adj[pivot][j])
        result[pivot][j] = true;
    const int* edges = g[j];
    for(int e = 0; edges[e] != -1; e++) {
        int i = edges[e];
        if (!visited[matchings[i]])
            search(matchings[i], g, adj, pivot, matchings, visited, result);
    }
}


int main() {
    int n;
    scanf("%d", &n);
    Matrix<bool> adj(n, n);
    adj.clear(false);
    int** g = new int*[n];

    {
        Matrix<bool> adjr(n, n);
        adjr.clear(false);
        for(int i = 0; i < n; i++) {
            int m;
            scanf("%d", &m);
            for(int j = 0; j < m; j++) {
                int k;
                scanf("%d", &k);
                //k--;
                adj[i][k] = true;
                adjr[k][i] = true;
            }
        }
        for(int i = 0; i < n; i++) {
            int m = count(adjr[i], adjr[i]+n, true);
            g[i] = new int[m+1];
            int k = 0;
            for(int j = 0; j < n; j++) {
                if (adjr[i][j])
                    g[i][k++] = j;
            }
            assert(k == m);
            g[i][m] = -1;
        }
    }

    int* matchings = new int[n];
    for(int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        //k--;
        matchings[i] = k;
    }

    Matrix<bool> result(n, n);
    result.clear(false);
    Matrix<bool> visited(n, n);
    visited.clear(false);
    for(int i = 0; i < n; i++) {
        fprintf(stderr, "checking %d...\n", i);
        search(matchings[i], g, adj, i, matchings, visited, result);
    }

    for(int i = 0; i < n; i++) {
        bool* v = result[i];
        printf("%d", count(v, v+n, true));
        for(int j = 0; j < n; j++) {
            if (v[j])
                printf(" %d", j+1);
        }
        printf("\n");
    }
    return 0;
}


