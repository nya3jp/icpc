// UVA 302 John's Trip
// Euler Tour

#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<pair<int,int> > Edges;
typedef vector<Edges> Graph;

void traverse(Graph& g, int a, vector<int>& route, vector<bool>& used) {
    Edges& v = g[a];
    for(int i = 0; i < (int)v.size(); i++) {
        int b = v[i].first;
        int id = v[i].second;
        if (!used[id]) {
            used[id] = true;
            traverse(g, b, route, used);
            route.push_back(id);
        }
    }
}

bool check(Graph& g) {
    int k = 0;
    int n = g.size();
    for(int i = 0; i < n; i++)
        if (g[i].size()%2 == 1)
            k++;
    return (k == 0);
}

struct Indexer {
    map<int,int> m;
    vector<int> v;
    int index(int id) {
        if (m.count(id) == 0) {
            m.insert(make_pair(id, (int)m.size()));
            v.push_back(id);
        }
        return m[id];
    }
    int invert(int i) {
        return v[i];
    }
};

struct Sorter {
    Indexer& x;
    Sorter(Indexer& x) : x(x) {
    }
    bool operator()(const Edges::value_type& a, const Edges::value_type& b) {
        return x.invert(a.second) < x.invert(b.second);
    }
};

int main() {

    while(true) {
        int m = 0;
        Graph g;
        int s = -1;
        Indexer indexer;
        Indexer indexer2;
        while(true) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == 0 && y == 0)
                break;
            int z;
            scanf("%d", &z);
            int a = indexer.index(x);
            int b = indexer.index(y);
            int id = indexer2.index(z);
            if ((int)g.size() <= max(a, b))
                g.resize(max(a, b)+1);
            g[a].push_back(make_pair(b, id));
            g[b].push_back(make_pair(a, id));
            if (s < 0)
                s = indexer.index(min(x, y));
            m++;
        }
        if (m == 0)
            break;
        int n = g.size();
        {
            Sorter so(indexer2);
            for(int i = 0; i < n; i++) {
                sort(g[i].begin(), g[i].end(), so);
            }
        }

        if (!check(g)) {
            printf("Round trip does not exist.\n");
        }
        else {
            vector<int> route;
            //set<int> used;
            vector<bool> used(m, false);
            traverse(g, s, route, used);

            for(int i = (int)route.size()-1; i >= 0; i--) {
                printf("%d%s", indexer2.invert(route[i]), (i == 0 ? "\n" : " "));
            }
        }
        printf("\n");
    }


    return 0;
}
