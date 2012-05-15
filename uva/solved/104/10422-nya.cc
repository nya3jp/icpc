/*
 * UVA 10422 Knights in FEN
 * 2005-07-16
 * by nya
 */

#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#define DEPTH_MEM 6
#define DEPTH_DFS 4
#define DEPTH_MAX (DEPTH_MEM+DEPTH_DFS)

enum State {
    Empty,
    White,
    Black
};

struct Map {
    State data[5][5];
};

typedef std::pair<int,int> Point;

int DIR[8][2] = {
    {+2, +1},
    {+1, +2},
    {-1, +2},
    {-2, +1},
    {-2, -1},
    {-1, -2},
    {+1, -2},
    {+2, -1},
};

bool operator<(const Map& a, const Map& b) {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            if (a.data[i][j] != b.data[i][j])
                return (a.data[i][j] < b.data[i][j]);
        }
    }
    return false;
}

std::map<Map, int> mem;


void make_mem(Map& m, const Point& pos, int depth) {
    std::map<Map,int>::iterator it = mem.find(m);
    bool deepen = true;
    if (it == mem.end()) {
        mem.insert(std::make_pair(m, depth));
    }
    else {
        if (depth < it->second)
            it->second = depth;
        else
            deepen = false;
    }
    if (deepen && depth < DEPTH_MEM) {
        for(int d=0; d<8; d++) {
            Point next = pos;
            next.first += DIR[d][0];
            next.second += DIR[d][1];
            if (0 <= pos.first && pos.first < 5 && 0 <= pos.second && pos.second < 5) {
                std::swap(m.data[pos.first][pos.second], m.data[next.first][next.second]);
                make_mem(m, next, depth+1);
                std::swap(m.data[pos.first][pos.second], m.data[next.first][next.second]);
            }
        }
    }
}


int search(Map& m, const Point& pos, int depth) {
    int best = DEPTH_MAX+1;
    std::map<Map,int>::iterator it = mem.find(m);
    if (it != mem.end()) {
        best = depth + it->second;
    }
    else if (depth < DEPTH_DFS) {
        for(int d=0; d<8; d++) {
            Point next = pos;
            next.first += DIR[d][0];
            next.second += DIR[d][1];
            if (0 <= pos.first && pos.first < 5 && 0 <= pos.second && pos.second < 5) {
                std::swap(m.data[pos.first][pos.second], m.data[next.first][next.second]);
                int res = search(m, next, depth+1);
                best = std::min(best, res);
                std::swap(m.data[pos.first][pos.second], m.data[next.first][next.second]);
            }
        }
    }

    return best;
}


int main() {

    {
        Map goal;
        int bound[5] = {0, 1, 3, 4, 5};
        for(int i=0; i<5; i++) {
            for(int j=0; j<5; j++) {
                goal.data[i][j] = (j < bound[i] ? White : Black);
            }
        }
        goal.data[2][2] = Empty;
        make_mem(goal, std::make_pair(2, 2), 0);
    }

    char buf[64];
    std::fgets(buf, sizeof(buf), stdin);
    int nCases;
    std::sscanf(buf, "%d", &nCases);

    for(int iCase=0; iCase<nCases; iCase++) {

        Map init;
        Point pos;

        for(int i=0; i<5; i++) {
            std::fgets(buf, sizeof(buf), stdin);
            for(int j=0; j<5; j++) {
                char c = buf[j];
                init.data[i][j] = ( c == ' ' ? Empty : c == '0' ? White : Black );
                if (init.data[i][j] == Empty)
                    pos = std::make_pair(i, j);
            }
        }

        int best = search(init, pos, 0);

        if (best <= DEPTH_MAX)
            std::printf("Solvable in %d move(s).\n", best);
        else
            std::printf("Unsolvable in less than 11 move(s).\n");

    }

    return 0;
}
