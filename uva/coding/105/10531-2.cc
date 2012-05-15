#include <cstdio>

using namespace std;

typedef unsigned int uint;

int h, w;
int leftmask, rightmask;

void setmask() {
    leftmask = rightmask = 0;
    return;
    leftmask = rightmask = 0xffffffffu;
    for(int r = 0; r < h; r++) {
        leftmask &= ~(1 << (r*w));
        rightmask &= ~(1 << (r*w+w-1));
    }
}

void found(int floor) {
}

void search(int r, int floor, int reachable) {
    if (r == h) {
        if ((reachable&(1<<(w*h-1))) != 0)
            found(floor);
    }
    else if (r == 0) {
        for(int p = 0; p < (1<<w); p++) {
            if ((p&1) == 0)
                continue;
            int newfloor = p;
            int newreachable = 1;
            for(int i = 0; i < w; i++)
                newreachable |= (newreachable << 1) & newfloor;
            search(r+1, newfloor, newreachable);
        }
    }
    else {
        for(int p = 0; p < (1<<w); p++) {
            int newfloor = floor | (p << (r*w));
            int newreachable = reachable;
            for(int i = 0; i < (r+1)*w; i++) {
                newreachable |= ((newreachable & leftmask) >> 1) & newfloor;
                newreachable |= ((newreachable & rightmask) << 1) & newfloor;
                newreachable |= (newreachable << w) & newfloor;
                newreachable |= (newreachable >> w) & newfloor;
            }
            int thisline = ((1<<w)-1) << (r*w);
            if ((newreachable & thisline) != 0)
                search(r+1, newfloor, newreachable);
        }
    }
}

int main() {
    w = 5;
    h = 6;
    setmask();
    search(0, 0, 0);
    return 0;
}
