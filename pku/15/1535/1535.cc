#include <cstdio>
#include <utility>
#include <stack>

using namespace std;


#define N 100

int field[N][N];




int main() {
    int h, w;
    while(scanf("%d%d", &h, &w), !(h == 0 && w == 0)) {
        int ay, ax, by, bx;
        scanf("%d%d%d%d", &ay, &ax, &by, &bx);
        int n;
        scanf("%d", &n);

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                field[i][j] = ((i < h && j < w) ? 0 : 1);

        for(int i = 0; i < n; i++) {
            int y, x;
            scanf("%d%d", &y, &x);
            field[y][x] = 1;
        }

        /*
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++)
                printf("%c", (field[i][j] == 1 ? '#' : '.'));
            printf("\n");
        }
        */

        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                int k = by - (i - ay);
                int l = bx - (j - ax);
                int op = 1;
                if (0 <= k && k < h && 0 <= l && l < w)
                    op = field[k][l];
                field[i][j] |= op;
            }
        }

        /*
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++)
                printf("%c", (field[i][j] == 1 ? '#' : '.'));
            printf("\n");
        }
        */

        stack< pair<int,int> > s;
        s.push(make_pair(ay, ax));
        while(!s.empty()) {
            int y = s.top().first;
            int x = s.top().second;
            if (y == by && x == bx)
                break;
            //printf("(%d,%d)\n", y, x);
            s.pop();
            for(int dy = -1; dy <= 1; dy++) {
                for(int dx = -1; dx <= 1; dx++) {
                    if (dx*dy == 0 && dx+dy != 0) {
                        int k = y+dy;
                        int l = x+dx;
                        if (0 <= k && k < h && 0 <= l && l < w) {
                            if ((field[k][l] & 3) == 0) {
                                field[k][l] |= 2;
                                s.push(make_pair(k, l));
                            }
                        }
                    }
                }
            }
        }

        printf("%s\n", (s.empty()) ? "NO" : "YES");

    }
    return 0;
}


