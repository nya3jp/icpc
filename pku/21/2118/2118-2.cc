/*
 * 行列演算
 *  高速べき乗
 *  LU分解
 *  ガウスの消去法
 */

#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long int integer;
typedef integer* vector_t;
typedef vector_t* matrix_t;


matrix_t new_matrix(int n) {
    matrix_t x = new vector_t[n];
    for(int i = 0; i < n; i++)
        x[i] = new integer[n];
    return x;
}

matrix_t dup_matrix(matrix_t x_, int n) {
    matrix_t x = new_matrix(n);
    for(int i = 0; i < n; i++)
        copy(x_[i], x_[i]+n, x[i]);
    return x;
}

void delete_matrix(matrix_t x, int n) {
    for(int i = 0; i < n; i++)
        delete[] x[i];
    delete[] x;
}


// 掛け算
matrix_t multiply(matrix_t a, matrix_t b, int n) {

    matrix_t r = new_matrix(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            r[i][j] = 0;
            for(int k = 0; k < n; k++)
                r[i][j] += a[i][k] * b[k][j];
            r[i][j] %= 10000;
        }
    }

    return r;
}


// 高速べき乗 e^m
matrix_t pow(matrix_t e, int n, int m) {

    matrix_t r = new_matrix(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            r[i][j] = ((m&1) == 0 ? (i == j ? 1 : 0) : e[i][j]);

    if (m >= 2) {
        matrix_t u = pow(e, n, m/2);
        matrix_t uu = multiply(u, u, n);
        matrix_t z = multiply(r, uu, n);
        delete_matrix(u, n);
        delete_matrix(uu, n);
        delete_matrix(r, n);
        r = z;
    }

    return r;
}


#include <iostream>

int main() {
    int n;
    while(cin >> n && n > 0) {
        vector_t b = new integer[n];
        matrix_t a = new_matrix(n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = 0;

        for(int i = 0; i < n; i++)
            cin >> b[i];
        for(int i = 0; i < n; i++)
            cin >> a[n-1][n-1-i];
        for(int i = 0; i < n-1; i++)
            a[i][i+1] = 1;

        /*
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                cout << a[i][j] << ' ';
            cout << endl;
        }
        */

        int k;
        cin >> k;
        if (k < n) {
            cout << b[k] << endl;
        }
        else {
            matrix_t m = pow(a, n, k-n+1);
            /*
            matrix_t m = dup_matrix(a, n);
            for(int i = 0; i < k-n; i++) {
                matrix_t mm = multiply(m, a, n);
                delete_matrix(m, n);
                m = mm;
            }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                cout << m[i][j] << ' ';
            cout << endl;
        }
            */
            integer z = 0;
            for(int i = 0; i < n; i++)
                z += m[n-1][i] * b[i];
            z %= 10000;
            delete_matrix(m, n);
            cout << z << endl;
        }

        delete[] b;
        delete_matrix(a, n);
    }
    return 0;
}
