#include <cstdio>

using namespace std;

int main() {
    int x, y;
    while(scanf("%d%d", &x, &y) == 2 && !(x == 0 && y == 0)) {
        printf("%.20f\n", (double)x/y);
    }
    return 0;
}

