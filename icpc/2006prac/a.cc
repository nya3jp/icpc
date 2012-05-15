#include <iostream>
#include <string>
#include <numeric>

using namespace std;

#define N 21

int field[N][N];

int main() {
    int n;
    while(cin >> n && n > 0) {
        for(int i = 0; i < N; i++) {
            fill(field[i], field[i]+N, 0);
        }
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            field[x][y] = 1;
        }

        int px=10, py=10;
        int m;
        field[px][py] = 0;
        cin >> m;
        for(int i = 0; i < m; i++) {
            char c;
            int len;
            cin >> c >> len;
            for(int j = 0; j < len; j++) {
                switch(c) {
                case 'N': py++; break;
                case 'E': px++; break;
                case 'S': py--; break;
                case 'W': px--; break;
                }
                field[px][py] = 0;
            }
        }

        int s = 0;
        for(int i = 0; i < N; i++)
            s += accumulate(field[i], field[i]+N, (int)0);
        cout << (s == 0 ? "Yes" : "No") << endl;
    }
    return 0;
}

