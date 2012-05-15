#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

template<class T>
ostream& operator<<(ostream& s, const vector< vector<T> >& v) {
    s << "{" << endl;
    for(int i = 0; i < (int)v.size(); i++)
        s << " " << v[i] << endl;
    s << "}" << endl;
    return s;
}

template<class T>
ostream& operator<<(ostream& s, const vector<T>& v) {
    if (v.empty()) {
        s << "{}";
    }
    else {
        s << "{ " << v[0];
        for(int i = 1; i < (int)v.size(); i++)
            s << ", " << v[i];
        s << " }";
    }
    return s;
}

double simplex(vector< vector<double> > a, vector<double> b, vector<double> c) {

    int n = a.size();
    int m = a[0].size();

    cout << "a = " << a;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    {string line; getline(cin, line);}

    // まず掃きだししましょー
    double x = 0;
    for(int pi = 0; pi < n; pi++) {

        for(int j = pi+1; j < n; j++) {
            if (abs(a[j][pi]) > abs(a[pi][pi])) {
                a[pi].swap(a[j]);
                swap(b[pi], b[j]);
            }
        }

        {
            double r = a[pi][pi];
            for(int j = pi; j < m; j++)
                a[pi][j] /= r;
            b[pi] /= r;
        }

        for(int i = 0; i < n; i++) {
            if (i == pi)
                continue;
            double r = a[i][pi];
            for(int j = pi; j < m; j++)
                a[i][j] -= a[pi][j] * r;
            b[i] -= b[pi] * r;
        }

        {
            double r = c[pi];
            for(int j = pi; j < m; j++)
                c[j] -= a[pi][j] * r;
            x -= b[pi] * r;
        }

        cout << "a = " << a;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        {string line; getline(cin, line);}

    }

    // しんぷれっくす
    for(;;) {

        int pj;
        for(pj = 0; pj < m; pj++)
            if (c[pj] < 0)
                break;
        if (pj == m)
            break; // さいてき

        int pi;
        for(pi = 0; pi < n; pi++)
            if (a[pi][pj] > 0)
                break;
        if (pi == n)
            return -1/0.; // ひゆうかい

        {
            double r = a[pi][pj];
            for(int j = 0; j < m; j++)
                a[pi][j] /= r;
            b[pi] /= r;
        }

        for(int i = 0; i < n; i++) {
            if (i == pi)
                continue;
            double r = a[i][pj];
            for(int j = 0; j < m; j++)
                a[i][j] -= a[pi][j] * r;
            b[i] -= b[pi] * r;
        }

        {
            double r = c[pj];
            for(int j = 0; j < m; j++)
                c[j] -= a[pi][j] * r;
            c[pj] = 0;
            x -= b[pi] * r;
        }

        cout << "a = " << a;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        {string line; getline(cin, line);}

    }

    return -x;
}

int main() {

    ifstream fin("simplex.in");

    int n, m;
    fin >> n >> m;

    vector< vector<double> > a(n, vector<double>(m));
    vector<double> b(n);
    vector<double> c(m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            fin >> a[i][j];
        fin >> b[i];
    }

    for(int j = 0; j < m; j++)
        fin >> c[j];

    cout << simplex(a, b, c) << endl;

    return 0;
}
