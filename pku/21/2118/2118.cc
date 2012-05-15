#include <vector>

template<class T>
struct Matrix : public std::vector< std::vector<T> >
{
    Matrix(int n, int m, const T& value = T()) {
        assign(n, m, value);
    }
    void assign(int n, int m, const T& value = T()) {
        std::vector< std::vector<T> >::assign(n, std::vector<T>(m, value));
    }
};


template<class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) {
    assert(a[0].size() == b.size());
    const int n = a.size();
    const int m = b[0].size();
    const int l = a[0].size();
    Matrix<T> result(n, m, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            T& r = result[i][j];
            for(int k = 0; k < l; k++) {
                r = (r + a[i][k] * b[k][j]) % 10000;
            }
        }
    }
    return result;
}

template<class T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b) {
    assert(a.size() == b.size() && a[0].size() == b[0].size());
    const int n = a.size();
    const int m = a[0].size();
    Matrix<T> result(a);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            result[i][j] = (result[i][j] + b[i][j]) % 10000;
        }
    }
    return result;
}

template<class T>
std::vector<T> operator*(const Matrix<T>& mat, const std::vector<T>& vec) {
    assert(mat[0].size() == vec.size());
    const int n = mat.size();
    const int m = mat[0].size();

    std::vector<T> result(n, 0);
    for(int i = 0; i < n; i++) {
        T& r = result[i];
        for(int j = 0; j < m; j++) {
            r = (r + mat[i][j] * vec[j]) % 10000;
        }
    }
    return result;
}

template<class T>
Matrix<T> pow(const Matrix<T>& unit, unsigned int mag) {
    assert(unit.size() == unit[0].size());
    const int n = unit.size();

    Matrix<T> result(n, n, 0);
    for(int i = 0; i < n; i++)
        result[i][i] = 1;
    Matrix<T> tmp(unit);
    for(unsigned int p = 1; p <= mag; p <<= 1, tmp = tmp*tmp) {
        if ((mag&p) != 0)
            result = result * tmp;
    }

    return result;
}



#include <cstdio>

using namespace std;

void print(const Matrix<int>& mat) {
    const int n = mat.size();
    const int m = mat[0].size();
    for(int i = 0; i < n; i++) {
        printf("%c{", (i == 0 ? '{' : ' '));
        for(int j = 0; j < m; j++) {
            printf("%4d", mat[i][j]);
        }
        printf("}%c\n", (i == n-1 ? '}' : ' '));
    }
}
void print(const vector<int>& vec) {
    const int n = vec.size();
    printf("{");
    for(int i = 0; i < n; i++) {
        printf("%4d", vec[i]);
    }
    printf("}\n");
}

int main() {
    while(true) {
        int k;
        scanf("%d", &k);
        if (k == 0)
            break;
        vector<int> a(k);
        for(int i = 0; i < k; i++)
            scanf("%d", &a[i]);
        vector<int> b(k);
        for(int i = 0; i < k; i++)
            scanf("%d", &b[i]);
        int index;
        scanf("%d", &index);
        int result;
        if (index < k) {
            result = a[index];
        }
        else {
            Matrix<int> m(k, k, 0);
            for(int i = 0; i < k-1; i++) {
                m[i][i+1] = 1;
            }
            for(int i = 0; i < k; i++) {
                m[k-1][i] = b[k-1-i];
            }

            /*
            printf("m:\n");
            print(m);
            */

            m = pow(m, index-(k-1));

            /*
            printf("pow(m, %d):\n", index-(k-1));
            print(m);
            */

            vector<int> v = m * a;

            /*
            printf("v:\n");
            print(v);
            */

            result = v[k-1];
        }
        printf("%d\n", result);
    }
    return 0;
}
