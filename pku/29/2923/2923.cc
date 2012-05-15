#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <limits>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

template<class T>
struct myvector {
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef int size_type;
    T* data;
    int n;
    int capa;
    myvector() : data(new T[2]), n(0), capa(2) {}
    myvector(int n) : data(new T[n]), n(n), capa(n) {
        REP(i, n)
            data[i] = T();
    }
    ~myvector() { delete[] data; }
    myvector(const myvector<T>& rhs) : data(new T[rhs.capa]), n(rhs.n), capa(rhs.capa) {
        copy(rhs.data, rhs.data+n, data);
    }
    myvector& operator=(const myvector<T>& rhs) {
        myvector cp(rhs);
        swap(data, cp.data);
        swap(n, cp.n);
        swap(capa, cp.capa);
    }
    inline int size() const { return n; }
    inline bool empty() const { return (n == 0); }
    inline void clear() { n = 0; }
    inline T* begin() { return data; }
    inline T* end() { return data+n; }
    inline T& front() { return *data; }
    inline T& operator[](int i) { return data[i]; }
    inline const T& front() const { return *data; }
    inline void push_back(const T& value) {
        if (n+1 > capa) {
            capa *= 2;
            T* newdata = new T[capa];
            copy(data, data+n, newdata);
            delete[] data;
            data = newdata;
        }
        data[n++] = value;
    }
    inline void pop_back() {
        n--;
    }

};


int pack(myvector<int> v, int c) {
    if (v.empty())
        return 0;

    int n = v.size();
    REP(i, n)
        if (v[i] > c)
            return 10000;

    int res = 12345;
    sort(v.begin()+1, v.end());
    do {
        int r = c;
        int k = 0;
        REP(i, n) {
            int l = v[i];
            if (r-l < 0)
                k++, r = c;
            r -= l;
        }
        k++;
        res <?= k;
    } while(next_permutation(v.begin()+1, v.end()));

    return res;
}

void solve() {
    int n, c1, c2;
    cin >> n >> c1 >> c2;
    myvector<int> v(n);
    REP(i, n)
        cin >> v[i];
    int res = n;
    REP(p, 1<<n) {
        myvector<int> v1, v2;
        REP(i, n)
            ((p&(1<<i)) != 0 ? v1 : v2).push_back(v[i]);
        res <?= max(pack(v1, c1), pack(v2, c2));
    }

    cout << res << endl;
}

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        cout << "Scenario #" << iCase+1 << ":" << endl;
        solve();
        cout << endl;
    }

    return 0;
}
