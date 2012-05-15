/*
 * UVA 10415 Eb Alto Saxophone Player
 * 2005-08-11
 * by nya
 */

#include <cstdio>

const bool PRESSES[15][10] = {
    {0,1,1,1,0,0,1,1,1,1},
    {0,1,1,1,0,0,1,1,1,0},
    {0,1,1,1,0,0,1,1,0,0},
    {0,1,1,1,0,0,1,0,0,0},
    {0,1,1,1,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0},
    {1,1,1,1,0,0,1,1,1,0},
    {1,1,1,1,0,0,1,1,0,0},
    {1,1,1,1,0,0,1,0,0,0},
    {1,1,1,1,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
};

int main() {
    char buf[256];
    int n;
    std::fgets(buf, sizeof(buf), stdin);
    std::sscanf(buf, "%d", &n);
    for(int i=0; i<n; i++) {
        int counts[10];
        for(int j=0; j<10; j++)
            counts[j] = 0;
        std::fgets(buf, sizeof(buf), stdin);
        char* p = buf;
        int prev = 14;
        while(true) {
            char c = *p++;
            int next = -1;
            if ('c' <= c && c <= 'g')
                next = c - 'c';
            if ('a' <= c && c <= 'b')
                next = c - 'a' + 5;
            if ('C' <= c && c <= 'G')
                next = c - 'C' + 7;
            if ('A' <= c && c <= 'B')
                next = c - 'A' + 12;
            if (next < 0)
                break;
            for(int j=0; j<10; j++) {
                if (PRESSES[prev][j] == 0 && PRESSES[next][j] == 1)
                    counts[j]++;
            }
            prev = next;
        }
        for(int j=0; j<10; j++) {
            if (j > 0)
                std::printf(" ");
            std::printf("%d", counts[j]);
        }
        std::printf("\n");
    }
    return 0;
}

