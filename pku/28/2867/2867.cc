#include <cstdio>
#include <algorithm>

using namespace std;

#define N 50000
#define R 1000
int genome[N];
int tasks[R][2];

void solve(int iCase) {
    int n;
    scanf("%d", &n);
    if (n > 0) {
        printf("Genome %d\n", iCase+1);
        for(int i = 0; i < n; i++)
            genome[i] = i+1;
        int r;
        scanf("%d", &r);
        for(int i = 0; i < r; i++) {
            int from, to;
            scanf("%d%d", &from, &to);
            from--; to--;
            tasks[i][0] = from;
            tasks[i][1] = to;
        }
        for(int i = r-1; i >= 0; i--) {
            int from = tasks[i][0];
            int to = tasks[i][1];
            reverse(genome+from, genome+to+1);
        }
        int q;
        scanf("%d", &q);
        for(int i = 0; i < q; i++) {
            int pos;
            scanf("%d", &pos);
            pos--;
            printf("%d\n", genome[pos]);
        }
        solve(iCase+1);
    }
}

int main() {
    solve(0);
    return 0;
}
