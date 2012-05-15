#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;



struct BipartiteGraph {
    const int n, m;

    enum Const {
        UNMATCHED = -2,
        WHITE = -1
    };

    struct Edge {
        int d, c;
        Edge* p;
        Edge(int d=0, int c=0) : d(d), c(c) {
        }
    };
    typedef vector<Edge*> Edges;
    typedef vector<Edges> Graph;

    Graph g;
    vector< vector<Edge*> > cm;
    vector< vector<bool> > eg;

    BipartiteGraph(int n1, int n2)
        : n(n1+n2), m(n1), g(n),
          cm(n, vector<Edge*>(n, (Edge*)0)),
          eg(n1, vector<bool>(n2, false)) {
    }
    ~BipartiteGraph() {
        for(int i = 0; i < n; i++) {
            int z = g[i].size();
            Edge** v = &g[i][0];
            //for(int j = 0; j < (int)g[i].size(); j++)
            for(int e = 0; e < z; e++)
                delete v[e];
        }
    }

    // •Ó‚¢‚Á‚±‚¢‚ê‚é
    void insert_edge(int i, int j, bool helper = false) {
        if (!helper)
            eg[i][j] = true;
        j += m;
        Edge* e1 = new Edge(j, WHITE);
        Edge* e2 = new Edge(i, WHITE);
        e1->p = e2; e2->p = e1;
        g[i].push_back(e1);
        g[j].push_back(e2);
    }

    bool augment(int i, int color, vector<bool>& visited) {
        Edges& v = g[i];
        for(int e = 0; e < (int)v.size(); e++) {
            if (v[e]->c == WHITE && !visited[v[e]->d]) {
                visited[v[e]->d] = true;
                if (!cm[v[e]->d][color] || augment(cm[v[e]->d][color]->d, color, visited)) {
                    if (cm[v[e]->d][color]) {
                        cm[v[e]->d][color]->c = WHITE;
                        cm[v[e]->d][color]->p->c = WHITE;
                    }
                    v[e]->c = color;
                    v[e]->p->c = color;
                    cm[i][color] = v[e];
                    cm[v[e]->d][color] = v[e]->p;
                    return true;
                }
            }
        }
        return false;
    }

    int paint() {
        int degree = 0;
        for(int i = 0; i < n; i++) {
            degree = max(degree, (int)g[i].size());
        }
        {
            int i = 0, j = m;
            while(true) {
                while(i < m && (int)g[i].size() == degree)
                    i++;
                while(j < n && (int)g[j].size() == degree)
                    j++;
                if (i == m)
                    break;
                insert_edge(i, j-m, true);
            }
        }
        for(int color = 0; color < degree; color++) {
            for(int i = 0; i < n; i++) {
                vector<bool> visited(n, false);
                augment(i, color, visited);
            }
            /*
            for(int i = 0; i < n; i++) {
                Edges& v = g[i];
                int k = v.size();
                for(int e = 0; e < k; e++) {
                    if (v[e]->c == color)
                        swap(v[e], v[--k]);
                }
                for(int e = k; e < (int)v.size(); e++)
                    delete v[e];
                v.resize(k);
            }
            //*/
        }
        return degree;
    }


    // F‚Ì“h‚è•û‚ðo—Í
    void print() {
        vector< vector<int> > vv(m, vector<int>(n-m, -1));
        for(int i = 0; i < m; i++) {
            //Edges& v = g[i];
            int z = g[i].size();
            Edge** v = &g[i][0];
            //for(int e = 0; e < (int)v.size(); e++) {
            for(int e = 0; e < z; e++) {
                int c = v[e]->c;
                int j = v[e]->d;
                assert(c != -1);
                if (eg[min(i, j)][max(i, j)-m])
                    vv[min(i, j)][max(i, j)-m] = c;
            }
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n-m; j++) {
                printf("%d%s",
                       vv[i][j]+1,
                       (j == n-m-1 ? "\n" : " "));
            }
        }
    }
};


int main() {
    int nCases;
    scanf("%d", &nCases);
    for(int iCase = 0; iCase < nCases; iCase++) {
        int n;
        scanf("%d", &n);
        BipartiteGraph g(n, n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                char c;
                scanf(" %c", &c);
                if (c == '*')
                    g.insert_edge(i, j);
            }
        }
        int colors = g.paint();
        printf("%d\n", colors);
        g.print();
    }
    return 0;
}

