/*
 * UVA 10487 Closest Sums
 * 2005-09-16
 * by nya
 */

#include <cstdio>
#include <algorithm>

#define N_MAX 1000

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

int main() {
    int iCase=0;
    int n;
    while(std::scanf("%d", &n) == 1 && n != 0) {
        int s[N_MAX];
        for(int i=0; i<n; i++)
            std::scanf("%d", &s[i]);
        std::sort(s, s+n);
        int m;
        std::scanf("%d", &m);
        std::printf("Case %d:\n", ++iCase);
        for(int i=0; i<m; i++) {
            int a;
            std::scanf("%d", &a);
            int na = s[0]+s[1];
            for(int k=0; k<n; k++) {
                int b = s[k];
                int c = a - b;
                int r = (std::lower_bound(s+k+1, s+n, c) - (s+k+1));
                if (r < n-k-1) {
                    int d = s[k+1+r];
                    int e = b+d;
                    if (abs(e-a) < abs(na-a))
                        na = e;
                }
                if (r-1 >= 0) {
                    int d = s[k+1+r-1];
                    int e = b+d;
                    if (abs(e-a) < abs(na-a))
                        na = e;
                }
            }
            std::printf("Closest sum to %d is %d.\n", a, na);
        }
    }
    return 0;
}
