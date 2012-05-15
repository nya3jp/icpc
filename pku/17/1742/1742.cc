#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(i,n) if(0);else for(int i = 0; i < (int)(n); i++)
#define for if(0);else for

#define N 100
#define M 100000

#define INF 10000

int values[N];
int coins[N];
int* pays1 = new int[M+1];
int* pays2 = new int[M+1];

int main() {

    for(;;) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0)
            break;

        REP(k, n)
            scanf("%d", &values[k]);
        REP(k, n)
            scanf("%d", &coins[k]);

        REP(i, m+1)
            pays1[i] = 0;
        pays1[0] = 1;

        REP(k, n) {
            int v = values[k];
            int c = coins[k];

            REP(i, v)
                pays2[i] = (pays1[i] > 0 ? c+1 : 0);
            for(int i = v; i <= m; i++) {
                if (pays1[i] > 0)
                    pays2[i] = c+1;
                else if (pays2[i-v] > 0)
                    pays2[i] = pays2[i-v]-1;
                else
                    pays2[i] = 0;
            }
            swap(pays1, pays2);
        }

        int res = 0;
        for(int i = 1; i <= m; i++)
            if (pays1[i])
                res++;
        printf("%d\n", res);
    }

    return 0;
}
