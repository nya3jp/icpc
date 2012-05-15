/*
 * UVA 10541 Stripe
 * 2005-09-28
 * by nya
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define IL inline


template<int N>
struct integer {
    typedef unsigned int I;
    typedef long long int II;
    typedef integer<N> T;
    typedef const T& CRT;
    typedef integer<N >> 1> B;
    static const T Z;
    B l, h;

    integer(I a=0) : l(a) {
    }
    explicit integer(const std::string& s) {
        for(int i=0; i<(int)s.size(); i++)
            mul(10, s[i] - '0');
    }

    IL bool any() const {
        return (l.any() || h.any());
    }
    IL int bits() const {
        int n = h.bits();
        return (n >= 0 ? n + (N>>1) : l.bits());
    }

    IL I add(CRT x, I r) {
        if (x.l.any() || r) {
            r = l.add(x.l, r);
        }
        if (x.h.any() || r) {
            r = h.add(x.h, r);
        }
        return r;
    }
    IL I sub(CRT x, I r) {
        if (x.l.any() || r) {
            r = l.sub(x.l, r);
        }
        if (x.h.any() || r) {
            r = h.sub(x.h, r);
        }
        return r;
    }
    IL T mul(CRT x, CRT r) {
        T t(*this), f;
        if (x.l.any()) {
            if (l.any()) {
                f.l = l.mul(x.l, f.l);
            }
            if (h.any() || f.l.any()) {
                f.l = h.mul(x.l, f.l);
            }
        }
        if (x.h.any()) {
            if (t.l.any()) {
                f.h = t.l.mul(x.h, f.h);
            }
            if (t.h.any() || f.h.any()) {
                f.h = t.h.mul(x.h, f.h);
            }
            f.h.add(B::Z, f.l.add(t.h, h.add(t.l, 0)));
        }
        f.add(Z, add(r, 0));
        return f;
    }
    IL I mul(I x, I r) {
        if (l.any() || r) {
            r = l.mul(x, r);
        }
        if (h.any() || r) {
            r = h.mul(x, r);
        }
        return r;
    }
    IL I div(I d, I e) {
        if (h.any() || e) {
            e = h.div(d, e);
        }
        if (l.any() || e) {
            e = l.div(d, e);
        }
        return e;
    }

    friend T operator+(CRT a, CRT b) {
        T x(a);
        x.add(b, 0);
        return x;
    }
    friend T operator-(CRT a, CRT b) {
        T x(a);
        x.sub(b, 0);
        return x;
    }
    friend T operator*(CRT a, CRT b) {
        T x(a);
        x.mul(b, T::Z);
        return x;
    }
    friend T operator*(CRT a, I b) {
        T x(a);
        x.mul(b, 0);
        return x;
    }
    friend T operator/(CRT a, I b) {
        T x(a);
        x.div(b, 0);
        return x;
    }
    friend I operator%(CRT a, I b) {
        T x(a);
        return x.div(b, 0);
    }
    int compare(CRT o) const {
        int i = h.compare(o.h);
        if (i == 0)
            i = l.compare(o.l);
        return i;
    }
    friend IL bool operator<(CRT a, CRT b) {
        return ( a.compare(b) < 0 );
    }
    friend IL bool operator>(CRT a, CRT b) {
        return ( a.compare(b) > 0 );
    }
    friend IL bool operator<=(CRT a, CRT b) {
        return ( a.compare(b) <= 0 );
    }
    friend IL bool operator>=(CRT a, CRT b) {
        return ( a.compare(b) >= 0 );
    }
    friend IL bool operator==(CRT a, CRT b) {
        return ( a.compare(b) == 0 );
    }
    friend IL bool operator!=(CRT a, CRT b) {
        return ( a.compare(b) != 0 );
    }
    T operator+=(T b) {
        add(b, 0);
        return *this;
    }
    T operator-=(T b) {
        sub(b, 0);
        return *this;
    }
    T operator*=(T b) {
        mul(b, T::Z);
        return *this;
    }
    T operator*=(I b) {
        mul(b, 0);
        return *this;
    }
    T operator/=(I b) {
        div(b, 0);
        return *this;
    }
    I operator%=(I b) {
        return div(b, 0);
    }
    friend std::ostream& operator<<(std::ostream& s, CRT a) {
        return s << a.toString();
    }

    std::string toString() const {
        std::vector<char> v;
        T x(*this);
        while(x.any()) {
            v.push_back(x.div(10, 0) + '0');
        }
        if (v.empty())
            v.push_back('0');
        return std::string(v.rbegin(), v.rend());
    }
};

template<>
struct integer<32> {

    typedef unsigned int I;
    typedef long long int II;
    typedef integer<32> T;
    typedef const T& CRT;
    static const T Z;
    static const I M = 0xffffffff;
    enum { N = 32 } consts;
    I a;

    integer(I a=0) : a(a) {
    }
    explicit integer(const std::string& s) {
        for(int i=0; i<(int)s.size(); i++)
            mul(10, s[i] - '0');
    }

    IL bool any() const {
        return (a != 0);
    }
    IL int bits() const {
        for(int i=N-1; i>=0; i--) {
            if ( (a & (1 << i)) != 0 )
                return i;
        }
        return -1;
    }

    IL I add(CRT x, I r) {
        II ll = (II)a + x.a + r;
        a = (I)ll;
        return (I)(ll >> N);
    }
    IL I sub(CRT x, I r) {
        II ll = (II)a - x.a - r;
        a = (I)(ll & M);
        return -(I)((ll >> N) & M);
    }
    IL T mul(CRT x, CRT r) {
        return mul(x.a, r.a);
    }
    IL I mul(I x, I r) {
        II ll = (II)a * x + r;
        a = (I)ll;
        return (I)(ll >> N);
    }
    IL I div(I d, I e) {
        II x = ((II)e << N) | a;
        a = (I)(x / d);
        return (I)(x % d);
    }

    int compare(CRT o) const {
        return (a == o.a ? 0 : a < o.a ? -1 : 1);
    }
    friend IL bool operator<(CRT a, CRT b) {
        return ( a.compare(b) < 0 );
    }
    friend IL bool operator>(CRT a, CRT b) {
        return ( a.compare(b) > 0 );
    }
    friend IL bool operator<=(CRT a, CRT b) {
        return ( a.compare(b) <= 0 );
    }
    friend IL bool operator>=(CRT a, CRT b) {
        return ( a.compare(b) >= 0 );
    }
    friend IL bool operator==(CRT a, CRT b) {
        return ( a.compare(b) == 0 );
    }
    friend IL bool operator!=(CRT a, CRT b) {
        return ( a.compare(b) != 0 );
    }

    friend T operator+(CRT a, CRT b) {
        T x(a);
        x.add(b, 0);
        return x;
    }
    friend T operator-(CRT a, CRT b) {
        T x(a);
        x.sub(b, 0);
        return x;
    }
    friend T operator*(CRT a, CRT b) {
        T x(a);
        x.mul(b, T::Z);
        return x;
    }
    friend T operator*(CRT a, I b) {
        T x(a);
        x.mul(b, 0);
        return x;
    }
    friend T operator/(CRT a, I b) {
        T x(a);
        x.div(b, 0);
        return x;
    }
    friend I operator%(CRT a, I b) {
        T x(a);
        return x.div(b, 0);
    }
    T operator+=(T b) {
        add(b, 0);
        return *this;
    }
    T operator-=(T b) {
        sub(b, 0);
        return *this;
    }
    T operator*=(T b) {
        mul(b, T::Z);
        return *this;
    }
    T operator*=(I b) {
        mul(b, 0);
        return *this;
    }
    T operator/=(I b) {
        div(b, 0);
        return *this;
    }
    I operator%=(I b) {
        return div(b, 0);
    }
    friend std::ostream& operator<<(std::ostream& s, CRT a) {
        return s << a.toString();
    }

    std::string toString() const {
        std::vector<char> v;
        T x(*this);
        while(x.any()) {
            v.push_back(x.div(10, 0) + '0');
        }
        if (v.empty())
            v.push_back('0');
        return std::string(v.rbegin(), v.rend());
    }
};

template<int N>
const integer<N> integer<N>::Z;
template<>
const integer<32> integer<32>::Z;



template<class T>
struct Matrix {
    const int n, m;
    T* data;
    Matrix(int n, int m, const T& def = T()) : n(n), m(m), data(new T[n*m]) {
        clear(def);
    }
    ~Matrix() {
        delete[] data;
    }
    void clear(const T& value = T()) {
        for(int i=0; i<n*m; i++)
            data[i] = value;
    }
    inline T* operator[](int i) {
        return data+i*m;
    }
    inline const T* operator[](int i) const {
        return data+i*m;
    }
};


int main() {
    int nCases;
    std::cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {
        int n, k;
        std::cin >> n >> k;
        std::vector<int> code(k);
        for(int i=0; i<k; i++)
            std::cin >> code[i];
        Matrix< integer<256> > table(k+1, n+1);
        for(int j=0; j<=n; j++) {
            table[k][j] = 1;
        }
        for(int i=k-1; i>=0; i--) {
            for(int j=n; j>=0; j--) {
                if (j+1 <= n)
                    table[i][j] += table[i][j+1];
                int hop = (i != k-1 ? code[i]+1 : code[i]);
                if (i+1 <= k && j+hop <= n)
                    table[i][j] += table[i+1][j+hop];
            }
        }
        /*
        for(int i=0; i<=k; i++) {
            for(int j=0; j<=n; j++) {
                std::cout << table[i][j].toString() << ' ';
            }
            std::cout << std::endl;
        }
        */
        std::cout << table[0][0].toString() << std::endl;
    }
    return 0;
}



