#include <cstdio>
#include <algorithm>

using namespace std;

#define N 40000

int v[N];

void solve() {
    int p;
    scanf("%d", &p);
    int z = 0;
    for(int i = 0; i < p; i++) {
        int k;
        scanf("%d", &k);
        int j = upper_bound(v, v+z, k) - v;
        if (j == z) {
            v[z++] = k;
        }
        else {
            v[j] = k;
        }
        /*
        printf("> ");
        for(int j = 0; j < z; j++) {
            printf("%d ", v[j]);
        }
        printf("\n");
        */
    }
    printf("%d\n", z);
}

int main() {
    int nCases;
    scanf("%d", &nCases);
    while(nCases-- > 0)
        solve();
    return 0;
}
