/*
 * UVA 10426 Knight's Nightmare
 * 2005-07-16
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
#include <string>

#define MAX_SIZE 16
#define INF 10000

const int KNIGHT_MOVES[8][2] = {
    {+2, +1},
    {+1, +2},
    {-1, +2},
    {-2, +1},
    {-2, -1},
    {-1, -2},
    {+1, -2},
    {+2, -1},
};

typedef std::pair<int,int> Point;
typedef int Map[MAX_SIZE][MAX_SIZE];

void dijkstra(Map& m, int nRows, int nCols, const Point& hero, const Point& monster) {
    for(int i=0; i<nRows; i++) {
        for(int j=0; j<nCols; j++) {
            m[i][j] = INF;
        }
    }

    /*
    std::priority_queue< std::pair<int, Point> > q;
    q.push( std::make_pair(0, hero) );

    while(! q.empty()) {

        int d = -q.top().first;
        Point pos = q.top().second;
        q.pop();

        if (0 <= pos.first && pos.first < nRows &&
            0 <= pos.second && pos.second < nCols &&
            pos != monster &&
            m[pos.first][pos.second] == INF) {

            m[pos.first][pos.second] = d;

            for(int dir=0; dir<8; dir++) {
                Point next = pos;
                next.first += KNIGHT_MOVES[dir][0];
                next.second += KNIGHT_MOVES[dir][1];

                q.push( std::make_pair( -d-1, next ) );
            }

        }

    }
    */

    m[hero.first][hero.second] = 0;
    bool success = true;
    for(int d=0; success; d++) {
        success = false;
        for(int i=0; i<nRows; i++) {
            for(int j=0; j<nCols; j++) {
                Point pos = std::make_pair(i, j);
                if (m[pos.first][pos.second] == d) {
                    for(int dir=0; dir<8; dir++) {
                        Point next = pos;
                        next.first += KNIGHT_MOVES[dir][0];
                        next.second += KNIGHT_MOVES[dir][1];
                        if (0 <= next.first && next.first < nRows &&
                            0 <= next.second && next.second < nCols &&
                            next != monster &&
                            m[next.first][next.second] == INF) {
                            m[next.first][next.second] = d+1;
                            success = true;
                        }
                    }
                }
            }
        }
    }

}

int main() {

    std::string casename;
    while(std::cin >> casename) {

        int nRows, nCols;
        std::cin >> nRows >> nCols;

        Point heroes[4];
        for(int i=0; i<4; i++) {
            std::cin >> heroes[i].first >> heroes[i].second;
            heroes[i].first--; heroes[i].second--;
        }

        Point monster;
        std::cin >> monster.first >> monster.second;
        monster.first--; monster.second--;

        Map safes[4];
        for(int i=0; i<4; i++) {
            dijkstra(safes[i], nRows, nCols, heroes[i], monster);
        }
        Map pinches[4];
        for(int i=0; i<4; i++) {
            dijkstra(pinches[i], nRows, nCols, heroes[i], std::make_pair(-1, -1));
        }

        int best = INF;
        for(int e=0; e<4; e++) {
            for(int i=0; i<nRows; i++) {
                for(int j=0; j<nCols; j++) {
                    int t = 0;
                    for(int k=0; k<4; k++) {
                        t += (k == e ? pinches[k][i][j] : safes[k][i][j]);
                    }
                    best = std::min(best, t);
                }
            }
        }

        std::cout << casename << std::endl;
        if (best < INF)
            std::cout << "Minimum time required is " << best << " minutes." << std::endl;
        else
            std::cout << "Meeting is impossible." << std::endl;
    }

    return 0;
}
