#include <iostream>
#include <numeric>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 8
#define M 8

const double EPS = 1.0e-10;
const double INF = 1./0.;
const double NaN = 0./0.;

typedef vector<double> vector_t;
typedef vector<vector_t> matrix_t;

vector_t simplex(matrix_t A, vector_t b, vector_t c) {

    int n = c.size(), m = b.size();

    // Bを正にして実行可能にする
    REP(i, m) if (b[i] < 0) {
        REP(j, n)
            A[i][j] *= -1;
        b[i] *= -1;
    }

    // 基底変数/独立変数のリスト
    vector<int> bx(m), nx(n);
    REP(i, m)
        bx[i] = n+i;
    REP(i, n)
        nx[i] = i;

    // Aの拡張、目的行の初期化
    A.resize(m+1);
    REP(i, m+1)
        A[i].resize(n+m, 0);
    REP(i, m)
        A[i][n+i] = 1;
    REP(i, m) REP(j, n)
        A[m][j] += A[i][j];
    b.push_back(accumulate(ALLOF(b), 0.0));

    // 最適化するよ！
    REP(phase, 2) {

        for(;;) {

            /*
            // でばっぐ
            printf("(Stage %d)\n", phase+1);
            printf("Free variables are: { ");
            REP(i, n)
                printf("%d ", nx[i]);
            printf("}\n");
            REP(i, m+1) {
                REP(j, n+m)
                    printf("%8.3f", A[i][j]);
                printf(" | %8.3f\n", b[i]);
            }
            printf("\n");
            */

            // 独立変数の選択
            int ni = -1;
            REP(i, n)
                if (A[m][nx[i]] > EPS && (ni < 0 || nx[i] < nx[ni]))
                    ni = i;
            if (ni < 0)
                break;

            int nv = nx[ni];

            // 有界性のチェック
            bool ninf = true;
            REP(i, m)
                if (A[i][nv] > EPS)
                    ninf = false;
            if (ninf)
                return vector_t(); // -infinity

            // 基底変数の選択
            int bi = -1;
            REP(i, m) if (A[i][nv] > EPS && (bi < 0 || (b[i]/A[i][nv] < b[bi]/A[bi][nv])))
                bi = i;
            if (bi < 0)
                break;

            // 掃きだし
            double pd = A[bi][nv];
            REP(i, n+m)
                A[bi][i] /= pd;
            b[bi] /= pd;

            REP(i, m+1) if (i != bi) {
                double pn = A[i][nv];
                REP(j, n+m)
                    A[i][j] -= A[bi][j] * pn;
                b[i] -= b[bi] * pn;
            }

            swap(nx[ni], bx[bi]);
        }

        if (phase)
            break;

        if (abs(b[m]) > EPS)
            return vector_t(); // no solution
        A[m].assign(n+m, 0);
        REP(i, n)
            A[m][i] = -c[i];
        b[m] = 0;
        REP(i, m) {
            double p = A[m][bx[i]];
            REP(j, n)
                A[m][j] -= A[i][j] * p;
            b[m] -= b[i] * p;
        }
    }

    vector_t x(n+m, 0);
    REP(i, m)
        x[bx[i]] = b[i];
    x.resize(n);

    return x;
}


int main() {

    freopen("simplex.in", "r", stdin);

    int n, m;
    cin >> n >> m;

    matrix_t A(m, vector_t(n));
    vector_t b(m), c(n);
    REP(i, m) {
        REP(j, n)
            cin >> A[i][j];
        cin >> b[i];
    }
    REP(i, n)
        cin >> c[i];

    vector_t x = simplex(A, b, c);
    printf("solution = { ");
    REP(i, n)
        printf("%8.3f", x[i]);
    printf(" }\n");

    double y = 0;
    REP(i, n)
        y += c[i] * x[i];
    printf("optimal value = %.3f\n", y);

    return 0;
}

