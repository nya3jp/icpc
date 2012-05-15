/*
 * 固定長整数クラス
 * 扱えるのは非負の数のみ!
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


#define IL inline
#define FBO friend inline bool operator

template<int N>
struct integer {
    typedef unsigned int I;
    typedef long long int II;
    typedef integer<N> T;
    typedef const T& CRT;
    typedef integer<N/2> B;
    static const T Z;
    B l, h;

    integer(I a=0) : l(a) {
    }
    explicit integer(const string& s) {
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
        if (r || x.l.any())
            r = l.add(x.l, r);
        if (r || x.h.any())
            r = h.add(x.h, r);
        return r;
    }
    IL T mul(CRT x, CRT r) {
        T t, f;
        if (x.h.any()) {
            t = *this;
            f.h = t.h.mul(x.h, t.l.mul(x.h, r.h));
        }
        else {
            t.l = r.h;
        }
        if (x.l.any()) {
            f.l = h.mul(x.l, l.mul(x.l, r.l));
        }
        else {
            l = r.l;
            h = B::Z;
        }
        f.h.add(B::Z, f.l.add(t.h, h.add(t.l, 0)));
        return f;
    }
    IL I mul(I x, I r) {
        if (r || l.any())
            r = l.mul(x, r);
        if (r || h.any())
            r = h.mul(x, r);
        return r;
    }
    IL I div(I d, I e) {
        if (e || h.any())
            e = h.div(d, e);
        if (e || l.any())
            e = l.div(d, e);
        return e;
    }
    IL void flip() {
        h.flip();
        l.flip();
    }
    IL void neg() {
        flip();
        add(Z, 1);
    }

    FBO ==(CRT a, CRT b) {
        return (a.l == b.l && a.h == b.h);
    }
    FBO !=(CRT a, CRT b) {
        return !(a == b);
    }
    FBO <(CRT a, CRT b) {
        if (!(a.h == b.h))
            return (a.h < b.h);
        return (a.l < b.l);
    }
    FBO <=(CRT a, CRT b) {
        return !(b < a);
    }
    FBO >(CRT a, CRT b) {
        return (b < a);
    }
    FBO >=(CRT a, CRT b) {
        return !(a < b);
    }

    friend T operator+(CRT a, CRT b) {
        T x(a);
        x.add(b, 0);
        return x;
    }
    friend T operator-(CRT a, CRT b) {
        T y(b);
        y.neg();
        y.add(a, 0);
        return y;
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
    IL T& operator+=(CRT b) {
        T t(b);
        add(t, 0);
        return *this;
    }
    IL T& operator-=(CRT b) {
        T t(b);
        t.neg();
        add(t, 0);
        return *this;
    }
    IL T& operator*=(CRT b) {
        T t(b);
        mul(t, T::Z);
        return *this;
    }
    IL T& operator*=(I b) {
        mul(b, 0);
        return *this;
    }
    IL T& operator/=(I b) {
        div(b, 0);
        return *this;
    }
    IL I operator%=(I b) {
        return div(b, 0);
    }
    friend ostream& operator<<(ostream& s, CRT a) {
        return s << a.to_string();
    }
    friend istream& operator>>(istream& s, T& a) {
        string t;
        cin >> t;
        a = T(t);
        return s;
    }

    string to_string() const {
        string s;
        T x(*this);
        while(x.any())
            s.append(1, (char)(x.div(10, 0) + '0'));
        if (s.empty())
            s.append(1, '0');
        return string(s.rbegin(), s.rend());
    }
};

template<>
struct integer<32> {

    typedef unsigned int I;
    typedef long long int II;
    typedef integer<32> T;
    typedef const T& CRT;
    static const T Z;
    enum { N = 32 } consts;
    I a;

    integer(I a=0) : a(a) {
    }
    explicit integer(const string& s) {
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
    IL void flip() {
        a = ~a;
    }

    FBO ==(CRT a, CRT b) {
        return (a.a == b.a);
    }
    FBO <(CRT a, CRT b) {
        return (a.a < b.a);
    }
};

const integer<32> integer<32>::Z;
template<int N>
const integer<N> integer<N>::Z;


typedef integer<1024> bigint;



int main() {

    for(bigint n; cin >> n; ) {
        if (n == 0)
            cout << 1 << endl;
        else
            cout << (n*(n-1) + 2) << endl;
    }


    return 0;
}

