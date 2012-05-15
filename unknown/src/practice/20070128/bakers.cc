#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define N 100

/*
struct boolean {
    bool data;
    inline boolean(bool data=false) : data(data) {
    }
    inline operator bool() const {
        return data;
    }
};
inline boolean operator*(const boolean& a, const boolean& b) {
    return boolean(a.data&&b.data);
}
inline boolean operator+(const boolean& a, const boolean& b) {
    return boolean(a.data!=b.data);
}
*/

typedef bool boolean;

inline boolean mul(const boolean& a, const boolean& b) {
    return boolean(a&&b);
}
inline boolean add(const boolean& a, const boolean& b) {
    return boolean(a!=b);
}


struct vector_t {
    boolean data[N];
    int n;
    vector_t() : n(0) {
    }
    vector_t(int n, bool value) : n(n) {
        REP(i, n)
            data[i] = value;
    }
    inline int size() const {
        return n;
    }
    inline boolean& operator[](int i) {
        return data[i];
    }
    inline const boolean& operator[](int i) const {
        return data[i];
    }
    inline boolean* begin() {
        return data;
    }
    inline boolean* end() {
        return data+n;
    }
};
struct matrix_t {
    vector_t data[N];
    int n;
    matrix_t() : n(0) {
    }
    matrix_t(int n, const vector_t& value) : n(n) {
        REP(i, n)
            data[i] = value;
    }
    inline int size() const {
        return n;
    }
    inline vector_t& operator[](int i) {
        return data[i];
    }
    inline const vector_t& operator[](int i) const {
        return data[i];
    }
};

/*
typedef vector<boolean> vector_t;
typedef vector<vector_t> matrix_t;
*/

matrix_t operator*(const matrix_t& x, const matrix_t& y) {
    int n = x.size();
    matrix_t res(n, vector_t(n, false));

    REP(i, n) REP(j, n) REP(k, n)
        res[i][j] = add(res[i][j], mul(x[i][k], y[k][j]));

    return res;
}

vector_t operator*(const vector_t& x, const matrix_t& y) {
    int n = x.size();
    vector_t res(n, false);

    REP(j, n) REP(k, n)
        res[j] = add(res[j], mul(x[k], y[k][j]));

    return res;
}

matrix_t pow(const matrix_t& x, int p) {
    int n = x.size();

    matrix_t res(n, vector_t(n, false));
    REP(i, n)
        res[i][i] = true;

    if (p%2 == 1)
        res = res * x;

    if (p >= 2) {
        matrix_t y = x * x;
        matrix_t z = pow(y, p/2);
        res = res * z;
    }
    return res;
}


map<string,int> ids;
vector<string> names;

int ID(string s) {
    if (ids.count(s) == 0) {
        ids.insert(make_pair(s, ids.size()));
        names.push_back(s);
    }
    return ids[s];
}


int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n, p;
        cin >> n >> p;

        ids.clear();
        names.clear();

        matrix_t x(n, vector_t(n, false));
        REP(i, n)
            x[i][i] = true;

        vector_t init(n, false);

        REP(i, n) {
            string s;
            cin >> s;
            /*
            char s[1024];
            scanf("%s", s);
            */
            int here = ID(s);
            int c, m;
            cin >> c >> m;
            /*
            scanf("%d%d", &c, &m);
            */
            init[here] = ((c%2) == 1);
            REP(j, m) {
                string t;
                cin >> t;
                /*
                char t[1024];
                scanf("%s", t);
                */
                int there = ID(t);
                x[here][there] = add(x[here][there], boolean(true));
            }
        }

        matrix_t y = pow(x, p);
        vector_t res = init * y;

        /*
        REP(i, n) {
            cout << names[i] << ": " << res[ID(names[i])].data << endl;
        }
        */

        cout << count(ALLOF(res), true) << endl;

    }


    return 0;
}
