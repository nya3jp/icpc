#include <iostream>
#include <vector>

using namespace std;

struct Rect {
    int left, bottom, right, top;
};

int main() {
    int width, height, n;
    cin >> width >> height >> n;
    vector<Rect> v(n);
    for(int i = 0; i < n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        Rect& rc = v[i];
        rc.left = x-r;
        rc.right = x+r;
        rc.bottom = y-r;
        rc.top = y+r;
    }

ONCEMORE:
    for(int i = 0; i < n; i++) {
        Rect& r1 = v[i];
        for(int j = i+1; j < n; j++) {
            Rect& r2 = v[j];
            if (!(r1.right < r2.left || r2.right < r1.left ||
                  r1.top < r2.bottom || r2.top < r1.bottom))
            {
                Rect r0;
                r0.left = min(r1.left, r2.left);
                r0.bottom = min(r1.bottom, r2.bottom);
                r0.right = max(r1.right, r2.right);
                r0.top = max(r1.top, r2.top);
                r1 = r0;
                v.erase(v.begin()+j, v.begin()+j+1);
                n--;
                goto ONCEMORE;
            }
        }
    }

    int area = 0;
    for(int i = 0; i < n; i++) {
        Rect& r = v[i];
        area += (r.right-r.left)*(r.top-r.bottom);
    }

    cout << (width*height - area) << endl;

    return 0;
}
