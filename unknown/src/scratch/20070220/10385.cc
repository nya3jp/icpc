#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

typedef long double decimal;

const decimal EPS = 1.0e-6;

typedef vector<decimal> vector_t;
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
    REP(i, n)
        nx[i] = i;
    REP(i, m)
        bx[i] = n+i;

    // Aの拡張、目的行の初期化
    A.resize(m+1);
    REP(i, m+1)
        A[i].resize(n+m, 0);
    REP(i, m)
        A[i][n+i] = 1;
    REP(i, m) REP(j, n)
        A[m][j] += A[i][j];
    b.push_back(accumulate(ALLOF(b), 0.0));

    int w = n + m;
    int v = n;
    // 最適化するよ！
    REP(phase, 2) {

        for(;;) {

            // でばっぐ
            /*
            printf("(Stage %d)\n", phase+1);
            printf("Free variables are: { ");
            REP(i, v)
                printf("%d ", nx[i]);
            printf("}\n");
            REP(i, m+1) {
                REP(j, w)
                    printf("%8.3f", (double)A[i][j]);
                printf(" | %8.3f\n", (double)b[i]);
            }
            printf("\n");
            */

            // 独立変数の選択
            int ni = -1;
            REP(i, v)
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
            REP(i, m) if (A[i][nv] > EPS)
                if (bi < 0 || b[i]/A[i][nv] < b[bi]/A[bi][nv]+EPS || (abs(b[i]/A[i][nv] - b[bi]/A[bi][nv]) < EPS && bx[i] < bx[bi]))
                    bi = i;
            if (bi < 0)
                break;

            // 掃きだし
            decimal pd = A[bi][nv];
            REP(i, w)
                A[bi][i] /= pd;
            b[bi] /= pd;

            REP(i, m+1) if (i != bi) {
                decimal pn = A[i][nv];
                REP(j, w)
                    A[i][j] -= A[bi][j] * pn;
                b[i] -= b[bi] * pn;
            }

            swap(nx[ni], bx[bi]);
        }

        if (phase)
            break;

        if (abs(b[m]) > EPS)
            return vector_t(); // no solution

        REP(bi, m) {
            int& bv = bx[bi];
            if (bv >= n) {
                REP(ni, n) {
                    int& nv = nx[ni];
                    if (abs(A[bi][nv]) > EPS) {

                        // 掃きだし
                        decimal pd = A[bi][nv];
                        REP(i, w)
                            A[bi][i] /= pd;
                        b[bi] /= pd;
                        
                        REP(i, m+1) if (i != bi) {
                            decimal pn = A[i][nv];
                            REP(j, w)
                                A[i][j] -= A[bi][j] * pn;
                            b[i] -= b[bi] * pn;
                        }

                        swap(nv, bv);
                        break;
                    }
                }
                assert(bv < n); // 条件おおすぎ
            }
        }

        w -= m;
        v -= m;
        nx.erase(remove_if(ALLOF(nx), bind2nd(greater_equal<int>(), n)), nx.end());
        assert(nx.size() == v);

        REP(i, m+1)
            A[i].resize(w);
        REP(i, n)
            A[m][i] = -c[i];
        b[m] = 0;
        REP(i, m) {
            decimal p = A[m][bx[i]];
            REP(j, w)
                A[m][j] -= A[i][j] * p;
            b[m] -= b[i] * p;
        }

    }

    vector_t x(n, 0);
    REP(i, m)
        x[bx[i]] = b[i];

    return x;
}


int main() {

    for(;;) {
        decimal len;
        cin >> len;
        if (!cin)
            break;

        int n;
        cin >> n;

        vector<decimal> sr(n), sk(n);
        REP(i, n)
            cin >> sr[i] >> sk[i];

        matrix_t A(n, n+2);
        REP(i, n-1) {
            A[i][0] = sk[i]*sk[n-1]*(sr[n-1]-sr[i]);
            A[i][1] = sr[i]*sr[n-1]*(sk[n-1]-sk[i]);
            A[i][2+i] = -sk[i]*sk[n-1]*sr[i]*sr[n-1];
            A[i][n+1] = -sk[i]*sk[n-1]*sr[i]*sr[n-1];
            /*
            A[i][0] = (1.0/sr[i] - 1.0/sr[n-1]);
            A[i][1] = (1.0/sk[i] - 1.0/sk[n-1]);
            A[i][2+i] = -1;
            A[i][n+1] = -1;
            */
        }
        A[n-1][0] = A[n-1][1] = 1;

        vector_t b(n);
        b[n-1] = len;

        vector_t c(n+2, 0);
        c[n+1] = -1;

        vector_t x = simplex(A, b, c);
        decimal rr, rk, ry = -1;

        if (!x.empty()) {
            rr = x[0];
            rk = x[1];
            ry = x[n+1];
        }

        /*
        {
            decimal r = len, k = 0;
            decimal y = 1e100;
            REP(i, n-1)
                y <?= (r/sr[i] + k/sk[i]) - (r/sr[n-1] + k/sk[n-1]);
            if (y > -EPS && y > ry) {
                ry = y;
                rr = r;
                rk = k;
            }
        }
        {
            decimal r = 0, k = len;
            decimal y = 1e100;
            REP(i, n-1)
                y <?= (r/sr[i] + k/sk[i]) - (r/sr[n-1] + k/sk[n-1]);
            if (y > -EPS && y > ry) {
                ry = y;
                rr = r;
                rk = k;
            }
        }
        */
        if (ry < 0) {
            printf("The cheater cannot win.\n");
        }
        else {
        printf("The cheater can win by %.0f seconds with r = %.2fkm and k = %.2fkm.\n",
               (double)(EPS+3600*ry), (double)(EPS+rr), (double)(EPS+rk));
        }

    }

    return 0;
}

