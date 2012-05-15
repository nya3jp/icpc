/*
 * UVA 10485 Painting with CSE
 * 2005-08-25
 * by nya
 */

#include <cstdio>
#include <ctype.h>
#include <cstring>
#include <complex>
#include <vector>
#include <algorithm>
#include <functional>

#define N 10

typedef std::complex<int> Point;

const Point R(0, 1);

struct SyntaxError {};
struct InvalidOperation {};

inline bool in_range(int i, int l, int h) {
    return (l <= i && i < h);
}

struct Object {
    std::vector<Point> points;
    void append(const Object& o) {
        if (points.back() != o.points[0])
            throw InvalidOperation();
        points.insert(points.end(), o.points.begin()+1, o.points.end());
    }
    void rotate(int degree) {
        if (degree%90 != 0)
            throw InvalidOperation();
        int r = (degree / 90) % 4;
        if (r < 0) r += 4;
        for(int c=0; c<r; c++) {
            for(int i=0; i<(int)points.size(); i++) {
                points[i] *= R;
            }
        }
    }
    void transform(int dx, int dy) {
        Point p(dx, dy);
        for(int i=0; i<(int)points.size(); i++) {
            points[i] += p;
        }
    }
    void scale(int sx, int sy) {
        for(int i=0; i<(int)points.size(); i++) {
            points[i] = Point(points[i].real()*sx, points[i].imag()*sy);
        }
    }
    bool checkConsistency() {
        int n = points.size();
        for(int i=0; i<n-1; i++) {
            if (!(points[i].real() == points[i+1].real() || points[i].imag() == points[i+1].imag()))
                return false;
        }
        return true;
    }
};

struct ObjectList {
    std::vector<Object> objects;
    void push_back(const Object& obj) {
        objects.push_back(obj);
    }
    void merge(const ObjectList& o) {
        objects.insert(objects.end(), o.objects.begin(), o.objects.end());
    }
    void rotate(int degree) {
        for(int i=0; i<(int)objects.size(); i++)
            objects[i].rotate(degree);
    }
    void transform(int dx, int dy) {
        for(int i=0; i<(int)objects.size(); i++)
            objects[i].transform(dx, dy);
    }
    void scale(int sx, int sy) {
        for(int i=0; i<(int)objects.size(); i++)
            objects[i].scale(sx, sy);
    }
};

struct Raster {
    bool err;
    bool v[N][N];
    Raster() {
        clear();
    }
    void clear() {
        err = false;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                v[i][j] = false;
    }
    void setp(int x, int y) {
        if (in_range(x, 0, N) && in_range(y, 0, N))
            v[y][x] = true;
    }
    void draw(const Object& obj) {
        int n = obj.points.size();
        if (n == 1)
            setp(obj.points[0].real(), obj.points[0].imag());
        for(int i=0; i<n-1; i++) {
            const Point& p = obj.points[i];
            const Point& q = obj.points[i+1];
            if (p.real() == q.real()) {
                for(int j=std::min(p.imag(), q.imag()); j<=std::max(p.imag(), q.imag()); j++)
                    setp(p.real(), j);
            }
            if (p.imag() == q.imag()) {
                for(int j=std::min(p.real(), q.real()); j<=std::max(p.real(), q.real()); j++)
                    setp(j, p.imag());
            }
        }
    }
    void draw(const ObjectList& objlist) {
        for(int i=0; i<(int)objlist.objects.size(); i++) {
            draw(objlist.objects[i]);
        }
    }
    void print() {
        if (err) {
            for(int i=N-1; i>=0; i--) {
                for(int j=0; j<N; j++) {
                    std::printf("%c", (i==0 && j==0 ? '?' : '.'));
                }
                std::printf("\n");
            }
        }
        else {
            for(int i=N-1; i>=0; i--) {
                for(int j=0; j<N; j++) {
                    std::printf("%c", (v[i][j] ? '#' : '.'));
                }
                std::printf("\n");
            }
        }
    }
};


