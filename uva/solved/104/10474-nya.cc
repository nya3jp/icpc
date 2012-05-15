/*
 * UVA 10474 Where is the Marble?
 * 2005-07-30
 * by nya
 */

#include <cstdio>

#define N 10000

int main() {
    int v[N+1];
    int n, q;
    int iCase = 0;
    while(std::scanf("%d%d", &n, &q), !(n == 0 && q == 0)) {
        std::printf("CASE# %d:\n", ++iCase);
        // n[input]+N[part_sum]+q[query]
        for(int i=0; i<=N; i++) {
            v[i] = 0;
        }
        for(int i=0; i<n; i++) {
            int t;
            std::scanf("%d", &t);
            v[t]++;
        }
        {
            int c = 1;
            for(int i=0; i<=N; i++) {
                int a = v[i];
                if (a > 0) {
                    v[i] = c;
                    c += a;
                }
            }
        }
        for(int i=0; i<q; i++) {
            int t;
            std::scanf("%d", &t);
            if (v[t] > 0) {
                std::printf("%d found at %d\n", t, v[t]);
            }
            else {
                std::printf("%d not found\n", t);
            }
        }
    }
    return 0;
}
