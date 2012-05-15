#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

typedef const char* sptr;

vector<string> field;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

void parse(sptr& p, int& w, int& h, int x, int y, bool render) {
    if (render) {
        //printf("render (%d,%d)-(%d,%d)\n", x, y, x+w-1, y+h-1);
    }
    if ((p[0] == '0' && p[1] == '0') || (p[0] == '1' && p[1] == '1')) {
        bool black = p[0] == '0';
        p += 2;
        if (render) {
            if (black) {
                assert(w == h);
                for(int dy = 0; dy < h; dy++)
                    fill(field[y+dy].begin()+x, field[y+dy].begin()+x+w, 'X');
            }
        }
        else {
            w = 1; h = 1;
        }
    }
    else if (p[0] == '1' && p[1] == '0') {
        // horizontal split
        p += 2;
        sptr q(p);
        int lw, lh, rw, rh;
        parse(p, lw, lh, 0, 0, false);
        parse(p, rw, rh, 0, 0, false);
        int g = gcd(lh, rh);
        int sl = rh / g;
        int sr = lh / g;
        int lw2 = lw*sl;
        int lh2 = lh*sl;
        int rw2 = rw*sr;
        int rh2 = rh*sr;
        if (render) {
            int ssl = h/lh2;
            int ssr = h/rh2;
            lw2 *= ssl;
            lh2 *= ssl;
            rw2 *= ssr;
            rh2 *= ssr;
            parse(q, lw2, lh2, x, y, true);
            parse(q, rw2, rh2, x+lw2, y, true);
        }
        else {
            w = lw2 + rw2;
            h = lh2;
            assert(lh2 == rh2);
        }
    }
    else if (p[0] == '0' && p[1] == '1') {
        // vertical split
        p += 2;
        sptr q(p);
        int lw, lh, rw, rh;
        parse(p, lw, lh, 0, 0, false);
        parse(p, rw, rh, 0, 0, false);
        int g = gcd(lw, rw);
        int sl = rw / g;
        int sr = lw / g;
        int lw2 = lw*sl;
        int lh2 = lh*sl;
        int rw2 = rw*sr;
        int rh2 = rh*sr;
        if (render) {
            int ssl = w/lw2;
            int ssr = w/rw2;
            lw2 *= ssl;
            lh2 *= ssl;
            rw2 *= ssr;
            rh2 *= ssr;
            parse(q, lw2, lh2, x, y, true);
            parse(q, rw2, rh2, x, y+lh2, true);
        }
        else {
            w = lw2;
            h = lh2 + rh2;
            assert(lw2 == rw2);
        }
    }
}


int main() {
    for(string s; getline(cin, s) && !s.empty(); ) {
        int w, h;
        {
            const char* p = s.c_str();
            parse(p, w, h, 0, 0, false);
        }
        field.assign(h, string(w, ' '));
        {
            const char* p = s.c_str();
            parse(p, w, h, 0, 0, true);
        }
        cout << string(w+2, '-') << endl;
        for(int i = 0; i < h; i++) {
            cout << '|';
            cout << field[i];
            cout << '|' << endl;
        }
        cout << string(w+2, '-') << endl;
    }
    return 0;
}
