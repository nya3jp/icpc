#include <cstdio>
#include <complex>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

struct P {
    int x, y;
};

struct Edge {
    int src, dest;
    double weight;
};

bool operator<(const Edge& a, const Edge& b) {
    return (a.weight < b.weight);
}
int cmp(const void* a_, const void* b_) {
    const Edge* a = (const Edge*)a_;
    const Edge* b = (const Edge*)b_;
    double d = a->weight - b->weight;
    if (d > 0)
        return 1;
    if (d < 0)
        return -1;
    return 0;
}

bool by_index(const Edge& a, const Edge& b) {
    return make_pair(a.src, a.dest) < make_pair(b.src, b.dest);
}

//typedef vector<int> Forest;
typedef int Forest[750];

void new_forest(Forest& f, int n) {
    //return Forest(n, -1);
    REP(i, n)
        f[i] = -1;
}

int find_root(Forest& v, int i) {
    return (v[i] < 0 ? i : (v[i] = find_root(v, v[i])));
}

bool unify(Forest& v, int i, int j) {
    int ri = find_root(v, i);
    int rj = find_root(v, j);
    if (ri != rj) {
        if (v[ri] > v[rj])
            swap(ri, rj);
        v[ri] += v[rj];
        v[rj] = ri;
        return true;
    }
    return false;
}

P v[750];

void myqsort(Edge* v, int n) {
    Edge* p = v[0];
    int i = 0, j = n-1;
    for(;;) {
        while(cmp(v+i, p) <= 0)
            i++;
}

int main() {

    int n;
    scanf("%d", &n);

    //vector<P> v(n);
    REP(i, n)
        scanf("%d%d", &v[i].x, &v[i].y);


    /*
      n = 750;
    REP(i, n) {
        v[i] = (P){rand(), rand()};
    }
    */

    Forest f;
    new_forest(f, n);
    
    int m;
    scanf("%d", &m);

    //m = 0;

    int remaining = n-1;

    REP(i, m) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        if (a > b)
            swap(a, b);
        if (unify(f, a, b))
            remaining--;
    }

    //vector<Edge> edges;
    //edges.reserve(n*(n-1)/2);
    Edge* edges = new Edge[n*(n-1)/2];
    int nEdges = 0;
    int groups[750];
    REP(i, n)
        groups[i] = find_root(f, i);
    REP(i, n) for(int j = i+1; j < n; j++) if (groups[i] != groups[j]) {
        double w = hypot(v[i].x-v[j].x, v[i].y-v[j].y);
        //edges.push_back((Edge){i,j,w});
        edges[nEdges++] = (Edge){i, j, w};
    }
    //sort(edges, edges+k);
    //fprintf(stderr, "%d %d\n", nEdges, n*(n-1)/2);
    //qsort(edges, nEdges, sizeof(Edge), cmp);
    myqsort(edges, nEdges);
    //sort(ALLOF(edges));

    /*
    REP(i, nEdges) {
        Edge& e = edges[i];
        assert(0 <= e.src && e.src < n);
        assert(0 <= e.dest && e.dest < n);
    }
    */

    vector<Edge> res;
    res.reserve(n);
    for(int i = 0; remaining > 0; i++) {
        Edge& e = edges[i];
        /*
        if (unify(f, e.src, e.dest)) {
            remaining--;
            res.push_back(e);
        }
        */
        if (groups[e.src] != groups[e.dest]) {
            unify(f, e.src, e.dest);
            REP(i, n)
                groups[i] = find_root(f, i);
            res.push_back(e);
            remaining--;
        }
    }

    sort(ALLOF(res), by_index);

    REP(i, res.size()) {
        int a = res[i].src;
        int b = res[i].dest;
        printf("%d %d\n", a+1, b+1);
    }

    return 0;
}
