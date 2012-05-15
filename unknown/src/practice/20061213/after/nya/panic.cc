#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 20

int adj[N][N];
int ints;

inline bool at(int bits, int pos) {
    return ((bits & (1<<pos)) != 0);
}

void solve() {

    int nRooms, iPanicRoom;
    cin >> nRooms >> iPanicRoom;

    REP(i, nRooms) REP(j, nRooms)
        adj[i][j] = 0;
    ints = 0;

    REP(iRoom, nRooms) {
        string intruder;
        cin >> intruder;
        if (intruder == "I")
            ints |= 1<<iRoom;

        int nDoors;
        cin >> nDoors;
        REP(i, nDoors) {
            int iNextRoom;
            cin >> iNextRoom;
            adj[iRoom][iNextRoom]++;
        }
    }

    const int IMPOSSIBLE = 10000000;
    int res = IMPOSSIBLE;
    REP(secure, 1<<nRooms) {
        if (at(secure, iPanicRoom) && ((secure & ints) == 0)) {
            int local = 0;
            REP(i, nRooms) REP(j, nRooms) {
                if (!at(secure, i) && at(secure, j)) {
                    if (adj[i][j] > 0)
                        local = IMPOSSIBLE;
                    local += adj[j][i];
                }
            }
            res <?= local;
        }
    }

    if (res == IMPOSSIBLE) {
        cout << "PANIC ROOM BREACH" << endl;
    }
    else {
        cout << res << endl;
    }

}



int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}
