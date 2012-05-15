#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int INF = numeric_limits<int>::max();

bool check(vector< vector<int> >& field, int c, vector<bool>& used) {
    int h = field.size();
    int w = field[0].size();

    int ymin=INF, ymax=0, xmin=INF, xmax=0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            int a = field[i][j];
            if (a == c) {
                ymin = min(ymin, i);
                ymax = max(ymax, i);
                xmin = min(xmin, j);
                xmax = max(xmax, j);
            }
        }
    }

    for(int i = ymin; i <= ymax; i++) {
        for(int j = xmin; j <= xmax; j++) {
            if (field[i][j] == c ||
                used[field[i][j]]) {
                // do nothing
            }
            else {
                return false;
            }
        }
    }
    return true;
}

bool solve() {
    int h, w;
    cin >> h >> w;
    vector< vector<int> > field(h, vector<int>(w, 0));
    vector<bool> exists(26, false);
    for(int i = 0; i < h; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < w; j++) {
            if (s[j] == '.') {
                field[i][j] = -1;
            }
            else {
                int c = s[j] - 'A';
                field[i][j] = c;
                exists[c] = true;
            }
        }
    }

    vector<bool> used(26, false);
    while(true) {
        bool ok = true;
        for(int i = 0; i < 26; i++) {
            if (exists[i] && !used[i])
                ok = false;
        }
        if (ok)
            break;

        ok = false;
        for(int i = 0; i < 26; i++) {
            if (exists[i] && !used[i]) {
                //cout << "removing " << i << endl;
                bool b = check(field, i, used);
                if (b) {
                    //cout << "success" << endl;
                    used[i] = true;
                    ok = true;
                    break;
                }
            }
        }
        if (!ok)
            return false;

    }

    return true;
}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        cout << (!solve() ? "SUSPICIOUS" : "SAFE") << endl;
    return 0;
}

