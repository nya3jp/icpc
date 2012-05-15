#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

#define REP(i,n) for(int i = 0 ; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

#define SEND(i,j,c) {sends[i] += c; receives[j] += c; /*printf("%d to %d: %d\n", i, j, c);*/}

int main() {
    ifstream cin("C.txt");

    bool first = true;

    int nPlayers, nProblems;
    while(cin >> nPlayers >> nProblems && !(nPlayers == 0 && nProblems == 0)) {

        if (!first)
            cout << endl;
        first = false;

        vector<int> sends(nPlayers+1, 0), receives(nPlayers+1, 0), delays(nPlayers);
        REP(i, nPlayers)
            cin >> delays[i];

        REP(iProblem, nProblems) {

            vector< vector<int> > answers_by_time(20);
            vector<int> answers_by_player(nPlayers);
            int nSubmissions;
            cin >> nSubmissions;
            REP(i, nSubmissions) {
                int id, time, len;
                string s;
                cin >> id >> time >> s;
                len = s.size();
                answers_by_time[(time+delays[id]*2)/1000].push_back(id);
                answers_by_player[id] = len;
            }

            vector<bool> answered(nPlayers, false);
            vector< vector<int> > knows(nPlayers, vector<int>(nPlayers, 0));
            REP(i, nPlayers)
                knows[i][i] = 3;

            REP(i, nPlayers)
                SEND(nPlayers, i, 3); // synchro

            REP(iTime, 20) {
                FOR(it, answers_by_time[iTime]) {
                    answered[*it] = true;
                    SEND(*it, nPlayers, (3+1+1+answers_by_player[*it]));
                }
                REP(iPlayer, nPlayers) {
                    if (answered[iPlayer]) {
                        int size = 0;
                        REP(i, nPlayers) {
                            if ((knows[iPlayer][i]&2) == 0 && answered[i]) {
                                size += 1 + 1 + answers_by_player[i];
                                knows[iPlayer][i] |= 2;
                            }
                        }
                        if (size > 0) {
                            //printf("B ");
                            SEND(nPlayers, iPlayer, (3+1+size));
                        }
                    }
                    else {
                        int size = 0;
                        REP(i, nPlayers) {
                            if ((knows[iPlayer][i]&1) == 0 && answered[i]) {
                                size += 1;
                                knows[iPlayer][i] |= 1;
                            }
                        }
                        if (size > 0) {
                            //printf("A ");
                            SEND(nPlayers, iPlayer, (3+1+size));
                        }
                    }
                }
            }

            REP(i, nPlayers)
                SEND(nPlayers, i, (3+1)); // synchro

        }

        cout << sends[nPlayers] << ' ' << receives[nPlayers] << endl;
        REP(i, nPlayers)
            cout << sends[i] << ' ' << receives[i] << endl;

    }

    return 0;
}

// Powered by Fate Testarossa
