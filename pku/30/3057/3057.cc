#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

vector<string> field;

typedef pair<int,int> P;

int adj[100][100];


void solve() {
    int h, w;
    cin >> h >> w;
    cin >> ws;
    field.resize(h);
    REP(i, h)
        getline(cin, field[i]);

    vector<P> doors;
    for(int i = 1; i <= h-2; i++) {
        {
            int j = 0;
            if (field[i][j] == 'D')
                doors.push_back(P(i, j+1));
        }
        {
            int j = w-1;
            if (field[i][j] == 'D')
                doors.push_back(P(i, j-1));
        }
    }
    for(int j = 1; j <= w-2; j++) {
        {
            int i = 0;
            if (field[i][j] == 'D')
                doors.push_back(P(i+1, j));
        }
        {
            int i = h-1;
            if (field[i][j] == 'D')
                doors.push_back(P(i-1, j));
        }
    }

    REP(i, h) {
        field[i] = field[i].substr(1, w-2);
        field[i].resize(10, 'X');
    }
    field.erase(field.begin());
    field.pop_back();
    h--; w--;
    REP(i, doors.size())
        doors[i].first--, doors[i].second--;

    const int INF = 10000;
    REP(i, 9) REP(j, 9) {
        adj[i*10+j][(i+1)*10+j] = adj[(i+1)*10+j][i*10+j] =
            (field[i][j] == '.' && field[i+1][j] == '.' ? 1 : INF);
        adj[i*10+j][i*10+j+1] = adj[i*10+j+1][i*10+j] =
            (field[i][j] == '.' && field[i][j+1] == '.' ? 1 : INF);
    }

    REP(i, 100) REP(j, 100) REP(k, 100)
        adj[i][k] <?= adj[i][j] + adj[j][k];

    

}

int main() {
    int n;
    cin >> n;
    while(n-- > 0)
        solve();
    return 0;
}
