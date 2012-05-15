#include <iostream>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define T 1000

bool cold[T][10][10];
bool reachable[T][10][10];
int h, w;

const int ADJ[2][7][2] = {
    {{1,0},{-1,0},{0,1},{0,-1},{1,-1},{-1,-1},{0,0}},
    {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{0,0}},
};

void precalc() {
    REP(t, T-1) {
        REP(i, h) REP(j, w) {
            int c = 0;
            REP(dir, 6) {
                int ii = i + ADJ[i%2][dir][0];
                int jj = j + ADJ[i%2][dir][1];
                if (0 <= ii && ii < h && 0 <= jj && jj < w)
                    if (cold[t][ii][jj])
                        c++;
            }
            if (!cold[t][i][j])
                cold[t+1][i][j] = (c == 3);
            else
                cold[t+1][i][j] = (c == 2 || c == 3);
        }
    }
}

int solve() {

    memset(reachable, 0, sizeof(reachable));

    queue< pair<int, pair<int,int> > > q;
    REP(j, w) {
        if (cold[0][0][j]) {
            reachable[0][0][j] = true;
            q.push(make_pair(0, make_pair(0, j)));
        }
    }

    while(!q.empty()) {
        int t = q.front().first;
        int i = q.front().second.first;
        int j = q.front().second.second;
        q.pop();
        REP(dir, 7) {
            int ii = i + ADJ[i%2][dir][0];
            int jj = j + ADJ[i%2][dir][1];
            if (0 <= ii && ii < h && 0 <= jj && jj < w && t+1 < T) {
                if (cold[t+1][ii][jj] && !reachable[t+1][ii][jj]) {
                    reachable[t+1][ii][jj] = true;
                    q.push(make_pair(t+1, make_pair(ii, jj)));
                }
            }
        }
    }

    REP(t, T) REP(j, w)
        if (reachable[t][h-1][j])
            return t+1;
    return -1;
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        cin >> h >> w;

        REP(i, h) {
            string row;
            cin >> row;
            REP(j, w)
                cold[0][i][j] = (row[j] == 'C');
        }

        precalc();

        int res = solve();
        
        if (res >= 0)
            cout << res << endl;
        else
            cout << "impossible" << endl;

    }

    return 0;
}



