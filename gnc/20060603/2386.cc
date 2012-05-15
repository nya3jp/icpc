#include <iostream>
#include <string>
#include <vector>

using namespace std;


void floodfill(vector<string>& field, int i, int j) {
    if (field[i][j] == 'W') {
        field[i][j] = '*';
        for(int di = -1; di <= 1; di++) {
            for(int dj = -1; dj <= 1; dj++) {
                int ii = i + di;
                int jj = j + dj;
                floodfill(field, ii, jj);
            }
        }
    }
}

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> field(h+2, string(w+2, '.'));
    for(int i = 0; i < h; i++) {
        string s;
        cin >> s;
        field[i+1] = string(1, '.') + s + string(1, '.');
    }
    int n = 0;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            if (field[i][j] == 'W') {
                floodfill(field, i, j);
                n++;
            }
        }
    }
    cout << n << endl;
    return 0;
}

