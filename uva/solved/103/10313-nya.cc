/*
 * UVA 10313 - Pay the Price
 * 2005-07-07
 * by nya
 */

// f(s, n) = sum {1 <= i <= s} f(s-i-(n-1)(i-1), n-1)
//         = sum {1 <= i <= s} f(s-n(i-1)-1, n-1)

#include <cstdio>

#define LIMIT 300

int main() {

    unsigned long long int table[LIMIT+1][LIMIT+1];

    // s = 0
    for(int n=0; n<=LIMIT; n++) {
        table[0][n] = (n == 0 ? 1 : 0);
    }

    for(int s=1; s<=LIMIT; s++) {
        table[s][0] = 0;
        for(int n=1; n<=LIMIT; n++) {
            unsigned long long int& r = table[s][n];
            r = 0;
            for(int i=1; i<=s; i++) {
                int s2 = s - n*(i-1) - 1;
                if (s2 < 0) break;
                r += table[s2][n-1];
            }
        }
    }

    while(true) {
        char buf[64];
        if (! std::fgets(buf, sizeof(buf), stdin))
            break;
        int n, l1, l2, r;
        r = std::sscanf(buf, "%d%d%d", &n, &l1, &l2);
        if (r == 1) {
            l2 = n;
            l1 = 0;
        }
        else if (r == 2) {
            l2 = l1;
            l1 = 0;
        }
        if (l2 > n)
            l2 = n;
        unsigned long long int sum = 0;
        for(int l=l1; l<=l2; l++) {
            sum += table[n][l];
        }
        std::printf("%llu\n", sum);
    }

    return 0;
}
