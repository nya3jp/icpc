#include <iostream>
#include <vector>

using namespace std;

int main() {
    int nRows, nCols;
    while(cin >> nRows >> nCols && !(nRows == 0 && nCols == 0)) {
        vector< vector<int> > v(nRows+4, vector<int>(nCols+4, -3));
        for(int i = 1; i < nRows+3; i++)
            for(int j = 1; j < nCols+3; j++)
                v[i][j] = -1;
        for(int i = 0; i < nRows; i++) {
            for(int j = 0; j < nCols; j++) {
                int t;
                cin >> t;
                v[i+2][j+2] = (t == 1 ? 0 : -1);
            }
        }
        int id = 0;
        for(int i = 2; i < nRows+2; i++) {
            for(int j = 2; j < nCols+2; j++) {
                if ((v[i-1][j] == -1 && v[i][j] == 0 && v[i+1][j] == 0) ||
                    (v[i][j-1] == -1 && v[i][j] == 0 && v[i][j+1] == 0))
                    v[i][j] = ++id;
            }
        }

        queue<pair<int,int> > q;
        q.push(make_pair(1, 1));
        while(!q.empty()) {
            int x = q.top().first;
            int y = q.top().second;
            q.pop();
            if (v[x][y] == -1) {
                v[x][y] = -2;
                if (v[x-1][y] == -1)
                    q.push(make_pair(x-1, y));
                if (v[x+1][y] == -1)
                    q.push(make_pair(x+1, y));
                if (v[x][y-1] == -1)
                    q.push(make_pair(x, y-1));
                if (v[x][y+1] == -1)
                    q.push(make_pair(x, y+1));
            }
        }

        for(int i = 0; i <= nRows; i++) {
            for(int j = 0; j < nCols; j++) {
                if (v[i+2][j+2] == -2 && v[i+2][j+2] == -2) {
                }
            }
            if (i < nRows) {
            }
        }

    }
    return 0;
}
