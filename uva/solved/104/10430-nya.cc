/*
 * UVA 10430 Dear GOD, Pardon Me
 * 2005-09-27
 * by nya
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

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
    T& operator=(CRT rhs) {
        l = rhs.l;
        h = rhs.h;
        return *this;
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
            if (x.h.any() || r) {
                r = h.add(x.h, r);
            }
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
    friend bool operator<(CRT a, CRT b) {
        return ( a.compare(b) < 0 );
    }
    friend bool operator>(CRT a, CRT b) {
        return ( a.compare(b) > 0 );
    }
    friend bool operator<=(CRT a, CRT b) {
        return ( a.compare(b) <= 0 );
    }
    friend bool operator>=(CRT a, CRT b) {
        return ( a.compare(b) >= 0 );
    }
    friend bool operator==(CRT a, CRT b) {
        return ( a.compare(b) == 0 );
    }
    friend bool operator!=(CRT a, CRT b) {
        return ( a.compare(b) != 0 );
    }
    T operator+=(CRT b) {
        add(b, 0);
        return *this;
    }
    T operator-=(CRT b) {
        sub(b, 0);
        return *this;
    }
    T operator*=(CRT b) {
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
    static const int N = 32;
    static const I M = 0xffffffff;
    I a;

    integer(I a=0) : a(a) {
    }
    explicit integer(const std::string& s) {
        for(int i=0; i<(int)s.size(); i++)
            mul(10, s[i] - '0');
    }
    T& operator=(CRT rhs) {
        a = rhs.a;
        return *this;
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
        return (a == o.a ? 0 : a < o.a ? -1 : 1);
    }
    friend bool operator<(CRT a, CRT b) {
        return ( a.compare(b) < 0 );
    }
    friend bool operator>(CRT a, CRT b) {
        return ( a.compare(b) > 0 );
    }
    friend bool operator<=(CRT a, CRT b) {
        return ( a.compare(b) <= 0 );
    }
    friend bool operator>=(CRT a, CRT b) {
        return ( a.compare(b) >= 0 );
    }
    friend bool operator==(CRT a, CRT b) {
        return ( a.compare(b) == 0 );
    }
    friend bool operator!=(CRT a, CRT b) {
        return ( a.compare(b) != 0 );
    }
    T operator+=(CRT b) {
        add(b, 0);
        return *this;
    }
    T operator-=(CRT b) {
        sub(b, 0);
        return *this;
    }
    T operator*=(CRT b) {
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

typedef integer<512> longint;


template<class T>
T gcd(T n, T m) {
    while(true) {
        while(n > m) {
            n -= m;
        }
        if (n == m)
            break;
        while(m > n) {
            m -= n;
        }
        if (n == m)
            break;
    }
    return n;
}

int main() {
    std::printf("Dear GOD, Pardon Me\n");
    int t, n;
    int iCase = 0;
    while(std::scanf("%d%d", &t, &n) == 2) {
        if (iCase > 0)
            std::printf("\n");
        if (t == 1) {
            int x = n;
            int k = 1;
            std::printf("X = %d\nK = %d\n", x, k);
        }
        else if (t == 0 || n == 0) {
            int x = 0;
            int k = 0;
            std::printf("X = %d\nK = %d\n", x, k);
        }
        else {
            longint k(1);
            for(int i=0; i<n; i++)
                k *= t;
            longint x = (t == 1 ? n : (k - longint(1))/(t - 1));
            std::printf("X = %s\nK = %s\n", x.toString().c_str(), k.toString().c_str());
        }
        iCase++;
    }
    return 0;
}

