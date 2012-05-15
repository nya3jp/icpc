#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <string>

using namespace std;

typedef vector< vector<int> > Field;
typedef pair<int,int> P;

const P nil = make_pair(-1, -1);

const int DIRS[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

inline bool in_range(int a, int l, int h) { return l <= a && a < h; }

P search(Field& field, P pos, P begin, int depth) {
    const int h = field.size();
    const int w = field[0].size();

    if (depth == 3)
        return nil;

    for(int dir = 0; dir < 4; dir++) {
        int di = DIRS[dir][0], dj = DIRS[dir][1];
        for(int l = 1; ; l++) {
            P p = make_pair(pos.first+di*l, pos.second+dj*l);
            if (!in_range(p.first, 0, h) || !in_range(p.second, 0, w))
                break;
            if (p != begin &&
                field[p.first][p.second] == field[begin.first][begin.second])
                return p;
            if (field[p.first][p.second] != 0)
                break;
            P result = search(field, p, begin, depth+1);
            if (result.first >= 0)
                return result;
        }
    }
    return nil;
}

pair<P,P> match(Field& field) {
    const int h = field.size();
    const int w = field[0].size();

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if (field[i][j] != 0) {
                P p = make_pair(i, j);
                P q = search(field, p, p, 0);
                if (q.first >= 0)
                    return make_pair(p, q);
            }
        }
    }

    return make_pair(nil, nil);
}

int main2() {

    string line;

    int w, h;
    if (!getline(cin, line))
        return 1;
    sscanf(line.c_str(), "%d%d", &w, &h);

    vector< vector<int> > field(h+2, vector<int>(w+2, 0));
    for(int i = 1; i <= h; i++) {
        getline(cin, line);
        for(int j = 1; j <= w; j++) {
            field[i][j] = (int)line[j-1];
        }
    }

    vector< pair<P,P> > steps;
    for(;;) {
        pair<P,P> p = match(field);
        if (p.first == nil)
            break;
        steps.push_back(p);
        field[p.first.first][p.first.second] = 0;
        field[p.second.first][p.second.second] = 0;
    }

    if (steps.size()*2 < w*h) {
        printf("No solution\n");
    }
    else {
        for(int i = 0; i < (int)steps.size(); i++) {
            P p = steps[i].first;
            P q = steps[i].second;
            printf("(%d,%d),(%d,%d)\n",
                   p.second, p.first, q.second, q.first);
        }
    }

    return 0;
}



int main() {
    while(main2() == 0);
    return 0;
}

