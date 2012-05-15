/*
 * UVA 10494 If We Were a Child Again
 * 2005-08-27
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
    typedef unsigned long long int II;
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

    IL bool zero() const {
        return (l.zero() && h.zero());
    }
    IL operator bool() const {
        return (! zero());
    }

    IL I add(CRT x, I r) {
        if (x.l || r) {
            r = l.add(x.l, r);
            if (x.h || r) {
                r = h.add(x.h, r);
            }
        }
        return r;
    }
    IL T mul(CRT x, CRT r) {
        T t(*this), f;
        if (x.l) {
            if (l) {
                f.l = l.mul(x.l, f.l);
            }
            if (h || f.l) {
                f.l = h.mul(x.l, f.l);
            }
        }
        if (x.h) {
            if (t.l) {
                f.h = t.l.mul(x.h, f.h);
            }
            if (t.h || f.h) {
                f.h = t.h.mul(x.h, f.h);
            }
            f.h.add(B::Z, f.l.add(t.h, h.add(t.l, 0)));
        }
        f.add(Z, add(r, 0));
        return f;
    }
    IL I mul(I x, I r) {
        if (l || r) {
            r = l.mul(x, r);
        }
        if (h || r) {
            r = h.mul(x, r);
        }
        return r;
    }
    IL I div(I d, I e) {
        if (h || e) {
            e = h.div(d, e);
        }
        if (l || e) {
            e = l.div(d, e);
        }
        return e;
    }


    friend T operator+(CRT a, CRT b) {
        T x(a);
        x.add(b, 0);
        return x;
    }
    friend T operator*(CRT a, CRT b) {
        T x(a);
        x.mul(b, T::Z);
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
    T operator+=(CRT b) {
        add(b, 0);
        return *this;
    }
    T operator*=(CRT b) {
        mul(b, T::Z);
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
        while(x) {
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
    typedef unsigned long long int II;
    typedef integer<32> T;
    typedef const T& CRT;
    static const T Z;
    static const int N = 32;
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

    IL bool zero() const {
        return (a == 0);
    }
    IL operator bool() const {
        return (a != 0);
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

    friend T operator+(CRT a, CRT b) {
        T x(a);
        x.add(b, 0);
        return x;
    }
    friend T operator*(CRT a, CRT b) {
        T x(a);
        x.mul(b, T::Z);
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
    T operator+=(CRT b) {
        add(b, 0);
        return *this;
    }
    T operator*=(CRT b) {
        mul(b, T::Z);
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
        while(x) {
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




int main() {

    typedef integer<4096> longint;

    std::string s;
    char c;
    unsigned int d;
    while(std::cin >> s >> c >> d) {
        longint a(s);
        if (c == '/')
            a = a / d;
        else
            a = a % d;
        std::cout << a << std::endl;
    }

    return 0;
}

