/*
 * UVA 10408 Farey sequences
 * 2005-08-08
 * by nya
 */

#include <cstdio>
#include <algorithm>

#define MAX_N 1000

struct frac {
    short num, denom;
};
inline bool operator<(const frac& a, const frac& b) {
    return ( ((int)a.num*(int)b.denom) < ((int)b.num*(int)a.denom) );
}
inline bool operator==(const frac& a, const frac& b) {
    return ( ((int)a.num*(int)b.denom) == ((int)b.num*(int)a.denom) );
}

int main() {
    frac* fracs = new frac[MAX_N*MAX_N];
    int n, k;
    while(std::scanf("%d%d", &n, &k) == 2) {
        k--;
        int m = 0;
        for(int denom=1; denom<=n; denom++) {
            for(int num=1; num<=denom; num++) {
                fracs[m].num = num;
                fracs[m].denom = denom;
                m++;
            }
        }
        std::stable_sort(fracs, fracs+m);
        m = std::unique(fracs, fracs+m) - fracs;
        std::printf("%d/%d\n", fracs[k].num, fracs[k].denom);
    }
    delete[] fracs;
    return 0;
}



