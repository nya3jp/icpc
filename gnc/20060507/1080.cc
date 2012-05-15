#include <cstdio>
#include <limits>
#include <algorithm>
#include <cassert>

using namespace std;

int score(char a, char b) {
    if (a > b)
        swap(a, b);
    if (a == '-') {
        switch(b) {
        case '-': assert(false);
        case 'A': return -3;
        case 'C': return -4;
        case 'G': return -2;
        case 'T': return -1;
        }
    }
    if (a == 'A') {
        switch(b) {
        case 'A': return 5;
        case 'C': return -1;
        case 'G': return -2;
        case 'T': return -1;
        }
    }
    if (a == 'C') {
        switch(b) {
        case 'C': return 5;
        case 'G': return -3;
        case 'T': return -2;
        }
    }
    if (a == 'G') {
        switch(b) {
        case 'G': return 5;
        case 'T': return -2;
        }
    }
    if (a == 'T') {
        switch(b) {
        case 'T': return 5;
        }
    }
    assert(false);
    return 0;
}

int main() {
    int nCases;
    scanf("%d", &nCases);
    for(int iCase = 0; iCase < nCases; iCase++) {
        int n, m;
        char s[128], t[128];
        scanf("%d%s%d%s", &n, s, &m, t);
        int table[128][128];
        table[0][0] = 0;
        for(int i = 1; i <= n; i++)
            table[i][0] = table[i-1][0] + score(s[i-1], '-');
        for(int j = 1; j <= m; j++)
            table[0][j] = table[0][j-1] + score('-', t[j-1]);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                table[i][j] = table[i-1][j-1] + score(s[i-1], t[j-1]);
                table[i][j] = max(table[i][j], table[i-1][j] + score(s[i-1], '-'));
                table[i][j] = max(table[i][j], table[i][j-1] + score('-', t[j-1]));
                //printf("%3d ", table[i][j]);
            }
            //printf("\n");
        }
        int best = numeric_limits<int>::min();
        {
            int penalty[128];
            penalty[n] = 0;
            for(int i = n-1; i >= 0; i--)
                penalty[i] = penalty[i+1] + score(s[i], '-');
            for(int i = 0; i <= n; i++) {
                //printf("%d,%d -> %d + %d\n", i, m, table[i][m], penalty[i]);
                best = max(best, table[i][m] + penalty[i]);
            }
        }
        {
            int penalty[128];
            penalty[m] = 0;
            for(int i = m-1; i >= 0; i--)
                penalty[i] = penalty[i+1] + score('-', t[i]);
            for(int i = 0; i <= m; i++) {
                //printf("%d,%d -> %d + %d\n", n, i, table[n][i], penalty[i]);
                best = max(best, table[n][i] + penalty[i]);
            }
        }
        printf("%d\n", best);
    }
    return 0;
}
