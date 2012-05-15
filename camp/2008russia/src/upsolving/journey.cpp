#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "journey"

#define MOD 1000000009

typedef int** matrix_t;

matrix_t new_matrix(int n) {
    matrix_t a = new int*[n];
    REP(i, n) {
        a[i] = new int[n];
        REP(j, n)
            a[i][j] = 0;
    }
    return a;
}

matrix_t multiply(matrix_t a, matrix_t b, int n) {
    matrix_t c = new_matrix(n);
    REP(i, n) REP(j, n) REP(k, n)
        c[i][k] = (int)((c[i][k] + (long long)a[i][j] * b[j][k]) % MOD);
    return c;
}

matrix_t pow(matrix_t a, int n, int p) {
    matrix_t b = new_matrix(n);
    REP(i, n) REP(j, n)
        b[i][j] = (p%2 == 0 ? (i == j ? 1 : 0) : a[i][j]);
    if (p >= 2)
        b = multiply(b, pow(multiply(a, a, n), n, p/2), n);
    return b;
}

int go(bool** g, int n, int d, int p) {
    matrix_t a = new_matrix(n);
    REP(i, n) REP(j, n)
        if (g[i][j] && (p & (1<<i)) == 0 && (p & (1<<j)) == 0)
            a[i][j] = 1;
    matrix_t b = pow(a, n, d-1);
    int res = 0;
    REP(i, n) REP(j, n)
        if ((p & (1<<j)) == 0)
            res = (res + b[i][j]) % MOD;
    return res;
}


int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    int n, m, k, d;
    cin >> n >> m >> k >> d;

    bool** g = new bool*[n];
    REP(i, n) {
        g[i] = new bool[n];
        REP(j, n)
            g[i][j] = false;
    }

    REP(i, m) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a][b] = g[b][a] = true;
    }

    int res = 0;
    REP(p, 1<<k) {
        int lo = go(g, n, d, p);
        if (__builtin_popcount(p) % 2 == 0)
            res = (res + lo) % MOD;
        else
            res = (res - lo + MOD) % MOD;
    }

    cout << res << endl;

    return 0;
}



