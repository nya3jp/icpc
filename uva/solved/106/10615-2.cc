#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;



struct BipartiteGraph {
    const int n, m;

    struct Edge {
        int d, c;
        Edge* p;
        Edge(int d=0, int c=0) : d(d), c(c) {
        }
    };
    typedef vector<Edge*> Edges;
    typedef vector<Edges> Graph;

    Graph g;

    BipartiteGraph(int n1, int n2)
        : n(n1+n2), m(n1), g(n) {
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

    // 辺いっこいれる
    void insert_edge(int i, int j, int white = 0) {
        j += m;
        Edge* e1 = new Edge(j, white);
        Edge* e2 = new Edge(i, white);
        e1->p = e2; e2->p = e1;
        g[i].push_back(e1);
        g[j].push_back(e2);
    }

    // from色をto色に塗り替える
    void repaint(int from, int to) {
        for(int i = 0; i < n; i++) {
            //Edges& v = g[i];
            int z = g[i].size();
            Edge** v = &g[i][0];
            //for(int e = 0; e < (int)v.size(); e++)
            for(int e = 0; e < z; e++)
                if (v[e]->c == from)
                    v[e]->c = to;
        }
    }

    // 頂点の次数を数える
    int count_degree(int i, int white) {
        int degree = 0;
        //Edges& v = g[i];
        int z = g[i].size();
        Edge** v = &g[i][0];
        //for(int e = 0; e < (int)v.size(); e++)
        for(int e = 0; e < z; e++)
            if (v[e]->c == white)
                degree++;
        return degree;
    }

    // 色ごとに辺を数える
    int count_edges(int white) {
        int k = 0;
        for(int i = 0; i < n; i++)
            k += count_degree(i, white);
        return k/2;
    }

    // 最大次数を調べる
    int max_degree(int white = 0) {
        int degree = 0;
        for(int i = 0; i < n; i++)
            degree = max(degree, count_degree(i, white));
        return degree;
    }

    // いっこぬる
    int euler_paint(int i, int white, int color) {
        //Edges& v = g[i];
        int z = g[i].size();
        Edge** v = &g[i][0];
        int e;
        //for(e = 0; e < (int)v.size(); e++)
        for(e = 0; e < z; e++)
            if (v[e]->c == white)
                break;
        v[e]->c = color;
        v[e]->p->c = color;
        return v[e]->d;
    }

    // Euler Split
    bool euler_split(int white, int red, int blue, int orange, int green, int k_degree, const vector<bool>& tomatch) {
        vector<int> degrees(n);
        for(int i = 0; i < n; i++)
            degrees[i] = count_degree(i, white);

        vector<int> oranges(n, 0);
        vector<int> greens(n, 0);

        for(int k = 0; k < n; k++) {
            for(int i = k, j; degrees[i]%2 == 1; i = j) {
                j = euler_paint(i, white, orange);
                degrees[i]--; degrees[j]--;
                oranges[i]++; oranges[j]++; 
                swap(orange, green);
                oranges.swap(greens);
            }
        }
        for(int k = 0; k < n; k++) {
            for(int i = k, j; degrees[i] != 0; i = j) {
                j = euler_paint(i, white, orange);
                degrees[i]--; degrees[j]--;
                oranges[i]++; oranges[j]++; 
                swap(orange, green);
                oranges.swap(greens);
            }
        }

        int orange_count[2] = {0, 0};
        int green_count[2] = {0, 0};
        for(int i = 0; i < n; i++) {
            if (tomatch[i]) {
                orange_count[oranges[i]%2]++;
                green_count[greens[i]%2]++;
            }
        }
        if (!(orange_count[k_degree%2] <= green_count[k_degree%2]))
            swap(orange, green);
        bool complete = (orange_count[0] == 0 || green_count[0] == 0 ||
                         orange_count[1] == 0 || green_count[1] == 0 );

        repaint(orange, red);
        repaint(green, blue);
        return complete;
    }

    // 最大次数の頂点を全て含むように一色塗る
    void paint_one(int white, int red) {
        int g_degree = max_degree(white);
        if (g_degree <= 1) {
            repaint(white, red);
        }
        else {
            int blue = white-1;
            int orange = white-2;
            int green = white-3;
            int purple = white-4;
            int yellow = white-5;

            vector<bool> tomatch(n);
            for(int i = 0; i < n; i++)
                tomatch[i] = (count_degree(i, white) == g_degree);

            euler_split(white, red, blue, orange, green, 0, tomatch);
            if (g_degree%2 != 0) {
                int d_degree = (g_degree+1)/2%2*2-1;
                int k_degree = (g_degree-d_degree)/4;
                bool complete;
                do {
                    complete = euler_split(blue, orange, green, purple, yellow, k_degree, tomatch);
                    if (k_degree%2 == 0) {
                        repaint(orange, red);
                        repaint(green, blue);
                        k_degree = k_degree/2;
                    }
                    else {
                        repaint(red, blue);
                        repaint(orange, blue);
                        repaint(green, red);
                        k_degree = (g_degree - k_degree)/2;
                        d_degree = -d_degree;
                    }
                } while(!complete);
            }
            repaint(red, white);
            paint_one(blue, red);
            repaint(blue, white);
        }
    }

    // 色をぬる
    // 普通に呼び出すときはデフォルトパラメータのままで呼ぶこと
    void paint(int white = 0, int color = 1) {
        int g_degree = max_degree(white);
        if (g_degree%2 == 1) {
            paint_one(white, color);
            color++;
            g_degree--;
            assert(g_degree == max_degree(white));
        }
        if (g_degree == 0)
            return;
        int red = white-1;
        int blue = white-2;
        int orange = white-3;
        int green = white-4;
        vector<bool> tomatch(n, false);
        euler_split(white, red, blue, orange, green, 0, tomatch);
        int red_edges = count_edges(red);
        int blue_edges = count_edges(blue);
        if (blue_edges <= red_edges) {
            repaint(red, white);
        }
        else {
            repaint(blue, white);
            repaint(red, blue);
        }
        paint(blue, color);
        color += g_degree/2;
        int p_degree = 1;
        while(p_degree < g_degree/2)
            p_degree <<= 1;
        int r_degree = p_degree - (g_degree/2);
        for(int i = color-r_degree; i < color; i++)
            repaint(i, white);
        color -= r_degree;
        paint(white, color);
    }

    // 色の塗り方を出力
    // ただしSimple Graph専用みたいな
    void print() {
        vector< vector<int> > vv(m, vector<int>(n-m, 0));
        for(int i = 0; i < m; i++) {
            //Edges& v = g[i];
            int z = g[i].size();
            Edge** v = &g[i][0];
            //for(int e = 0; e < (int)v.size(); e++) {
            for(int e = 0; e < z; e++) {
                int c = v[e]->c;
                int j = v[e]->d;
                vv[min(i, j)][max(i, j)-m] = c;
            }
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n-m; j++) {
                printf("%d%s",
                       vv[i][j],
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
        int colors = g.max_degree();
        g.paint();
        printf("%d\n", colors);
        g.print();
    }
    return 0;
}

