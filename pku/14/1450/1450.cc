#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("Scenario #%d:\n%.2f\n\n", i+1, x*y + (x*y%2 == 1 ? sqrt(2.0)-1 : 0));
    }
    return 0;
}
