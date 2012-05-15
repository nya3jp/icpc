/*
 * UVA 758 The Same Game
 * 2005-08-08
 * by nya
 */

#include <iostream>
#include <map>
#include <algorithm>
#include <utility>

struct Field {
    int field[10][15];

    int count_all() const {
        int n = 0;
        for(int y=0; y<10; y++) {
            for(int x=0; x<15; x++) {
                if (field[y][x] != 0)
                    n++;
            }
        }
        return n;
    }
    int count(int x, int y) const {
        bool visited[10][15];
        for(int yy=0; yy<10; yy++) {
            for(int xx=0; xx<15; xx++) {
                visited[yy][xx] = (field[yy][xx] != field[y][x]);
            }
        }
        return count_sub(x, y, visited);
    }
    int count_sub(int x, int y, bool (&visited)[10][15]) const {
        int n = 1;
        int c = field[y][x];
        visited[y][x] = true;
        if (x-1 >= 0 && field[y][x-1] == c && !visited[y][x-1])
            n += count_sub(x-1, y, visited);
        if (y-1 >= 0 && field[y-1][x] == c && !visited[y-1][x])
            n += count_sub(x, y-1, visited);
        if (x+1 < 15 && field[y][x+1] == c && !visited[y][x+1])
            n += count_sub(x+1, y, visited);
        if (y+1 < 10 && field[y+1][x] == c && !visited[y+1][x])
            n += count_sub(x, y+1, visited);
        return n;
    }
    void erase(int x, int y) {
        int c = field[y][x];
        field[y][x] = 0;
        if (x-1 >= 0 && field[y][x-1] == c)
            erase(x-1, y);
        if (y-1 >= 0 && field[y-1][x] == c)
            erase(x, y-1);
        if (x+1 < 15 && field[y][x+1] == c)
            erase(x+1, y);
        if (y+1 < 10 && field[y+1][x] == c)
            erase(x, y+1);
    }
    void compress() {
        for(int x=0; x<15; x++) {
            int ny=0;
            for(int y=0; y<10; y++) {
                if (field[y][x] != 0) {
                    field[ny][x] = field[y][x];
                    ny++;
                }
            }
            while(ny < 10) {
                field[ny++][x] = 0;
            }
        }
        {
            int nx = 0;
            for(int x=0; x<15; x++) {
                if (field[0][x] != 0) {
                    for(int y=0; y<10; y++) {
                        field[y][nx] = field[y][x];
                    }
                    nx++;
                }
            }
            while(nx < 15) {
                for(int y=0; y<10; y++) {
                    field[y][nx] = 0;
                }
                nx++;
            }
        }
    }
    int max() const {
        std::map<int,int> m;
        for(int y=0; y<10; y++) {
            for(int x=0; x<15; x++) {
                m[field[y][x]]++;
            }
        }
        m.erase(0);
        int x=0;
        for(std::map<int,int>::const_iterator it = m.begin(); it != m.end(); ++it) {
            x = std::max(x, it->second);
        }
        return x;
    }
    std::pair<std::pair<int,int>, int> find_next() const {
        bool visited[10][15];
        for(int yy=0; yy<10; yy++)
            for(int xx=0; xx<15; xx++)
                visited[yy][xx] = false;
        int best = 0;
        std::pair<int,int> pos;
        for(int x=0; x<15; x++) {
            for(int y=0; y<10; y++) {
                if (field[y][x] != 0 && !visited[y][x]) {
                    int n = count_sub(x, y, visited);
                    if (n > best) {
                        best = n;
                        pos = std::make_pair(x, y);
                    }
                }
            }
        }
        return std::make_pair(pos, best);
    }
};


int main() {

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        Field field;
        for(int y=9; y>=0; y--) {
            for(int x=0; x<15; x++) {
                char c;
                std::cin >> c;
                field.field[y][x] = (int)c;
            }
        }

        if (iCase > 0)
            std::cout << std::endl;
        std::cout << "Game " << (iCase+1) << ":" << std::endl << std::endl;

        int iRound = 0;
        int score = 0;
        while(true) {
            std::pair<std::pair<int,int>, int> next = field.find_next();
            std::pair<int,int> pos = next.first;
            int n = next.second;
            if (n < 2)
                break;
            int pt = (n-2)*(n-2);
            std::cout << "Move " << (iRound+1)
                      << " at (" << (pos.second+1) << "," << (pos.first+1)
                      << "): removed " << n << " balls of color "
                      << (char)(field.field[pos.second][pos.first])
                      << ", got " << pt << " points." << std::endl;
            field.erase(pos.first, pos.second);
            field.compress();
            score += pt;
            iRound++;
        }

        if (field.max() == 0)
            score += 1000;

        std::cout << "Final score: " << score << ", with " << field.count_all() << " balls remaining." << std::endl;

    }

    return 0;
}

