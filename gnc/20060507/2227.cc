#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <limits>

using namespace std;


int fill0(const vector< vector<int> >& v, vector< vector<int> >& f, int w, int h, int i, int j) {
    if (f[i][j] >= 0)
        return f[i][j];
    if (f[i][j] == -2)
        return -1;
    f[i][j] = -2;
    int m = numeric_limits<int>::max();
    for(int di = -1; di <= 1; di++) {
        for(int dj = -1; dj <= 1; dj++) {
            if (di*dj == 0 && !(di == 0 && dj == 0)) {
                int ii = i+di;
                int jj = j+dj;
                if (!(ii >= 0 && ii < h && jj >= 0 && j < w)) {
                    m = v[i][j];
                    goto OUT;
                }
                int r = fill0(v, f, w, h, ii, jj);
                if (r >= 0)
                    m = min(m, r);
            }
        }
    }
OUT:
    printf("(%d,%d) -> %d\n", i, j, m);
    f[i][j] = m;
    return m;
}

void fill_(const vector< vector<int> >& v, vector< vector<int> >& f, int w, int h) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            fill0(v, f, w, h, i, j);
        }
    }
}

struct UF {
    vector<int> data;
    const int n;

    UF(int n) : data(n, -1), n(n) {
    }
    bool link(int a, int b) {
        int ra = find_root(a);
        int rb = find_root(b);
        if (ra != rb) {
            if (data[rb] < data[ra])
                swap(ra, rb);
            data[ra] += data[rb];
            data[rb] = ra;
        }
        return (ra != rb);
    }
    bool check(int a, int b) {
        return (find_root(a) == find_root(b));
    }

    int find_root(int a) {
        return ((data[a] < 0) ? a : (data[a] = find_root(data[a])));
    }
};

void fill(const vector< vector<int> >& v, vector< vector<int> >& f, int w, int h) {
    /*
    for(int i = 0; i < h; i++) {
        f[i][0] = v[i][0];
        f[i][w-1] = v[i][w-1];
    }
    for(int j = 0; j < w; j++) {
        f[0][j] = v[0][j];
        f[h-1][j] = v[h-1][j];
    }
    */

    typedef pair<int, pair<int,int> > K;
    priority_queue<K, vector<K>, greater<K> > qq;

    UF uf(w*h);

    for(int i = 0; i < h; i++) {
        uf.link(i*w+0, 0);
        uf.link(i*w+w-1, 0);
    }
    for(int j = 0; j < w; j++) {
        uf.link(0*w+j, 0);
        uf.link((h-1)*w+j, 0);
    }

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            qq.push(make_pair(v[i][j], make_pair(i, j)));
        }
    }
    while(!qq.empty()) {
        int i = qq.top().second.first;
        int j = qq.top().second.second;
        qq.pop();
        f[i][j] = -2;
        for(int di = -1; di <= 1; di++) {
            for(int dj = -1; dj <= 1; dj++) {
                if (di*dj == 0 && !(di == 0 && dj == 0)) {
                    int ii = i+di;
                    int jj = j+dj;
                    if (ii >= 0 && ii < h && jj >= 0 && jj < w ) {
                        if (f[ii][jj] == -2) {
                            uf.link(i*w+j, ii*w+jj);
                        }
                    }
                }
            }
        }
        if (uf.check(i*w+j, 0)) {
            int m = v[i][j];
            for(int ii=0; ii<h; ii++){
                for(int jj=0; jj<w; jj++) {
                    if (f[ii][jj] == -2) {
                        f[ii][jj] = m;
                    }
                }
            }
        }
    }
}
/*
int hoge() {
    while(!qq.empty()) {
        int i = qq.top().second.first;
        int j = qq.top().second.second;
        qq.pop();
        if (f[i][j] < 0) {
            printf("(%d,%d) %d:\n", i, j, v[i][j]);
            priority_queue<K, vector<K>, greater<K> > q;
            set< pair<int,int> > s;
            q.push(make_pair(v[i][j], make_pair(i, j)));
            int m = numeric_limits<int>::max();
            while(!q.empty()) {
                if (q.top().first > m)
                    break;
                int ii = q.top().second.first;
                int jj = q.top().second.second;
                q.pop();
                if (s.insert(make_pair(ii, jj)).second) {
                    printf("\t(%d,%d) %d\n", ii, jj, v[ii][jj]);
                    for(int di = -1; di <= 1; di++) {
                        for(int dj = -1; dj <= 1; dj++) {
                            if (di*dj == 0 && !(di == 0 && dj == 0)) {
                                int iii = ii+di;
                                int jjj = jj+dj;
                                if (iii >= 0 && iii < h && jjj >= 0 && jjj < w && f[iii][jjj] < 0) {
                                    q.push(make_pair(v[iii][jjj], make_pair(iii, jjj)));
                                }
                                else {
                                    // flaw
                                    printf("\t\tflowed at (%d,%d)\n", iii, jjj);
                                    m = v[ii][jj];
                                }
                            }
                        }
                    }
                }
            }
            printf("\t\t-> filled with %d\n", m);
            for(set< pair<int,int> >::iterator it = s.begin(); it != s.end(); ++it) {
                f[it->first][it->second] = m;
            }
        }
    }
}
*/

int main() {
    int w, h;
    scanf("%d%d", &w, &h);
    vector< vector<int> > v(h, vector<int>(w));
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            scanf("%d", &v[i][j]);
        }
    }
    vector< vector<int> > f(h, vector<int>(w, -1));
    fill(v, f, w, h);
    long long int r = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            printf("%d/%d ", f[i][j], v[i][j]);
            r += (long long int)(f[i][j] - v[i][j]);
        }
        printf("\n");
    }
    cout << r << endl;

    return 0;
}