inline char readNext(const char* (&p)) {
    while(isspace(*p))
        p++;
    return *p;
}
inline bool matchNext(const char* (&p), char c) {
    if (readNext(p) == c) {
        p++;
        return true;
    }
    return false;
}
inline void assertNext(const char* (&p), char c) {
    if (readNext(p) != c)
        throw SyntaxError();
    p++;
}


ObjectList parseObjectList(const char* (&p));

int parseInteger(const char* (&p)) {
    int num = 0;
    bool negate = false;
    {
        char c = readNext(p);
        if (!isdigit(readNext(p)) && c != '-')
            throw SyntaxError();
        if (c == '-') {
            negate = true;
            p++;
        }
    }
    while(isdigit(*p)) {
        num = num*10 + (int)(*p - '0');
        p++;
    }
    if (negate)
        num = -num;
    return num;
}


Object parseObject(const char* (&p)) {
    Object obj;
    switch(readNext(p)) {
    case '[':
        assertNext(p, '[');
        do {
            assertNext(p, '(');
            int x = parseInteger(p);
            assertNext(p, ',');
            int y = parseInteger(p);
            assertNext(p, ')');
            obj.points.push_back(Point(x, y));
        } while(matchNext(p, ','));
        assertNext(p, ']');
        if (! obj.checkConsistency())
            throw InvalidOperation();
        break;
    case 'A':
        assertNext(p, 'A');
        assertNext(p, '(');
        obj = parseObject(p);
        assertNext(p, ',');
        obj.append(parseObject(p));
        assertNext(p, ')');
        break;
    default:
        throw SyntaxError();
    }
    return obj;
}


ObjectList parseTransform(const char* (&p)) {
    assertNext(p, 'T');
    assertNext(p, '(');
    int dx = parseInteger(p);
    assertNext(p, ',');
    int dy = parseInteger(p);
    assertNext(p, ',');
    ObjectList objlist = parseObjectList(p);
    assertNext(p, ')');
    objlist.transform(dx, dy);
    return objlist;
}
ObjectList parseScale(const char* (&p)) {
    assertNext(p, 'S');
    assertNext(p, '(');
    int sx = parseInteger(p);
    assertNext(p, ',');
    int sy = parseInteger(p);
    assertNext(p, ',');
    ObjectList objlist = parseObjectList(p);
    assertNext(p, ')');
    objlist.scale(sx, sy);
    return objlist;
}
ObjectList parseRotate(const char* (&p)) {
    assertNext(p, 'R');
    assertNext(p, '(');
    int degree = parseInteger(p);
    assertNext(p, ',');
    ObjectList objlist = parseObjectList(p);
    assertNext(p, ')');
    objlist.rotate(degree);
    return objlist;
}


ObjectList parseObjectList(const char* (&p)) {
    ObjectList objlist;
    do {
        switch(readNext(p)) {
        case '[':
        case 'A':
            objlist.push_back(parseObject(p));
            break;
        case 'T':
            objlist.merge(parseTransform(p));
            break;
        case 'S':
            objlist.merge(parseScale(p));
            break;
        case 'R':
            objlist.merge(parseRotate(p));
            break;
        default:
            throw SyntaxError();
        }
    } while(matchNext(p, 'u'));
    return objlist;
}


Raster parseCSE(const char* buf) {
    Raster raster;
    const char* p = buf;
    try {
        ObjectList objlist = parseObjectList(p);
        if (readNext(p) != '\0')
            throw SyntaxError();
        raster.draw(objlist);
    }
    catch(...) {
        /*
        std::printf("Error near \'%c\':\n", *p);
        std::printf("%s\n", buf);
        for(int i=0; i<(p-buf); i++)
            std::printf(" ");
        std::printf("~\n");
        */
        raster.err = true;
    }
    return raster;
}


void chomp(char* p) {
    int len = std::strlen(p);
    while(len > 0) {
        if (! isspace(p[len-1]))
            break;
        len--;
    }
    p[len] = '\0';
}


int main() {
    for(int iCase=0; ; iCase++) {
        char buf[1024];
        std::fgets(buf, sizeof(buf), stdin);
        chomp(buf);
        if (std::strcmp(buf, "#") == 0)
            break;
        std::printf("Set #%d\n", iCase+1);
        parseCSE(buf).print();
    }
    return 0;
}
