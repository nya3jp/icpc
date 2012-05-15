#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

bool valid[1<<18];
int board[9];

#define SAME(a,b,c) (board[a] == board[b] && board[a] == board[c] && board[a] > 0)
void search(int d) {
    if (SAME(0, 1, 2) || SAME(3, 4, 5) || SAME(6, 7, 8) ||
        SAME(0, 3, 6) || SAME(1, 4, 7) || SAME(2, 5, 8) ||
        SAME(0, 4, 8) || SAME(2, 4, 6) || d == 9)
    {
        int s = 0;
        REP(i, 9)
            s |= board[i]<<(i*2);
        valid[s] = true;
    }
    else {
        REP(i, 9) {
            if (board[i] == 0) {
                board[i] = (d&1)+1;
                search(d+1);
                board[i] = 0;
            }
        }
    }
}

int main() {

    {
        REP(i, 1<<18)
            valid[i] = false;
        REP(i, 9)
            board[i] = 0;
        search(0);
    }

    for(string line; getline(cin, line), line != "end"; ) {
        int s = 0;
        REP(i, 9)
            s |= (line[i] == 'X' ? 1 : line[i] == 'O' ? 2 : 0) << (i*2);
        cout << (valid[s] ? "valid" : "invalid") << endl;
    }

    return 0;
}
