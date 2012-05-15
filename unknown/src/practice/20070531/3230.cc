#include <cstdio>
#include <limits>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 100

int adj[N][N];
const int IMPOSSIBLE = numeric_limits<int>::max() / 2 * -1;

int main() {

    for(;;) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0)
            break;

        REP(i, n) REP(j, n)
            scanf("%d", &adj[i][j]);

        int* dp_old = new int[n];
        int* dp_new = new int[n];

        REP(i, n)
            dp_old[i] = IMPOSSIBLE;
        dp_old[0] = 0;

        REP(day, m) {
            int incomes[N];
            REP(i, n)
                scanf("%d", &incomes[i]);
            REP(i, n)
                dp_new[i] = IMPOSSIBLE;
            REP(i, n) REP(j, n) {
                dp_new[j] >?= dp_old[i] - adj[i][j] + incomes[j];
            }
            swap(dp_old, dp_new);
        }

        printf("%d\n", *max_element(dp_old, dp_old+n));

    }

    return 0;
}


