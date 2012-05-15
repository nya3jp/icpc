#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class Sim {
private:
    const int width, height;
    vector< vector<char> > v;

public:
    Sim(int width, int height)
        : width(width), height(height), v(width, vector<char>(height, ' ')) {
    }
    void point(int x, int y) {
        plot(x, y, 'o');
    }
    void text(int x, int y, const char* txt) {
        int len = strlen(txt);
        for(int i = 0; i < len; i++)
            plot(x+i, y, txt[i]);
    }
    void line(int x1, int y1, int x2, int y2) {
        if (x2 < x1) {
            swap(x1, x2);
            swap(y1, y2);
        }
        if (x1 == x2) {
            if (y1 > y2)
                swap(y1, y2);
            for(int y = y1; y <= y2; y++)
                plot(x1, y, '|');
        }
        else if (y1 == y2) {
            if (x1 > x2)
                swap(x1, x2);
            for(int x = x1; x <= x2; x++)
                plot(x, y1, '-');
        }
        else if (y1 < y2) {
            for(int i = 0; i <= (x2 - x1); i++)
                plot(x1+i, y1+i, '\\');
        }
        else {
            for(int i = 0; i <= (x2 - x1); i++)
                plot(x1+i, y1-i, '/');
        }
    }
    void clear(int x1, int y1, int x2, int y2) {
        if (x2 < x1)
            swap(x1, x2);
        if (y2 < y1)
            swap(y1, y2);
        for(int x = x1; x <= x2; x++)
            for(int y = y1; y <= y2; y++)
                plot(x, y, ' ');
    }
    void print() {
        printf("+");
        for(int i = 0; i < width; i++)
            printf("-");
        printf("+\n");
        for(int y = 0; y < height; y++) {
            printf("|");
            for(int x = 0; x < width; x++) {
                printf("%c", v[x][y]);
            }
            printf("|\n");
        }
        printf("+");
        for(int i = 0; i < width; i++)
            printf("-");
        printf("+\n");
    }
private:
    void plot(int x, int y, char c) {
        if (1 <= x && x <= width && 1 <= y && y <= height) {
            char& o = v[x-1][y-1];
            if (o == ' ')
                o = c;
            else if (o == c)
                ;// do nothing
            else if ((o == '-' && c == '|') || (o == '|' && c == '-') || (o == '+' && (c == '-' || c == '|')))
                o = '+';
            else if ((o == '/' && c == '\\') || (o == '\\' && c == '/') || (o == 'x' && (c == '/' || c == '\\')))
                o = 'x';
            else if (c == ' ')
                o = ' ';
            else
                o = '*';
        }
    }
};

int main() {

    int width, height;
    while(scanf("%d%d", &width, &height), !(width == 0 && height == 0)) {
        Sim sim(width, height);
        while(true) {
            char cmd[32];
            scanf("%s", cmd);
            if (strcmp(cmd, "POINT") == 0) {
                int x, y;
                scanf("%d%d", &x, &y);
                sim.point(x, y);
            }
            if (strcmp(cmd, "TEXT") == 0) {
                int x, y;
                char txt[4096];
                scanf("%d%d%s", &x, &y, txt);
                sim.text(x, y, txt);
            }
            if (strcmp(cmd, "LINE") == 0) {
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                sim.line(x1, y1, x2, y2);
            }
            if (strcmp(cmd, "CLEAR") == 0) {
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                sim.clear(x1, y1, x2, y2);
            }
            if (strcmp(cmd, "PRINT") == 0) {
                sim.print();
                printf("\n");
                break;
            }
        }
    }


    return 0;
}

