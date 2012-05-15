/*
 * UVA 10452 Marcus, help!
 * 2005-08-21
 * by nya
 */

#include <cstdio>
#include <vector>

#define MAX_HEIGHT 8
#define MAX_WIDTH  8

inline bool iehova(char c) {
    const char s[] = "IEHOVA@#";
    for(int i=0; i<sizeof(s)-1; i++) {
        if (c == s[i])
            return true;
    }
    return false;
}

int main() {
    int nCases;
    std::scanf("%d", &nCases);
    for(int iCase=0; iCase<nCases; iCase++) {
        int height, width;
        std::scanf("%d%d", &height, &width);

        bool field[MAX_HEIGHT][MAX_WIDTH];
        int goal, start;
        for(int y=0; y<height; y++) {
            for(int x=0; x<width; x++) {
                char c;
                std::scanf(" %c", &c);
                field[y][x] = iehova(c);
                if (c == '#')
                    goal = x;
                if (c == '@')
                    start = x;
            }
        }

        int _route[MAX_HEIGHT+1][MAX_WIDTH];
        int (*route)[MAX_WIDTH] = _route+1;
        for(int x=0; x<width; x++)
            route[-1][x] = (x == goal ? goal : -1);

        for(int y=0; y<height; y++) {
            for(int x=0; x<width; x++) {
                route[y][x] = -1;
            }
            for(int x=0; x<width; x++) {
                if (field[y][x] && route[y-1][x] != -1 && route[y][x] == -1) {
                    route[y][x] = x;
                    for(int i=x+1; i<width && field[y][i] && route[y][i] == -1; i++)
                        route[y][i] = x;
                    for(int i=x-1; i>=0 && field[y][i] && route[y][i] == -1; i--)
                        route[y][i] = x;
                }
            }
        }

        std::vector<const char*> v;
        {
            int pos = start;
            for(int y=height-1; y>=0; y--) {
                int next = route[y][pos];
                int delta = next - pos;
                if (delta > 0) {
                    for(int i=0; i<delta; i++)
                        v.push_back("right");
                }
                else if (delta < 0) {
                    for(int i=0; i>delta; i--)
                        v.push_back("left");
                }
                pos = next;
                if (y > 0)
                    v.push_back("forth");
            }
        }

        for(int i=0; i<(int)v.size(); i++) {
            if (i > 0)
                std::printf(" ");
            std::printf("%s", v[i]);
        }
        std::printf("\n");
    }
    return 0;
}
