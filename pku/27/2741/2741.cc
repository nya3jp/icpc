#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;


#define N 4


// 立方体を回転させる
// r = 0~23
void rotate_die(int* src, int* dest, int r) {
    int p[6] = {0, 1, 2};
    int t = r/4, s = r%4;
    p[0] += t;
    p[1] += (t+1)/2*2;
    p[2] += t/2*2;
    for(int i = 0; i < 3; i++) {
        p[i] %= 6;
        p[3+i] = (p[i]+3)%6;
    }
    rotate(p+3, p+4, p+6);
    rotate(p+1, p+1+s, p+5);
    rotate(p+3, p+5, p+6);
    for(int i = 0; i < 6; i++)
        dest[i] = src[p[i]];
}

int pow(int a, int n) {
    int r = 1;
    while(n-- > 0)
        r *= a;
    return r;
}

int solve(int (*dice)[6], int n) {
    int best = numeric_limits<int>::max();

    int ptns = pow(24, n-1);
    for(int ptn = 0; ptn < ptns; ptn++) {
        int POS[N] = {0};
        for(int t = ptn, i = 1; i < n; i++, t/=24)
            POS[i] = t%24;
        int newdice[N][6];
        for(int i = 0; i < n; i++)
            rotate_die(dice[i], newdice[i], POS[i]);
        int paints = 0;
        for(int j = 0; j < 6; j++) {
            int colors[N+1];
            for(int i = 0; i < n; i++)
                colors[i] = newdice[i][j];
            sort(colors, colors+n);
            colors[n] = -1;
            int p = 0;
            int t = 1;
            for(int i = 1; i <= n; i++) {
                if (colors[i] != colors[i-1]) {
                    p = max(p, t);
                    t = 1;
                }
                else {
                    t++;
                }
            }
            paints += n-p;
        }
        best = min(best, paints);
    }

    return best;
}

map<string, int> colorMap;

int colorIndex(const string& s) {
    if (colorMap.count(s) == 0)
        colorMap.insert(make_pair(s, (int)colorMap.size()));
    return colorMap[s];
}

int main() {
    const int TRANS[6] = {0, 1, 2, 5, 4, 3};
    int n;
    while(cin >> n && n > 0) {
        int dice[N][6];
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 6; j++) {
                string s;
                cin >> s;
                dice[i][TRANS[j]] = colorIndex(s);
            }
        }
        cout << solve(dice, n) << endl;
    }
    return 0;
}

