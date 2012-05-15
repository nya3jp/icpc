#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool walk(vector<string>& field, vector< vector<bool> >& accept, int defi, int defj, int dir) {

    const int h = field.size()-2, w = field[0].size()-2;
    const int DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for(int i = defi, j = defj; 1 <= i && i <= h && 1 <= j && j <= w; ) {

        /*
        for(int a = 1; a <= h; a++) {
            string s = field[a];
            if (i == a)
                s[j] = '@';
            cout << s << endl;
        }
        for(int x = 0; x < 30000000; x++);
        */

        if (accept[i][j])
            return true;
        int di = DIRS[dir][0], dj = DIRS[dir][1];
        int ri = DIRS[(dir+3)%4][0], rj = DIRS[(dir+3)%4][1];
        if (field[i+di][j+dj] == 'X') {
            dir = (dir+1)%4;
        }
        else {
            i += di; j += dj;
            if (field[i+ri][j+rj] != 'X') {
                dir = (dir+3)%4;
                i += ri; j += rj;
            }
        }
    }

    return false;
}

int main() {

    while(true) {
        int w, h;
        {
            string line;
            getline(cin, line);
            sscanf(line.c_str(), "%d%d", &w, &h);
            if (w < 3 || h < 3)
                break;
        }

        vector<string> field(h+2, string(w+2, ' '));

        for(int i = 0; i < h; i++) {
            string s;
            getline(cin, s);
            if (s.length() > w)
                s = s.substr(0, w);
            else if (s.length() < w)
                s = s + string(w-s.length(), 'X');
            field[i+1] = string(1, ' ') + s + string(1, ' ');
        }

        vector< vector<bool> > accept(h+2, vector<bool>(w+2, false));

        for(int i = 1; i <= h; i++) {
            for(int j = 1; j <= w; j++) {
                if (field[i][j] == 'G') {
                    for(int ii = i; ii >= 0 && field[ii][j] != 'X'; ii--)
                        accept[ii][j] = true;
                    for(int ii = i; ii < h+2 && field[ii][j] != 'X'; ii++)
                        accept[ii][j] = true;
                    for(int jj = j; jj >= 0 && field[i][jj] != 'X'; jj--)
                        accept[i][jj] = true;
                    for(int jj = j; jj < w+2 && field[i][jj] != 'X'; jj++)
                        accept[i][jj] = true;
                }
            }
        }

        int num = 0, denom = 0;

        for(int i = 1, j = 1; j <= w; j++) {
            if (field[i][j] == 'E') {
                denom++;
                if (walk(field, accept, i, j, 0))
                    num++;
            }
        }

        for(int i = 1, j = 1; i <= h; i++) {
            if (field[i][j] == 'E') {
                denom++;
                if (walk(field, accept, i, j, 1))
                    num++;
            }
        }

        for(int i = h, j = 1; j <= w; j++) {
            if (field[i][j] == 'E') {
                denom++;
                if (walk(field, accept, i, j, 2))
                    num++;
            }
        }

        for(int i = 1, j = w; i <= h; i++) {
            if (field[i][j] == 'E') {
                denom++;
                if (walk(field, accept, i, j, 3))
                    num++;
            }
        }

        cout << "The goal would be found from " << num << " out of " << denom << " entrances." << endl;

    }

    return 0;
}

