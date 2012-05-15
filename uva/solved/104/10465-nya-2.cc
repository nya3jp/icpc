/*
 * UVA 10465 Homer Simpson
 * 2006-02-14
 * by nya
 */

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_TIME 10000

int main() {
    int burgers[MAX_TIME+1];
    int n, m, t;
    while(scanf("%d%d%d", &n, &m, &t) == 3) {
        burgers[0] = 0;
        for(int i = 1; i <= t; i++) {
            burgers[i] = -1;
        }
        for(int i = n; i <= t; i++) {
            if (burgers[i-n] != -1)
                burgers[i] = max(burgers[i], burgers[i-n]+1);
        }
        for(int i = m; i <= t; i++) {
            if (burgers[i-m] != -1)
                burgers[i] = max(burgers[i], burgers[i-m]+1);
        }
        for(int i = t; i >= 0; i--) {
            if (burgers[i] != -1) {
                printf("%d", burgers[i]);
                if (i != t) {
                    printf(" %d", t-i);
                }
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

