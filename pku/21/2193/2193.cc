#include <iostream>
#include <algorithm>
#include <map>
#include <memory.h>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef long long int integer;

integer mem[11][2010];
int n, m;

integer solve(int pos, int lower) {
    if (pos == n)
        return 1;
    if (lower > 2000)
        return 0;
    if (mem[pos][lower] < 0) {
        integer res = 0;
        for(int next = lower; next <= m; next++)
            res += solve(pos+1, next*2);
        mem[pos][lower] = res;
    }
    return mem[pos][lower];
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        cin >> n >> m;
        memset(mem, -1, sizeof(mem));
        cout << "Case "
             << (iCase+1)
             << ": n = "
             << n
             << ", m = "
             << m
             << ", # lists = "
             << solve(0, 1)
             << endl;
    }


    return 0;
}
