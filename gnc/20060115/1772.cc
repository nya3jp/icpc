#include <cstdio>
#include <cassert>

inline bool in_range(int x, int l, int h) {
    return (l <= x && x < h);
}

enum State { Undetermined, Stone, Empty, Outside };

typedef State Map[15][15];

int verts[15];
int horzs[15];
int poss[30];
int negs[30];

inline bool horz_sum_check(int y, int x, Map& map, int n) {
    int id = y;
    int rem = n-x;
    int s = 0;
    for(int i=-n; i<=n; i++) {
        int ax = x+i;
        int ay = y;
        if (in_range(ax, 0, n) && in_range(ay, 0, n)) {
            s += (map[ay][ax] == Stone ? 1 : 0);
        }
    }
    return (horzs[id]-rem <= s && s <= horzs[id]);
}
inline bool vert_sum_check(int y, int x, Map& map, int n) {
    int id = x;
    int rem = n-y;
    int s = 0;
    for(int i=-n; i<=n; i++) {
        int ax = x;
        int ay = y+i;
        if (in_range(ax, 0, n) && in_range(ay, 0, n)) {
            s += (map[ay][ax] == Stone ? 1 : 0);
        }
    }
    return (verts[id]-rem <= s && s <= verts[id]);
}
inline bool pos_sum_check(int y, int x, Map& map, int n) {
    int id = x+y;
    int rem = x;
    int s = 0;
    for(int i=-n; i<=n; i++) {
        int ax = x-i;
        int ay = y+i;
        if (in_range(ax, 0, n) && in_range(ay, 0, n)) {
            s += (map[ay][ax] == Stone ? 1 : 0);
        }
    }
    return (poss[id]-rem <= s && s <= poss[id]);
}
inline bool neg_sum_check(int y, int x, Map& map, int n) {
    int id = x-y+n-1;
    int rem = n-1-y;
    int s = 0;
    for(int i=-n; i<=n; i++) {
        int ax = x+i;
        int ay = y+i;
        if (in_range(ax, 0, n) && in_range(ay, 0, n)) {
            s += (map[ay][ax] == Stone ? 1 : 0);
        }
    }
    return (negs[id]-rem <= s && s <= negs[id]);
}

inline bool check(int y, int x, Map& map, int n) {
    if (!pos_sum_check(y, x, map, n))
        return false;
    if (!neg_sum_check(y, x, map, n))
        return false;
    if (!horz_sum_check(y, x, map, n))
        return false;
    if (!vert_sum_check(y, x, map, n))
        return false;
    if (!pos_sum_check(y, x, map, n))
        return false;
    return true;
}

void search(int y, int x, Map& map, int n);
inline void searchnext(int y, int x, Map& map, int n) {
    if (check(y, x, map, n)) {
        x++;
        if (x == n) {
            x = 0;
            y++;
        }
        if (y == n)
            search(-1, -1, map, n);
        else
            search(y, x, map, n);
    }
}

struct Found {};

void search(int y, int x, Map& map, int n) {
    if (y == -1) {
        throw Found();
    }
    if (map[y][x] != Undetermined) {
        searchnext(y, x, map, n);
    }
    else {
        //std::printf("(%d,%d)->\n", x, y);
        map[y][x] = Stone;
        searchnext(y, x, map, n);
        map[y][x] = Empty;
        searchnext(y, x, map, n);
        map[y][x] = Undetermined;
        //std::printf("<-(%d,%d)\n", x, y);
    }
}

void paint(int y, int x, Map& map, int n) {
    if (map[y][x] == Empty) {
        map[y][x] = Outside;
        if (x-1 >= 0)
            paint(y, x-1, map, n);
        if (y-1 >= 0)
            paint(y-1, x, map, n);
        if (x+1 < n)
            paint(y, x+1, map, n);
        if (y+1 < n)
            paint(y+1, x, map, n);
    }
}

int count(Map& map, int n) {
    for(int i=0; i<n; i++) {
        paint(i, 0, map, n);
        paint(i, n-1, map, n);
        paint(0, i, map, n);
        paint(n-1, i, map, n);
    }
    int s = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if (map[i][j] == Empty)
                s++;
    return s;
}

int main() {
    int n;
    while(std::scanf("%d", &n), n != 0) {
        //std::printf("n=%d\n", n);
        for(int i=0; i<n; i++)
            std::scanf("%d", &horzs[i]);
        for(int i=0; i<n; i++)
            std::scanf("%d", &verts[i]);
        for(int i=0; i<2*n-1; i++)
            std::scanf("%d", &poss[i]);
        for(int i=0; i<2*n-1; i++)
            std::scanf("%d", &negs[i]);
        Map map;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                map[i][j] = Undetermined;
        try {
            search(0, 0, map, n);
            std::printf("not found\n");
        } catch(Found) {
            /*
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    std::printf("%c", (map[i][j] == Stone ? 'X' : '.'));
                }
                std::printf("\n");
            }
            */
            std::printf("%d\n", count(map, n));
        }
    }
    return 0;
}
