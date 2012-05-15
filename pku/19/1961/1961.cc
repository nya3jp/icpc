#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

char buf[1000000+1024];

void solve(const char* s, int n) {
    int* kmp = new int[n+1];

    int q = kmp[0] = -1;
    for(int p = 1; p <= n; p++) {
        while(q >= 0 && s[q] != s[p-1])
            q = kmp[q];
        kmp[p] = ++q;
    }

    for(int i = 2; i <= n; i++) {
        int p = i - kmp[i];
        if (i % p == 0) {
            int k = i / p;
            if (k > 1) {
                printf("%d %d\n", i, k);
            }
        }
    }

    delete[] kmp;
}


int main() {
    int iCase = 0;
    for(;;) {
        int n;
        scanf("%d%s", &n, buf);
        if (n == 0)
            break;
        printf("Test case #%d\n", ++iCase);
        solve(buf, n);
        printf("\n");
    }
    return 0;
}
