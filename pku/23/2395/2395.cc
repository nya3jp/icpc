#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

struct Edge {
    int a, b, c;
};
bool operator<(const Edge& a, const Edge& b) {
    return a.c < b.c;
}

struct UF {
    vector<int> data;
    UF(int n) : data(n, -1) {
    }
    bool link(int a, int b) {
        int ra = root(a);
        int rb = root(b);
        if (ra != rb) {
            if (!(data[ra] < data[rb]))
                swap(ra, rb);
            data[ra] += data[rb];
            data[rb] = ra;
        }
        return ra != rb;
    }
    int root(int a) {
        return (data[a] < 0 ? a : (data[a] = root(data[a])));
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> v(m);
    REP(i, m) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        v[i].a = a;
        v[i].b = b;
        v[i].c = c;
    }
    sort(ALLOF(v));

    UF uf(n);
    int res = 0;
    int connected = 1;
    REP(i, m) {
        if (connected == n)
            break;
        if (uf.link(v[i].a, v[i].b))
            connected++;
        res >?= v[i].c;
    }

    cout << res << endl;

    return 0;
}
