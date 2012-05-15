#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

#define N 1000

char board[N+4][N+4];
int h, w;

bool dot(int i, int j) {
    if (board[i][j] == '.' || board[i][j] == ' ') {
        board[i][j] = '.';
        return true;
    }
    return false;
}

int main() {

    int iCase = 0;
    
    for(;;) {
        cin >> h >> w;
        if (h == 0 && w == 0)
            break;
        h += 4;
        w += 4;
        REP(i, h) REP(j, w)
            board[i][j] = ' ';
        REP(i, h) {
            board[i][0] = board[i][w-1] = 'P';
            board[i][1] = board[i][w-2] = 'P';
        }
        REP(j, w) {
            board[0][j] = board[h-1][j] = 'P';
            board[1][j] = board[h-2][j] = 'P';
        }

        {
            int n;
            cin >> n;
            REP(i, n) {
                int a, b;
                cin >> a >> b;
                a++; b++;
                board[a][b] = 'Q';
            }
        }
        {
            int n;
            cin >> n;
            REP(i, n) {
                int a, b;
                cin >> a >> b;
                a++; b++;
                board[a][b] = 'K';
            }
        }
        {
            int n;
            cin >> n;
            REP(i, n) {
                int a, b;
                cin >> a >> b;
                a++; b++;
                board[a][b] = 'P';
            }
        }

        REP(i, h) REP(j, w) {
            switch(board[i][j]) {
            case 'Q':
                for(int s = 1; ; s++) {
                    int ii = i + s;
                    int jj = j;
                    if (!dot(ii, jj))
                        break;
                }
                for(int s = 1; ; s++) {
                    int ii = i - s;
                    int jj = j;
                    if (!dot(ii, jj))
                        break;
                }
                for(int s = 1; ; s++) {
                    int ii = i;
                    int jj = j + s;
                    if (!dot(ii, jj))
                        break;
                }
                for(int s = 1; ; s++) {
                    int ii = i;
                    int jj = j - s;
                    if (!dot(ii, jj))
                        break;
                }
                for(int s = 1; ; s++) {
                    int ii = i + s;
                    int jj = j + s;
                    if (!dot(ii, jj))
                        break;
                }
                for(int s = 1; ; s++) {
                    int ii = i + s;
                    int jj = j - s;
                    if (!dot(ii, jj))
                        break;
                }
                for(int s = 1; ; s++) {
                    int ii = i - s;
                    int jj = j + s;
                    if (!dot(ii, jj))
                        break;
                }
                for(int s = 1; ; s++) {
                    int ii = i - s;
                    int jj = j - s;
                    if (!dot(ii, jj))
                        break;
                }
                break;
            case 'K':
                dot(i+2, j+1);
                dot(i+1, j+2);
                dot(i-1, j+2);
                dot(i-2, j+1);
                dot(i-2, j-1);
                dot(i-1, j-2);
                dot(i+1, j-2);
                dot(i+2, j-1);
                break;
            }
        }

        /*
        REP(i, h) {
            REP(j, w)
                cout << board[i][j];
            cout << endl;
        }
        //*/

        int res = 0;
        REP(i, h) REP(j, w)
            if (board[i][j] == ' ')
                res++;
        cout << "Board " << ++iCase << " has " << res << " safe squares." << endl;
    }
    
    return 0;
}
