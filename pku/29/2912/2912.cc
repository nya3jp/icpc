#include <iostream>
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

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

#define N 500

const int UNKNOWN = -1;
const int IMPOSSIBLE = -2;

const char* SIGNS = "=<>";

struct UF {
    int parent;
    int delta;
};

UF uf[N][N];

void init_uf(UF* uf, int n) {
    REP(i, n) {
        uf[i].parent = -1;
        uf[i].delta = 0;
    }
}

UF find_root(UF* uf, int i) {
    UF res;
    if (uf[i].parent < 0) {
        res.parent = i;
        res.delta = 0;
    }
    else {
        res = find_root(uf, uf[i].parent);
        res.delta = (res.delta + uf[i].delta) % 3;
        uf[i] = res;
    }
    return res;
}

bool merge(UF* uf, int i, int j, int delta) {
    UF r1 = find_root(uf, i);
    UF r2 = find_root(uf, j);
    if (r1.parent == r2.parent) {
        if ((r2.delta + delta - r1.delta + 3)%3 != 0)
            return false;
    }
    else {
        // ri - i = r1.delta
        // rj - j = r2.delta
        // j - i = delta
        // rj - ri = r2.delta - r1.delta + delta
        assert(uf[r1.parent].delta == 0);
        uf[r1.parent].parent = r2.parent;
        uf[r1.parent].delta = (r2.delta - r1.delta + delta + 3) % 3;
    }
    return true;
}

int main() {

    int n, nRounds;
    while(cin >> n >> nRounds) {

        bool valid[N];
        REP(i, n)
            valid[i] = true;
        int nValids = n;

        int nJudgeTime = -1;

        if (n == 1)
            nJudgeTime = 0;

        REP(i, n)
            init_uf(uf[i], n);

        REP(iRound, nRounds) {
            int a, b;
            char outcome;
            scanf("%d%c%d", &a, &outcome, &b);

            int d = string(SIGNS).find(outcome);

            REP(c, n) {
                if (valid[c]) {
                    if (/*true || */c != a && c != b) {
                        if (!merge(uf[c], a, b, d)) {
                            //cout << "Assumption " << c << " was rejected by line " << iRound << endl;
                            valid[c] = false;
                            nValids--;
                            if (nValids == 1)
                                nJudgeTime = iRound+1;
                        }
                    }
                }
            }

            /*
            REP(c, n) {
                if (valid[c]) {
                    cout << "Assumuption " << c << ":";
                    REP(i, n) {
                        cout << "(" << uf[c][i].parent << "," << uf[c][i].delta << ")" ;
                    }
                    cout << endl;
                }
            }
            cout << endl;
            //*/
        }

        if (nValids == 0) {
            cout << "Impossible" << endl;
        }
        else if (nValids == 1) {
            int iJudge = find(valid, valid+n, true) - valid;
            cout << "Player " << iJudge << " can be determined to be the judge after " << nJudgeTime << " lines" << endl;
        }
        else {
            cout << "Can not determine" << endl;
        }


    }

    return 0;
}



// Powered by fate testarossa
