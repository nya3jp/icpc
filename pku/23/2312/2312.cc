#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

const int INF = 10000000;
int field[302][302];
int h, w;

typedef pair<int,int> place;

int main() {

    while(cin >> h >> w && !(h == 0 && w == 0)) {

        REP(i, h+2) REP(j, w+2)
            field[i][j] = INF;

        place you, target;

        REP(i, h) REP(j, w) {
            char c;
            cin >> c;
            int& cell = field[i+1][j+1];
            switch(c) {
            case 'E':
                cell = 1;
                break;
            case 'Y':
                cell = 1;
                you = place(i+1, j+1);
                break;
            case 'T':
                cell = 1;
                target = place(i+1, j+1);
                break;
            case 'S':
            case 'R':
                cell = INF;
                break;
            case 'B':
                cell = 2;
                break;
            }
        }

        typedef pair<int, place> node;
        priority_queue<node, vector<node>, greater<node> > q;
        q.push(node(0, you));

        map<place, int> costs;

        while(!q.empty()) {
            int cost = q.top().first;
            place here = q.top().second;
            q.pop();

            if (cost >= INF) {
                costs[target] = -1;
                break;
            }

            if (costs.count(here) == 0) {
                costs[here] = cost;
                if (here == target)
                    break;
                const int DIRS[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
                REP(dir, 4) {
                    place there(here.first+DIRS[dir][0], here.second+DIRS[dir][1]);
                    if (costs.count(there) == 0) {
                        q.push(node(cost + field[there.first][there.second], there));
                    }
                }
            }
        }

        cout << costs[target] << endl;

    }

    return 0;
}
