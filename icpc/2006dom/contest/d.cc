#include <iostream>

using namespace std;

#define N 20

struct Field {
    int w, h;
    bool field[N][N];
    int gx, gy;
};

inline bool in_range(int a, int low, int high) {
    return (low <= a && a < high);
}

bool search(int depth, int limit, Field& f, int cx, int cy) {

    int DIRS[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    if (depth >= limit)
        return false;

    /*
    cout << "--------------------" << endl;
    cout << "depth=" << depth << endl;
    for(int y = 0; y < f.h; y++) {
        for(int x = 0; x < f.w; x++) {
            if (x == cx && y == cy)
                cout << "@ ";
            else 
                cout << f.field[x][y] << ' ';
        }
        cout << endl;
    }
    */

    for(int dir = 0; dir < 4; dir++) {
        //cout << "dir=" << dir << endl;
        int dx = DIRS[dir][0];
        int dy = DIRS[dir][1];
        if (in_range(cx+dx, 0, f.w) && in_range(cy+dy, 0, f.h) &&
            (!f.field[cx+dx][cy+dy])) {
            int l;
            for(l = 1; ; l++) {
                int mx = cx+dx*l;
                int my = cy+dy*l;
                if ((!in_range(mx, 0, f.w)) || (!in_range(my, 0, f.h))) {
                    //cout << "reject2" << mx << ',' << my << endl;
                    goto MISSED;
                }
                if (mx == f.gx && my == f.gy)
                    return true;
                if (f.field[mx][my])
                    break;
            }
            l--;
            f.field[cx+dx*(l+1)][cy+dy*(l+1)] = false;
            if (search(depth+1, limit, f, cx+dx*l, cy+dy*l))
                return true;
            f.field[cx+dx*(l+1)][cy+dy*(l+1)] = true;
        }
        else {
            //cout << "reject1" << endl;
        }
    MISSED:
        ;
    }

    return false;
}


int search(Field& f, int cx, int cy) {
    for(int limit = 1; limit <= 10; limit++) {
        if (search(0, limit, f, cx, cy))
            return limit;
    }
    return -1;
}

int main() {

    Field f;
    while(cin >> f.w >> f.h && !(f.w == 0 && f.h == 0)) {

        int cx = -1, cy = -1;
        for(int y = 0; y < f.h; y++) {
            for(int x = 0; x < f.w; x++) {
                int t;
                cin >> t;
                if (t == 2) {
                    cx = x;
                    cy = y;
                    t = 0;
                }
                else if (t == 3) {
                    f.gx = x;
                    f.gy = y;
                    t = 0;
                }
                f.field[x][y] = (t > 0);
            }
        }

        assert(cx >= 0 && cy >= 0);

        cout << search(f, cx, cy) << endl;

    }

    return 0;
}
