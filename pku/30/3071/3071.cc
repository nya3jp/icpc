#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 7

double prob[1<<N][1<<N];
int n;

double mem[N][1<<N];

double f(int order, int k) {
    if (order == n)
        return 1.0;
    double& res = mem[order][k];
    if (res < 0) {
        int m = 1<<(n-order-1);
        int mask = m-1;
        int from = (k&~mask)^m;
        int to = from + m;
        res = 0;
        for(int l = from; l < to; l++)
            res += f(order+1, l) * prob[k][l];
        res *= f(order+1, k);
    }
    return res;
}

int main() {
    while(scanf("%d", &n), n >= 0) {
        REP(i, 1<<n) REP(j, 1<<n)
            scanf("%lf", &prob[i][j]);
        REP(i, n) REP(j, 1<<n)
            mem[i][j] = -1;
        vector<double> res(1<<n);
        REP(i, 1<<n)
            res[i] = f(0, i);
        printf("%d\n", max_element(ALLOF(res))-res.begin() + 1);
    }
    return 0;
}
