#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Swap {
    int h, p, q;
    friend bool operator<(const Swap& a, const Swap& b) {
        return a.h < b.h;
    }
};

int main() {
    int n, m, a;
    while(cin >> n >> m >> a && !(n == 0 && m == 0 && a == 0)) {
        a--;
        vector<Swap> v(m);
        for(int i = 0; i < m; i++) {
            Swap& s = v[i];
            cin >> s.h >> s.p >> s.q;
            s.p--;
            s.q--;
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        int pos = a;
        for(int i = 0; i < m; i++) {
            //cout << pos+1 << endl;
            Swap& s = v[i];
            if (pos == s.p)
                pos = s.q;
            else if (pos == s.q)
                pos = s.p;
        }
        pos++;
        cout << pos << endl;
    }
    return 0;
}
