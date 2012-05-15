#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

#define N 300

const int INF = numeric_limits<int>::max();

int field[N][N];
int level[N][N];
int width, height;


void spill() {

    typedef pair<int, pair<int,int> > K;
    priority_queue<K, vector<K>, greater<K> > q;

    for(int x = 0; x < width; x++) {
        q.push(make_pair(0, make_pair(x, 0)));
        q.push(make_pair(0, make_pair(x, height-1)));
    }
    for(int y = 0; y < height; y++) {
        q.push(make_pair(0, make_pair(0, y)));
        q.push(make_pair(0, make_pair(width-1, y)));
    }

    while(!q.empty()) {
        int h = q.top().first;
        int x = q.top().second.first;
        int y = q.top().second.second;
        q.pop();

        if (level[y][x] != INF)
            continue;

        h = max(h, field[y][x]);
        level[y][x] = h;

        {
            int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
            for(int i = 0; i < 4; i++) {
                int xx = x + DIR[i][0];
                int yy = y + DIR[i][1];
                if (0 <= xx && xx < width && 0 <= yy && yy < height)
                    if (level[yy][xx] == INF)
                        q.push(make_pair(h, make_pair(xx, yy)));
            }
        }
    }
}

int main() {

    scanf("%d%d", &width, &height);

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            scanf("%d", &field[y][x]);

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            level[y][x] = INF;

    spill();

    long long int total = 0;
    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            total += (long long int)(level[y][x] - field[y][x]);

    cout << total << endl;

    return 0;
}


