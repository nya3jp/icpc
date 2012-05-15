#include <cstdio>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <memory.h>

using namespace std;

typedef long long int integer;
const integer MOD = 100000000000000000ll;

#define N 126

integer mem1[N][N][N];
integer mem2[N][N][N];
int n, n1, n2;
int sums1[N], sums2[N];

integer solve1(int s1, int s2, int s3, int k) {
    if (k == n1-1)
        return 1;

    integer m = mem1[s1][s2][s3];
    if (m < 0) {
        m = 0;
        const int s = sums1[k];
        const int l1 = max(0, s-s2-s3);
        const int u1 = min(s, s1);
        for(int a1 = l1; a1 <= u1; a1++) {
            const int l2 = max(0, s-a1-s3);
            const int u2 = min(s-a1, s2);
            for(int a2 = l2; a2 <= u2; a2++) {
                const int a3 = s-a1-a2;
                m += solve(s1-a1, s2-a2, s3-a3, k+1);
                if (m >= MOD*10)
                    m %= MOD;
            }
        }
        m %= MOD;
        mem[s1][s2][s3] = m;
    }
    return m;
}


int main() {
    memset(mem, -1, sizeof(mem));
    int s1, s2, s3;
    cin >> n >> s1 >> s2 >> s3;
    for(int i = 0; i < n; i++)
        cin >> sums[i];
    //sort(sums, sums+n, less<int>());
    sort(sums, sums+n, greater<int>());
    rotate(sums, sums+1, sums+n);
    if (accumulate(sums, sums+n, (int)0) != s1+s2+s3) {
        cout << 0 << endl;
    }
    else {
        cout << solve(s1, s2, s3, 0) << endl;
    }
    return 0;
}

