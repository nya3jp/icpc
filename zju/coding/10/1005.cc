/*
 * s—ñ‰‰Z
 *  ‚‘¬‚×‚«æ
 *  LU•ª‰ğ
 *  ƒKƒEƒX‚ÌÁ‹–@
 */

#include <cstdio>
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <cassert>

const long double PI = acos((long double)0.0)*2;

using namespace std;

typedef complex<long double> decimal;

typedef decimal* vector_t;
typedef vector_t* matrix_t;


matrix_t new_matrix(int n) {
    matrix_t x = new vector_t[n];
    for(int i = 0; i < n; i++)
        x[i] = new decimal[n];
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


// Š|‚¯Z
matrix_t multiply(matrix_t a, matrix_t b, int n) {

    matrix_t r = new_matrix(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            r[i][j] = 0;
            for(int k = 0; k < n; k++)
                r[i][j] += a[i][k] * a[k][j];
        }
    }

    return r;
}


// ‚‘¬‚×‚«æ e^m
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


// LU•ª‰ğ
// a‚ğ”j‰ó‚µ‚ÄLUŒ`®‚É•ÏŠ·‚·‚é
// p‚É‚Íint[n]‚ğ“n‚·
void lu_decompose(matrix_t a, int* p, int n) {

    for(int i = 0; i < n; i++)
        p[i] = i;

    for(int k = 0; k < n; k++) {

        int pivot = k;
        for(int i = k+1; i < n; i++)
            if (abs(a[i][k]) > abs(a[pivot][k]))
                pivot = i;

        swap(a[k], a[pivot]);
        swap(p[k], p[pivot]);

        for(int i = k+1; i < n; i++) {
            decimal m = (a[i][k] /= a[k][k]);
            for(int j = k+1; j < n; j++)
                a[i][j] -= a[k][j] * m;
        }

    }

}


// LU•ª‰ğ‚µ‚½s—ñ‚ğ—p‚¢‚ÄAx=b‚ğ‰ğ‚­
void lu_solve(matrix_t a, int* p, vector_t b, vector_t x, int n) {

    for(int i = 0; i < n; i++)
        x[i] = b[p[i]];

    for(int k = 0; k < n; k++)
        for(int i = 0; i < k; i++)
            x[k] -= a[k][i] * x[i];

    for(int k = n-1; k >= 0; k--) {
        for(int i = k+1; i < n; i++)
            x[k] -= a[k][i] * x[i];
        x[k] /= a[k][k];
    }

}


// ƒKƒEƒX‚ÌÁ‹–@‚ÅAx=b‚ğ‰ğ‚­
// a, b‚Í”j‰ó‚³‚êA“š‚¦‚ªb‚É•Ô‚é
void gauss(matrix_t a, vector_t b, int n) {

    for(int k = 0; k < n; k++) {

        int p = k;
        for(int i = k+1; i < n; i++)
            if (abs(a[i][k]) > abs(a[p][k]))
                p = i;

        swap(a[k], a[p]);
        swap(b[k], b[p]);

        for(int i = k+1; i < n; i++) {
            decimal m = a[i][k] / a[k][k];
            for(int j = k+1; j < n; j++)
                a[i][j] -= a[k][j] * m;
            b[i] -= b[k] * m;
        }

    }

    for(int k = n-1; k >= 0; k--) {
        for(int i = k+1; i < n; i++)
            b[k] -= a[k][i] * b[i];
        b[k] /= a[k][k];
    }
}


int main() {
    int iCase = 0;
    int n;
    while(cin >> n) {

        vector<decimal> points(n);
        for(int i = 0; i < n; i++) {
            long double x, y;
            cin >> x >> y;
            points[i] = decimal(x, y);
        }

        vector<long double> thetas(n);
        for(int i = 0; i < n; i++) {
            cin >> thetas[i];
        }

        matrix_t a = new_matrix(n);
        vector_t b = new decimal[n];

        for(int i = 0; i < n; i++) {
            fill(a[i], a[i]+n, 0);
            int j = (i+1)%n;
            long double th = thetas[i] * PI / 180;
            decimal rot = polar((long double)1.0, (PI-th)/2);
            long double ratio = 1.0 / ((long double)2.0 * sin(th / 2));
            a[i][i] = decimal(1, 0) - rot * ratio;
            a[i][j] = rot * ratio;
            b[i] = points[i];
        }

        /*
        cout << "A = " << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << a[i][j] << ' ';
            }
            cout << endl;
        }

        cout << "b = " << endl;
        for(int i = 0; i < n; i++) {
            cout << b[i] << ' ';
        }
        cout << endl;
        */

        /*
        matrix_t a_ = dup_matrix(a, n);
        */

        //*
        vector_t x = new decimal[n];
        int* p = new int[n];
        lu_decompose(a, p, n);
        lu_solve(a, p, b, x, n);
        copy(x, x+n, b);
        delete[] x;
        delete[] p;
        /*/
        gauss(a, b, n);
        //*/

        if (iCase++ > 0)
            printf("\n");
        for(int i = 0; i < n; i++) {
            double x = (double)(b[i].real());
            double y = (double)(b[i].imag());
            if (abs(x) < 0.005)
                x = 0;
            if (abs(y) < 0.005)
                y = 0;
            printf("%.2f %.2f\n", x, y);
        }

        delete_matrix(a, n);
        delete[] b;

    }
    return 0;
}



