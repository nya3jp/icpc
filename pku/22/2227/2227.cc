#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define H 302
#define W 302

int h, w;
int field[H][W];
bool visited[H][W];

int main() {

    scanf("%d%d", &w, &h);

    memset(field, 0, sizeof(field));
    REP(i, h) REP(j, w)
        scanf("%d", &field[i+1][j+1]);

    memset(visited, 0, sizeof(visited));
    REP(i, h+2)
        visited[i][0] = visited[i][w+1] = true;
    REP(j, w+2)
        visited[0][j] = visited[h+1][j] = true;

    priority_queue< pair<int, pair<int,int> > > q;
    REP(i, h-1) {
        {
            int ii = i + 1;
            int jj = 1;
            q.push(make_pair(-field[ii][jj], make_pair(ii, jj)));
        }
        {
            int ii = h - i;
            int jj = w;
            q.push(make_pair(-field[ii][jj], make_pair(ii, jj)));
        }
    }
    REP(j, w-1) {
        {
            int ii = 1;
            int jj = w - j;
            q.push(make_pair(-field[ii][jj], make_pair(ii, jj)));
        }
        {
            int ii = h;
            int jj = j + 1;
            q.push(make_pair(-field[ii][jj], make_pair(ii, jj)));
        }
    }


    long long int res = 0;

    while(!q.empty()) {
        int ch = -q.top().first;
        int ci = q.top().second.first;
        int cj = q.top().second.second;
        q.pop();
        if (visited[ci][cj])
            continue;
        visited[ci][cj] = true;
        res += (ch - field[ci][cj]);
        const int ADJ[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        REP(dir, 4) {
            int di = ci + ADJ[dir][0];
            int dj = cj + ADJ[dir][1];
            int dh = max(ch, field[di][dj]);
            if (!visited[di][dj])
                q.push(make_pair(-dh, make_pair(di, dj)));
        }
    }

    cout << res << endl;

    return 0;
}
