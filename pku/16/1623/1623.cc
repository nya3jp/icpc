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

#define ever (;;)

#define N 128

bool field[N][N];
bool term[8][N][N];
bool valid[8][N][N];

int main() {

    // May fate be with you!

    for ever {

        int h, w;
        cin >> h >> w;

        if (h == 0 && w == 0)
            break;

        const int deg = (int)(ceil(log2((double)max(h, w))-1.0e-8) + 1.0e-8);
        int n = 1<<deg;

        REP(i, n) REP(j, n)
            field[i][j] = 0;

        REP(i, h) {
            string line;
            cin >> line;
            REP(j, w)
                field[i][j] = (line[j] == '1');
        }

        REP(i, n) {
            REP(j, n)
                cout << field[i][j];
            cout << endl;
        }

        int res1 = 0;
        for(int d = deg; d >= 0; d--) {
            int nBlocks = 1<<(deg-d);
            int blockSize = 1<<d;
            REP(bi, nBlocks) REP(bj, nBlocks) {
                bool& tm = term[d][bi][bj];
                bool& vl = valid[d][bi][bj];
                if (d == deg || !term[d+1][bi/2][bj/2]) {
                    vl = true;
                    bool base = field[bi*blockSize][bj*blockSize];
                    tm = true;
                    REP(i, blockSize) REP(j, blockSize)
                        if (field[bi*blockSize+i][bj*blockSize+j] != base)
                            tm = false;
                    res1++;
                }
                else {
                    vl = false;
                    tm = true;
                }
            }
        }

        int res2 = 0;
        for(int d = deg; d >= 0; d--) {
            int nBlocks = 1<<(deg-d);
            int blockSize = 1<<d;
            REP(bi, nBlocks) REP(bj, nBlocks) {
                bool& tm = term[d][bi][bj];
                bool& vl = valid[d][bi][bj];
                if (vl) {
                    if (d < deg && term[d+1][bi/2][bj/2]) {
                        tm = true;
                    }
                    else {
                        bool same = false;
                        REP(bii, bi) REP(bjj, nBlocks) if (valid[d][bii][bjj]) {
                            if (!same) {
                                same = true;
                                REP(i, blockSize) REP(j, blockSize)
                                    if (field[bi*blockSize+i][bj*blockSize+j] != field[bii*blockSize+i][bjj*blockSize+j])
                                        same = false;
                            }
                        }
                        for(int bii = bi; bii <= bi; bii++) REP(bjj, bj) if (valid[d][bii][bjj]) {
                            if (!same) {
                                same = true;
                                REP(i, blockSize) REP(j, blockSize)
                                    if (field[bi*blockSize+i][bj*blockSize+j] != field[bii*blockSize+i][bjj*blockSize+j])
                                        same = false;
                            }
                        }
                        tm = same;
                        if (!same || d == 0) {
                            cout << "res2++: blockSize=" << blockSize << "; (" << bi << "," << bj << ")" << endl;
                            res2++;
                        }
                    }
                }
            }
        }

        cout << res1 << " " << res2 << endl;

    }

    return 0;
}



// Powered by fate testarossa
