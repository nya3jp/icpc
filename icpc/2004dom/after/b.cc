#include <iostream>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

const int adj[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

void dfs(vector<string>& field, int i, int j) {
    if (field[i][j] == '.') {
        field[i][j] = '*';
        REP(dir, 4) {
            int di = adj[dir][0], dj = adj[dir][1];
            int ii = i + di, jj = j + dj;
            dfs(field, ii, jj);
        }
    }
}


int main() {

    for(;;) {
        int w, h;
        cin >> w >> h;
        if (w == 0 && h == 0)
            break;

        vector<string> field(h);
        REP(i, h)
            cin >> field[i];

        REP(i, h)
            field[i] = string("#") + field[i] + string("#");
        field.insert(field.begin(), string(w+2, '#'));
        field.insert(field.end(), string(w+2, '#'));

        w += 2; h += 2;

        int si, sj;
        REP(i, h) REP(j, w)
            if (field[i][j] == '@')
                si = i, sj = j;
        field[si][sj] = '.';

        dfs(field, si, sj);

        int res = 0;
        REP(i, h)
            res += count(ALLOF(field[i]), '*');

        cout << res << endl;

    }

    return 0;
}

