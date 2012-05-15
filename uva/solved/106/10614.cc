/*
  UVA 10614 Dreadful Vectors
  2005-10-26
  by nya
*/

#include <cstdio>
#include <cstring>

typedef char* pchar;

struct ArithmeticException {};
struct SyntaxException {};

struct Value {
    int x, y, z;
    bool s;
    Value(int x=0) : x(x), s(true) {}
    Value(int x, int y, int z) : x(x), y(y), z(z), s(false) {}
    bool isScalar() const { return s; }
    Value operator+(const Value& o) const {
        if (s) {
            if (! o.isScalar())
                throw ArithmeticException();
            return Value(x + o.x);
        }
        if (o.isScalar())
            throw ArithmeticException();
        return Value(x+o.x, y+o.y, z+o.z);
    }
    Value operator-(const Value& o) const {
        if (s) {
            if (! o.isScalar())
                throw ArithmeticException();
            return Value(x - o.x);
        }
        if (o.isScalar())
            throw ArithmeticException();
        return Value(x-o.x, y-o.y, z-o.z);
    }
    Value operator*(const Value& o) const {
        if (s) {
            if (o.isScalar())
                return Value(x * o.x);
            return o*(*this);
        }
        if (o.isScalar())
            return Value(x*o.x, y*o.x, z*o.x);
        return Value(x*o.x + y*o.y + z*o.z);
    }
    Value operator%(const Value& o) const {
        if (s) {
            throw ArithmeticException();
        }
        if (o.isScalar())
            throw ArithmeticException();
        return Value(y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x);
    }
    void print() const {
        if (s)
            std::printf("%d", x);
        else
            std::printf("[%d,%d,%d]", x, y, z);
    }
};


char get_next(pchar& p) {
    while(*p == ' ' || *p == '\r' || *p == '\n')
        p++;
    return *p;
}

void ensure_chr(pchar& p, char ch) {
    if (get_next(p) != ch)
        throw SyntaxException();
}

int parse_int(pchar& p) {
    get_next(p);
    int v = 0;
    while('0' <= *p && *p <= '9') {
        v = v*10 + (int)(*p - '0');
        p++;
    }
    return v;
}

Value parse_expr(pchar& p);

Value parse_vector(pchar& p) {
    Value vx, vy, vz;
    ensure_chr(p, '['); p++;
    vx = parse_expr(p);
    ensure_chr(p, ','); p++;
    vy = parse_expr(p);
    ensure_chr(p, ','); p++;
    vz = parse_expr(p);
    ensure_chr(p, ']'); p++;
    if (!vx.isScalar() || !vy.isScalar() || !vz.isScalar())
        throw ArithmeticException();
    return Value(vx.x, vy.x, vz.x);
}

Value parse_value(pchar& p) {
    char ch = get_next(p);
    if (ch == '[') {
        return parse_vector(p);
    }
    if ('0' <= ch && ch <= '9') {
        return Value(parse_int(p));
    }
    if (ch == '(') {
        p++;
        Value value = parse_expr(p);
        ensure_chr(p, ')'); p++;
        return value;
    }
    throw SyntaxException();
}


Value parse_term(pchar& p) {
    Value value = parse_value(p);
    bool cont = true;
    do {
        switch(get_next(p)) {
        case '*':
            value = value * parse_value(++p);
            break;
        case 'x':
            value = value % parse_value(++p);
            break;
        default:
            cont = false;
            break;
        }
    } while(cont);
    return value;
}

Value parse_expr(pchar& p) {
    Value value = parse_term(p);
    bool cont = true;
    do {
        switch(get_next(p)) {
        case '+':
            value = value + parse_term(++p);
            break;
        case '-':
            value = value - parse_term(++p);
            break;
        default:
            cont = false;
            break;
        }
    } while(cont);
    return value;
}

void parse(pchar p) {
    try {
        Value value = parse_expr(p);
        ensure_chr(p, '\0');
        value.print();
        std::printf("\n");
    }
    catch(...) {
        std::printf("Bang!\n");
    }
}

int main() {
    while(true) {
        char buf[128];
        std::fgets(buf, sizeof(buf), stdin);
        if (buf[0] == '#')
            break;
        parse(buf);
    }
    return 0;
}
