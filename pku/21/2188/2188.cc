#include <cstdio>
#include <algorithm>

using namespace std;


#define N 1000

int main() {
    int n;
    scanf("%d", &n);

    int v[N];
    for(int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        v[a] = b;
    }

    int s = 0;
    for(int i = 0; i < n; i++) {
        int j = min_element(v+i, v+n) - v;
        s += j-i;
        rotate(v+i, v+j, v+j+1);
    }
    printf("%d\n", s);

    return 0;
}
