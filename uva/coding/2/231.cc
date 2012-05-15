#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;
#define N 1000000
#define INF 10000000
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
int lis[N];

int main() {

    int iCase = 0;
    while(true) {

        int h;
        scanf("%d", &h);
        if (h < 0)
            break;
REP(i, N) lis[i] = INF;

        do {

            h = 40000 - h;
            *upper_bound(lis, lis+N, h) = h;
            
        } while(scanf("%d", &h), h != -1);

        if (iCase > 0)
            printf("\n");
        printf("Test #%d:\n  maximum possible interceptions: %d\n",
               iCase+1, find(lis, lis+N, INF) - lis);

        iCase++;
    }

    return 0;
}

