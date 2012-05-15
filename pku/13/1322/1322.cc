#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

//typedef vector<double> vector_t;
//typedef vector<vector_t> matrix_t;

#define N 101

struct matrix_t {
    double** data;
    int n;
    matrix_t(int n) : n(n) {
        data = new double*[n];
        REP(i, n) {
            data[i] = new double[n];
            REP(j, n)
                data[i][j] = 0;
        }
    }
    virtual ~matrix_t() {
        REP(i, n)
            delete[] data[i];
        delete[] data;
    }
    inline double* operator[](int i) {
        return data[i];
    }
    inline const double* operator[](int i) const {
        return data[i];
    }
    inline int size() const {
        return n;
    }
};


matrix_t mul(const matrix_t& lhs, const matrix_t& rhs) {
    int n = lhs.size();
    matrix_t res(n);
    REP(i, n) REP(j, n) REP(k, n)
        res[i][j] += lhs[i][k] * rhs[k][j];
    return res;
}

matrix_t pow(const matrix_t& mat, int m) {
    int n = mat.size();
    matrix_t x(n);
    if (m&1) {
        x = mat;
    }
    else {
        REP(i, n)
            x[i][i] = 1;
    }
    if (m >= 2)
        x = mul(x, pow(mul(mat, mat), m>>1));
    return x;
}


int main() {

    freopen("1322.in", "r", stdin);

    for(;;) {

        int colors, iterations, choice;
        cin >> colors >> iterations >> choice;

        if (colors == 0)
            break;

        int n = colors + 1;

        matrix_t mat(n);

        for(int i = 1; i < colors; i++) {
            mat[i+1][i] = (double)(colors-i) / colors;
            mat[i-1][i] = (double)(i) / colors;
        }
        mat[1][0] = 1.0;
        mat[colors-1][colors] = 1.0;

        matrix_t pm = pow(mat, iterations);

        double res = (choice <= colors ? pm[choice][0] : 0);

        printf("%.3f\n", res);

    }

    return 0;
}
