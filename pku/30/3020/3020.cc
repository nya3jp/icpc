#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

int w, h;
string field;
int mem[400][1024];

int f(int pos, int used) {
    //printf("f(%d,%d) ", pos, used);
    if (pos == w*h)
        return 0;
    int& res = mem[pos][used];
    if (res < 0) {
        if (field[pos] == '*' && (used&1) == 0) {
            if (pos%w == w-1)
                res = f(pos+1, (used>>1)|(1<<(w-1))) + 1;
            else
                res = min(f(pos+2, used>>2) + 1,
                          f(pos+1, (used>>1)|(1<<(w-1))) + 1);
        }
        else {
            res = f(pos+1, used>>1);
        }
    }
    //printf("f(%d,%d) = %d\n", pos, used, res);
    return res;
}

void solve() {
    cin >> h >> w >> ws;
    field.clear();
    REP(i, h) {
        string s;
        getline(cin, s);
        field += s;
    }
    //cout << field << endl;
    REP(i, w*h) REP(j, 1<<w) mem[i][j] = -1;
    cout << f(0, 0) << endl;
}

int main() {
    int n;
    cin >> n;
    while(n-- > 0)
        solve();
    return 0;
}
