#include <cstdio>
#include <algorithm>

using namespace std;

typedef unsigned long long int integer;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 500

int modulo;
int n;

//typedef integer matrix_t[N][N];
struct matrix_t {
    integer** data;
    matrix_t() {
        data = new integer*[N];
        REP(i, n)
            data[i] = new integer[N];
    }
    ~matrix_t() {
        REP(i, n)
            delete[] data[i];
        delete[] data;
    }
    matrix_t(matrix_t&);

    inline integer* operator[](int index) {
        return data[index];
    }
};

void nomult(matrix_t& x, matrix_t& a, matrix_t& b) {
    REP(i, n) REP(j, n) {
        x[i][j] = 0;
        REP(k, n)
            x[i][j] = (x[i][j] + a[i][k] * b[k][j]) % modulo;
    }
}

void mult(matrix_t& x, matrix_t& a, matrix_t& b) {
    REP(i, 1) REP(j, n) {
        x[i][j] = 0;
        REP(k, n)
            x[i][j] = (x[i][j] + a[i][k] * b[k][j]) % modulo;
    }
    for(int i = 1; i < n; i++) {
        REP(j, n) {
            x[i][j] = x[0][(j-i+n)%n];
        }
    }
}

void pow(matrix_t& x, matrix_t& b, int p) {
    //printf("pow(%d)\n", p);
    if (p % 2 == 0) {
        REP(i, n) REP(j, n)
            x[i][j] = (i == j ? 1 : 0);
    }
    else {
        REP(i, n) REP(j, n)
            x[i][j] = b[i][j];
    }

    if (p >= 2) {
        matrix_t b2, r, t;
        mult(b2, b, b);
        pow(r, b2, p/2);
        mult(t, x, r);
        REP(i, n) REP(j, n)
            x[i][j] = t[i][j];
    }
}

int main() {

    //printf("hoge\n");

    freopen("cell.in", "r", stdin);

    int nCases;
    scanf("%d", &nCases);
    REP(iCase, nCases) {

        int d, p;
        scanf("%d%d%d%d", &n, &modulo, &d, &p);

        //printf("hoge\n");

        integer init[N];
        REP(i, n) {
            int t;
            scanf("%d", &t);
            init[i] = t;
        }

        //printf("hoge\n");

        matrix_t band;

        REP(i, n) REP(j, n) {
            int dd = i-j;
            if (dd < 0)
                dd += n;
            dd = min(dd, n-dd);
            band[i][j] = (dd <= d ? 1 : 0);
        }

        //printf("hoge\n");

        //printf("band:\n");
        /*
        REP(i, n) {
            REP(j, n) {
                printf("%d ", (int)band[i][j]);
            }
            printf("\n");
        }
        */

        matrix_t x;
        pow(x, band, p);

        integer res[N];
        REP(i, n) {
            res[i] = 0;
            REP(j, n) {
                res[i] = (res[i] + x[i][j]*init[j]) % modulo;
            }
        }

        REP(i, n)
            printf("%d%c", (int)res[i], (i == n-1 ? '\n' : ' '));

    }
    return 0;
}

