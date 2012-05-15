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

int main() {
    ifstream cin("B.txt");

    const char* HANDS[] = {
        "Rock",
        "Gun",
        "Lightning",
        "Devil",
        "Dragon",
        "Water",
        "Air",
        "Paper",
        "Sponge",
        "Wolf",
        "Tree",
        "Human",
        "Snake",
        "Scissors",
        "Fire",
    };

    int n;
    while(cin >> n && n > 0) {
        vector<bool> v(15, false);
        REP(i,n) {
            string s;
            cin >> s;
            int h = -1;
            REP(j, 15)
                if (s == HANDS[j])
                    h = j;
            assert(h >= 0);
            v[h] = true;
        }
        int res = -1;
        REP(i, 15) {
            if (v[i]) {
                //cout << HANDS[i] << ":";
                bool ok = true;
                for(int d = 1; d <= 7; d++) {
                    int j = (i+d)%15;
                    if (v[j]) {
                        ok = false;
                        //cout << HANDS[j] << ' ';
                    }
                }
                if (!ok)
                    continue;
                ok = false;
                for(int d = 8; d <= 14; d++) {
                    int j = (i+d)%15;
                    if (v[j]) {
                        ok = true;
                    }
                }
                if (ok) {
                    //cout << "OK" << endl;
                    res = i;
                    break;
                }
                //cout << endl;
            }
        }
        if (res < 0) {
            cout << "Draw" << endl;
        }
        else {
            cout << HANDS[res] << endl;
        }
    }

    return 0;
}

// Powered by Fate Testarossa
