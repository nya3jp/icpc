#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int n;
int m;

bool table[15][10000];
int current[16][10000];

int res;

void search(int j, int zero, int total) {
    int remain = current[j][0];
    if (total < res) {
        if (remain == 0) {
            res = total;
        }
        else if (total == res-1) {
            return;
        }
        else if (j == m) {
            return;
        }
        else {
            if (table[j][0]) {
                int nextremain = 0;
                REP(i, remain)
                    if (table[j][current[j][i+1]])
                        current[j+1][++nextremain] = current[j][i+1];
                current[j+1][0] = nextremain;
                search(j+1, zero, total+1);
            }
            else {
                int nextremain = 0;
                REP(i, remain)
                    if (!table[j][current[j][i+1]])
                        current[j+1][++nextremain] = current[j][i+1];
                current[j+1][0] = nextremain;
                search(j+1, zero+1, total+(zero >= 2 ? 2 : 1));
            }
            memcpy(current[j+1], current[j], sizeof(int)*(remain+1));
            search(j+1, zero, total);
        }
    }
}

int solve() {

    res = 123456789;

    current[0][0] = n-1;
    for(int i = 1; i < n; i++)
        current[0][i] = i;
    search(0, 0, 0);

    return res;
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        scanf("%d%d", &n, &m);

        REP(i, n) {
            char buf[1024];
            scanf("%s", buf);
            REP(j, m)
                table[j][i] = (buf[j] == '1');
        }

        printf("%d\n", solve());

    }

    return 0;
}

