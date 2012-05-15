#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PLAYERS 100
#define GAMES 1000

int score[PLAYERS][GAMES];
int table[PLAYERS*GAMES];

int maximize(const int* myscore, const int* theirscore, int nGames) {
    int res = 0;
    int iMy = 0, iTheir = 0;
    while(iMy < nGames && iTheir < nGames) {
        while(!(myscore[iMy] > theirscore[iTheir]) && iTheir < nGames)
            iTheir++;
        if (iTheir < nGames) {
            res++;
            iMy++;
            iTheir++;
        }
    }
    return res;
}

int minimize(const int* myscore, const int* theirscore, int nGames) {
    int res = nGames;
    int iMy = 0, iTheir = 0;

    while(iMy < nGames && iTheir < nGames) {
        while(!(myscore[iMy] <= theirscore[iTheir]) && iMy < nGames)
            iMy++;
        if (iMy < nGames) {
            res--;
            iMy++;
            iTheir++;
        }
    }
    return res;

    /*
    int myscore2[GAMES], theirscore2[GAMES];
    REP(i, nGames)
        myscore2[nGames-1-i] = -myscore[i];
    REP(i, nGames)
        theirscore2[nGames-1-i] = -theirscore[i];
    return maximize(myscore2, theirscore2, nGames);
    */
}


int main() {

    ifstream cin("b.in");

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        int nPlayers, nGames;
        cin >> nPlayers >> nGames;

        REP(i, nPlayers) REP(j, nGames)
            cin >> score[i][j];

        REP(i, nPlayers)
            sort(score[i], score[i]+nGames, greater<int>());

        int maxs[PLAYERS];
        int mins[PLAYERS];

        // maximum
        REP(iPlayer, nPlayers) {

            int res = nGames;
            REP(jPlayer, nPlayers) {
                if (jPlayer == iPlayer)
                    continue;

                res <?= maximize(score[iPlayer], score[jPlayer], nGames);
            }

            maxs[iPlayer] = res;

        }

        // minimum
        REP(iPlayer, nPlayers) {

            {
                int pos = 0;
                REP(jPlayer, nPlayers) {
                    if (jPlayer == iPlayer)
                        continue;
                    REP(i, nGames)
                        table[pos++] = score[jPlayer][i];
                }
            }

            partial_sort(table, table+nGames, table+nGames*(nPlayers-1), greater<int>());

            /*
            cout << iPlayer << " vs others" << endl;
            REP(i, nGames)
                cout << table[i] << ' ';
            cout << endl;
            */

            mins[iPlayer] = minimize(score[iPlayer], table, nGames);

        }

        REP(iPlayer, nPlayers)
            cout << mins[iPlayer] << ' ' << maxs[iPlayer] << endl;

    }

    return 0;
}



