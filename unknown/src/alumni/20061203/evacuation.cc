#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

#define cin fin

ifstream fin("f.in");

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 12
#define T 200

const int INF = 10000000;

struct BGM {
    int n, m;
    vector< vector<int> > g;
    vector<int> z;
    vector<bool> v;
    vector<bool> matched;
    int matches;

    BGM(int n, int m) : n(n), m(m), g(n), z(m, -1), matched(n, false), matches(0) {
    }

    void add_edge(int a, int b) {
        g[a].push_back(b);
    }

    bool augment(int a) {
        if (a < 0)
            return true;
        vector<int>& e = g[a];
        REP(i, e.size()) {
            int b = e[i];
            if (!v[b]) {
                v[b] = true;
                if (augment(z[b])) {
                    z[b] = a;
                    return true;
                }
            }
        }
        return false;
    }
    int match(int restricted_n) {
        REP(a, restricted_n) {
            if (matches == min(restricted_n, m))
                break;
            if (matched[a])
                continue;
            v.assign(m, false);
            if (augment(a)) {
                matched[a] = true;
                matches++;
            }
        }
        return matches;
    }
};

int adj[N*N][N*N];

void solve() {
    int height, width;
    cin >> height >> width;
    vector<string> field(height);
    REP(i, height)
        cin >> field[i];

#define ID(i, j) ((i)*width+(j))

    vector<int> door_ids;
    REP(j, width) {
        int i = 0;
        if (field[i][j] == 'D') {
            door_ids.push_back(ID(i, j));
            //printf("door at (%d,%d)\n", i, j);
        }
    }
    REP(j, width) {
        int i = height-1;
        if (field[i][j] == 'D') {
            door_ids.push_back(ID(i, j));
            //printf("door at (%d,%d)\n", i, j);
        }
    }
    REP(i, height) {
        int j = 0;
        if (field[i][j] == 'D') {
            door_ids.push_back(ID(i, j));
            //printf("door at (%d,%d)\n", i, j);
        }
    }
    REP(i, height) {
        int j = width-1;
        if (field[i][j] == 'D') {
            door_ids.push_back(ID(i, j));
            //printf("door at (%d,%d)\n", i, j);
        }
    }

    REP(i, width*height) REP(j, width*height)
        adj[i][j] = INF;

    REP(i, height-1) REP(j, width-1) {
        if (field[i][j] != 'X') {
            if (field[i+1][j] != 'X') {
                if (field[i][j] == 'D' && field[i+1][j] == 'D') {
                    // do nothing
                }
                else {
                    adj[ID(i, j)][ID(i+1, j)] = adj[ID(i+1, j)][ID(i, j)] = 1;
                    //printf("connect (%d,%d)-(%d,%d)\n", i, j, i+1, j);
                }
            }
            if (field[i][j+1] != 'X') {
                if (field[i][j] == 'D' && field[i][j+1] == 'D') {
                    // do nothing
                }
                else {
                    adj[ID(i, j)][ID(i, j+1)] = adj[ID(i, j+1)][ID(i, j)] = 1;
                    //printf("connect (%d,%d)-(%d,%d)\n", i, j, i, j+1);
                }
            }
        }
    }

    /*
    REP(i, width*height) {
        REP(j, width*height) {
            int d = adj[i][j];
            if (d == INF)
                printf("x ");
            else
                printf("%d ", d);
        }
        printf("\n");
    }
    */

    REP(j, width*height) REP(i, width*height) REP(k, width*height)
        adj[i][k] <?= adj[i][j] + adj[j][k];

    vector<int> person_ids;
    REP(i, height) REP(j, width)
        if (field[i][j] == '.')
            person_ids.push_back(ID(i, j));

    int nPersons = person_ids.size();
    int nDoors = door_ids.size();
    BGM bgm(T*nDoors, nPersons);

    REP(iPerson, nPersons) {
        int mindist = INF;
        //printf("> ");
        REP(iDoor, nDoors) {
            int dist = adj[person_ids[iPerson]][door_ids[iDoor]];
            //printf("%2d ", dist);
            for(int t = dist; t < T; t++)
                bgm.add_edge(t*nDoors+iDoor, iPerson);
            mindist <?= dist;
        }
        //printf("\n");
        if (mindist == INF) {
            cout << "impossible" << endl;
            return;
        }
    }

    for(int t = 1; t <= T; t++) {
        if (bgm.match(t*nDoors) == nPersons) {
            cout << t-1 << endl;
            return;
        }
    }

    assert(false);
}


int main() {

    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();

    return 0;
}
