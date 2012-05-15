#include <iostream>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 32

#define PAD(x) ((((x)/n/m%k+1)*(m+2)+((x)/n%m+1))*(n+2)+((x)%n+1))

const int ADJ[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

int find_root(int a, vector<int>& uf) {
    return (uf[a] < 0 ? a : (uf[a] = find_root(uf[a], uf)));
}

void unify(int a, int b, vector<int>& uf) {
    int ra, rb;
    ra = find_root(a, uf);
    rb = find_root(b, uf);
    if (ra != rb) {
        if (uf[ra] > uf[rb])
            swap(ra, rb);
        uf[ra] += uf[rb];
        uf[rb] = ra;
    }
}

void solve() {

    int n, m, k;
    int nParts;
    cin >> n >> m >> k >> nParts;

    vector< vector<int> > parts(nParts);

    REP(iPart, nParts) {
        int size;
        scanf("%d", &size);
        vector<int>& part = parts[iPart];
        part.reserve(size);
        REP(i, size) {
            int x;
            scanf("%d", &x);
            part.push_back(PAD(x));
        }
    }

    n += 2;
    m += 2;
    k += 2;

    vector<int> uf(n*m*k, -1);
    vector<bool> occupied(n*m*k, false);

    int res = 0;
    int total = 0;
    for(int t = nParts-1; t >= 0; t--) {

        vector<int>& part = parts[t];

        REP(i, part.size())
            occupied[part[i]] = true;

        REP(i, part.size()) {
            int here = part[i];
            REP(dir, 6) {
                int there = part[i] + ADJ[dir][0]*n*m + ADJ[dir][1]*n + ADJ[dir][2];
                if (occupied[there])
                    unify(here, there, uf);
            }
        }

        total += part.size();

        int root = find_root(part[0], uf);

        if (-uf[root] != total)
            res++;

    }

    cout << res << endl;
}



int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases)
        solve();

    return 0;
}


