#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 50000
#define LOGN 16

int n;

int seq[N];
int firsts[N];
int lasts[N];
int mintable[LOGN][N];

void make_mintable() {
    REP(i, n)
        mintable[0][i] = seq[i];
    for(int i = 1; i < LOGN; i++) {
        int p = 1 << i;
        REP(j, n) {
            if (j+p > n)
                break;
            mintable[i][j] = min(mintable[i-1][j], mintable[i-1][j+(p>>1)]);
        }
    }
}

int range_min(int s, int t) {
    int res = numeric_limits<int>::max();
    for(int i = LOGN; i >= 0; i--) {
        int p = 1 << i;
        if (s + p <= t) {
            res <?= mintable[i][s];
            s += p;
        }
    }
    return res;
}

void generate(int* seq, int n, int mod, int a1, int a2, int a3) {
    REP(i, n) {
        long long t = 0;
        t += a1;
        t %= mod;
        t *= i;
        t %= mod;
        t += a2;
        t %= mod;
        t *= i;
        t %= mod;
        t += a3;
        t %= mod;
        seq[i] = (int)t;
    }
}

int mins[N];

int main() {

    //freopen("1341.in", "r", stdin);

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        cin >> n;
        int a1, a2, a3;
        cin >> a1 >> a2 >> a3;
        generate(seq, n, 9973, a1, a2, a3);
        /*
        REP(i, n)
            printf("%d ", seq[i]);
        */
        make_mintable();
        int m;
        cin >> m;
        int b1, b2, b3, c1, c2, c3;
        cin >> b1 >> b2 >> b3 >> c1 >> c2 >> c3;
        generate(firsts, m, n/2, b1, b2, b3);
        generate(lasts, m, n/2, c1, c2, c3);
        REP(i, m)
            lasts[i] += firsts[i];
        int maxi = -1;
        REP(i, m) {
            mins[i] = range_min(firsts[i], lasts[i]+1);
            maxi >?= mins[i];
        }
        int res = find(mins, mins+m, maxi) - mins;
        printf("%d\n", res);
    }

    return 0;
}

