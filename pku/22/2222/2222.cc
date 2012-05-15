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


#define N 15
#define H 10
#define W 10

char field[H][W];
int erase[H][W];
int pieces[N][2];

int h, w;
int n;

#define VALID_RANGE(i,j) (IN(i, 0, h) && IN(j, 0, w))

void erasee(int i, int j, int d) {
    if (VALID_RANGE(i, j))
        erase[i][j] += d;
    
}

void eraseeKing(int pi, int pj, int d) {
    for(int di = -1; di <= 1; di++) {
        for(int dj = -1; dj <= 1; dj++) {
            if (!(di == 0 && dj == 0)) {
                erasee(pi+di, pj+dj, d);
            }
        }
    }
}

void eraseeQueen(int pi, int pj, int d) {
    for(int k = 1; k < max(W, H); k++) {
        erasee(pi-k, pj-k, d);
        erasee(pi+k, pj-k, d);
        erasee(pi-k, pj+k, d);
        erasee(pi+k, pj+k, d);
        erasee(pi-k, pj, d);
        erasee(pi+k, pj, d);
        erasee(pi, pj+k, d);
        erasee(pi, pj-k, d);
    }
}

void eraseeBishop(int pi, int pj, int d) {
    for(int k = 1; k < max(W, H); k++) {
        erasee(pi-k, pj-k, d);
        erasee(pi+k, pj-k, d);
        erasee(pi-k, pj+k, d);
        erasee(pi+k, pj+k, d);
    }
}

void eraseeRook(int pi, int pj, int d) {
    for(int k = 1; k < max(W, H); k++) {
        erasee(pi-k, pj, d);
        erasee(pi+k, pj, d);
        erasee(pi, pj+k, d);
        erasee(pi, pj-k, d);
    }
}

void eraseePawn(int pi, int pj, int d) {
    assert(false);
}

void eraseeKnight(int pi, int pj, int d) {
    erasee(pi-2, pj-1, d);
    erasee(pi-1, pj-2, d);
    erasee(pi+1, pj-2, d);
    erasee(pi+2, pj-1, d);
    erasee(pi+2, pj+1, d);
    erasee(pi+1, pj+2, d);
    erasee(pi-1, pj+2, d);
    erasee(pi-2, pj+1, d);
}

void do_erasee(int iPiece, int d) {
    assert(IN(iPiece, 0, n));
    int pi = pieces[iPiece][0];
    int pj = pieces[iPiece][1];
    char c = field[pi][pj];
    switch(c) {
    case 'K':
        eraseeKing(pi, pj, d);
        break;
    case 'Q':
        eraseeQueen(pi, pj, d);
        break;
    case 'R':
        eraseeRook(pi, pj, d);
        break;
    case 'B':
        eraseeBishop(pi, pj, d);
        break;
    case 'N':
        eraseeKnight(pi, pj, d);
        break;
    default:
        assert(false);
    }
}

int search(int iPiece) {
    if (iPiece == n) {
        int res = 0;
        REP(i, h) REP(j, w) {
            if (erase[i][j] > 0 && field[i][j] != 'E')
                res++;
        }
        return res;
    }

    int pi = pieces[iPiece][0];
    int pj = pieces[iPiece][1];
    assert(field[pi][pj] != 'E');

    if (erase[pi][pj] > 0)
        return search(iPiece+1);

    assert(erase[pi][pj] == 0);

    erase[pi][pj]++;
    int res1 = search(iPiece+1);
    erase[pi][pj]--;

    do_erasee(iPiece, 1);

    int res2 = search(iPiece+1);

    do_erasee(iPiece, -1);

    return min(res1, res2);
}

int main() {

    // May fate be with you!

    char buf[1024];
    while(scanf("%s", buf), strcmp(buf, "START") == 0) {

        scanf("%d%d", &w, &h);

        n = 0;
        REP(i, h) REP(j, w) {
            char c;
            scanf(" %c", &c);
            field[i][j] = c;
            if (c != 'E') {
                pieces[n][0] = i;
                pieces[n][1] = j;
                n++;
            }
        }

        REP(i, h) REP(j, w) {
            erase[i][j] = 0;
        }

        printf("Minimum Number of Pieces to be removed: %d\n",
               search(0));

        scanf("%s", buf);
        assert(strcmp(buf, "END") == 0);

    }

    return 0;
}



// Powered by fate testarossa
