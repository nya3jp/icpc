#include <cstdio>
#include <limits>
#include <algorithm>

using namespace std;

int store[100][100][100];

int main() {
    int v[100][100];
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &v[i][j]);
        }
    }

    // make table
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int s = 0;
            for(int w = 1; w <= n-j; w++) {
                s += v[i][j+w-1];
                store[i][j][w-1] = s;
            }
        }
    }

    int ans = numeric_limits<int>::min();

    for(int w = 1; w <= n; w++) {
        for(int j = 0; j < n-w; j++) {
            int s = 0;
            for(int i = 0; i < n; i++) {
                s += store[i][j][w-1];
                ans = max(ans, s);
                if (s < 0)
                    s = 0;
            }
            /*
            for(int i = 0; i < h; i++) {
                s += store[i][j][w-1];
            }
            //printf("(%d,%d)x%d = %d\n", 0, j, m, s);
            ans = max(ans, s);
            for(int i = h; i < n; i++) {
                s += store[i][j][w-1];
                s -= store[i-h][j][w-1];
                ans = max(ans, s);
                //printf("(%d,%d)x%d = %d\n", i-m+1, j, m, s);
            }
            */
        }
    }

    printf("%d\n", ans);

    return 0;
}
