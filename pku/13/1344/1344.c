#include <stdio.h>

int adj[30][30];

int solve(int* v, int n, int l) {
    int u[101][20], m[101];
    int g = v[0];
    int i;
    int res = adj[0][g]-l;
    printf("%d: ", l);
    for(i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
    memset(m,0,sizeof(m));
    for(i = 1; i < n; i++) {
        int a = v[i];
        int d = (adj[0][g] + adj[0][a] - adj[a][g])/2;
        u[d][m[d]++] = a;
    }
    for(i = 0; i < 101; i++)
        if (m[i] > 0)
            res += solve(u[i], m[i], i);
    return res;
}

int main() {
    int i,j;
    int v[30];
    for(;;) {
        int n;
        scanf("%d", &n);
        if (n == 0)
            break;
        for(i = 0; i < n; i++) {
            adj[i][i] = 0;
            for(j = i+1; j < n; j++)
                scanf("%d", &adj[i][j]), adj[j][i]=adj[i][j];
        }
        for(i = 1; i < n; i++)
            v[i-1] = i;
        printf("%d\n", solve(v, n-1, 0));
    }
}
