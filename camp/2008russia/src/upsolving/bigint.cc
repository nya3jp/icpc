/*
 * ŒÅ’è’·®”ƒNƒ‰ƒX
 * ˆµ‚¦‚é‚Ì‚Í”ñ•‰‚Ì”‚Ì‚İ!
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


#define REP(i,n) for(int i = 0; i < (int)(n); i++)


template<int N>
struct integer {
    integer<N/2> l, h;

    integer(unsigned int a = 0) : l(a) {
    }
    explicit integer(const string& s) {
        REP(i, s.size())
            muladd(10, s[i] - '0');
    }

    inline bool any() const {
        return (l.any() || h.any());
    }
    inline bool is_negative() const {
        return h.is_negative();
    }
    inline unsigned int add(const integer<N>& x, unsigned int r) {
        return h.add(x.h, l.add(x.l, r));
    }
    inline integer<N> muladd(const integer<N>& x, const integer<N>& r) {
        integer<N> t(*this), f;
        f.h = t.h.muladd(x.h, t.l.muladd(x.h, r.h));
        f.l = h.muladd(x.l, l.muladd(x.l, r.l));
        f.h.add(0, f.l.add(t.h, h.add(t.l, 0)));
        return f;
    }
    inline unsigned int muladd(unsigned int x, unsigned int r) {
        return h.muladd(x, l.muladd(x, r));
    }
    inline unsigned int div(unsigned int d, unsigned int e) {
        return l.div(d, h.div(d, e));
    }
    inline void flip() {
        h.flip();
        l.flip();
    }
    inline void neg() {
        flip();
        add(0, 1);
    }

    string to_string() const {
        string s;
        integer<N> x(*this);
        string sgn;
        if (x.is_negative()) {
            sgn = "-";
            x.neg();
        }
        while(x.any())
            s.append(1, (char)(x.div(10, 0) + '0'));
        if (s.empty())
            s.append(1, '0');
        s += sgn;
        return string(s.rbegin(), s.rend());
    }

    void print() {
        h.print();
        l.print();
    }
};

template<>
struct integer<32> {

    enum { N = 32 } consts;
    unsigned int a;

    integer(unsigned int a = 0) : a(a) {
    }
    explicit integer(const string& s) {
        REP(i, s.size())
            muladd(10, s[i] - '0');
    }

    inline bool any() const {
        return (a != 0);
    }
    inline bool is_negative() const {
        return ((int)a < 0);
    }

    inline unsigned int add(const integer<32>& x, unsigned int r) {
        unsigned long long ll = (unsigned long long)a + x.a + r;
        a = (int)ll;
        return (int)(ll >> N);
    }
    inline integer<32> muladd(const integer<32>& x, const integer<32>& r) {
        return muladd(x.a, r.a);
    }
    inline unsigned int muladd(unsigned int x, unsigned int r) {
        unsigned long long ll = (unsigned long long)a * x + r;
        a = (int)ll;
        return (int)(ll >> N);
    }
    inline unsigned int div(unsigned int d, unsigned int e) {
        unsigned long long x = ((unsigned long long)e << N) | a;
        a = (unsigned int)(x / d);
        return (unsigned int)(x % d);
    }
    inline void flip() {
        a = ~a;
    }
    void print() {
        printf("%08x ", a);
    }
};

template<int N>
integer<N> operator+(const integer<N>& a, const integer<N>& b) {
    integer<N> r(a);
    r.add(b, 0);
    return r;
}
template<int N>
integer<N> operator*(const integer<N>& a, const integer<N>& b) {
    integer<N> r(a);
    r.muladd(b, 0);
    return r;
}
template<int N>
integer<N> operator/(const integer<N>& a, int b) {
    integer<N> r(a);
    r.div(b, 0);
    return r;
}


typedef integer<256> bigint;



// ‚Ä‚·‚Æ
int main() {

    bigint c(3);
    REP(i, 100) {
        c = c * c;
        c.print();
        cout << endl;
    }
    return 0;

    //bigint a("12345678901234567890");
    //bigint b("87654321098765432110");
    bigint a(13), b(12);
    int i = 4;
    a.neg();

    a.print();

    cout << a.to_string() << " + " << b.to_string() << " = " << (a+b).to_string() << endl;
    cout << a.to_string() << " * " << b.to_string() << " = " << (a*b).to_string() << endl;
    cout << a.to_string() << " / " << i << " = " << (a/i).to_string() << endl;

    return 0;
}



